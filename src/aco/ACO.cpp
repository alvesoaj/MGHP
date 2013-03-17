/*
 * ACO.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#include "ACO.h"

// Construtor
ACO::ACO(int populationSize, int plantSize, int intervalSize, int valueSize,
		int maxIterationSize, double pheromoneRate, double evaporationRate,
		double positiveConstant, SistemaHidroeletrico* sistemaHidroeletrico) {
	this->bestRouteAt = INVALID;
	this->populationSize = populationSize;
	this->plantSize = plantSize;
	this->intervalSize = intervalSize;
	this->valueSize = valueSize;
	this->maxIterationSize = maxIterationSize;
	this->pheromoneRate = pheromoneRate;
	this->positiveConstant = positiveConstant;
	this->evaporationRate = evaporationRate;
	this->bestFitness = INVALID;
	this->worseFitness = INVALID;
	this->indexBestAnt = INVALID;
	this->sistemaHidroeletrico = sistemaHidroeletrico;

	this->sugeno = Sugeno();
}

// Métodos públicos
void ACO::calculateSolution() {
	iteration = 0;
	// Inicializando os objetos formigas
	this->initializeAnts();
	// Configurando as concetrações iniciais de feromônio
	this->seedInitialPheromone();

	while (iteration < maxIterationSize) {
		cout << "---------------------- " << iteration << endl;

		if (iteration % 100 == 0) {
			string phe_link_print = "PH:\n";
			for (unsigned int p = 0; p < pheromoneLinks.size(); p++) {
				vector<vector<double> > tempPheUsi;
				tempPheUsi = pheromoneLinks[p];
				phe_link_print += "\t u(" + conversor.double_para_string(p)
						+ "):\n";
				for (unsigned int i = 0; i < tempPheUsi.size(); i++) {
					vector<double> tempPheVal;
					tempPheVal = tempPheUsi[i];
					phe_link_print += "\t\t i("
							+ conversor.double_para_string(i) + "):\n\t\t\t ";
					for (unsigned int v = 0; v < tempPheVal.size(); v++) {
						phe_link_print += "v(" + conversor.double_para_string(v)
								+ "): "
								+ conversor.double_para_string(tempPheVal[v])
								+ ", ";
					}
					phe_link_print += "\n";
				}
				phe_link_print += "\n";
			}
			cout << phe_link_print << endl;
		}

		this->buildSolutions();
		this->checkBestSolution();
		this->pheromoneEvaporates();
		this->updatePheromone();
		this->resetBestRoute();

		// cin.get();
		iteration++;
	}
	cout << "Melhor sulução encontrada em: " << this->bestRouteAt << endl;
	this->desnormalizarRotas();
}

// Métodos privados
void ACO::initializeAnts() {
	for (int i = 0; i < this->populationSize; i++) {
		Ant a = Ant(i, this->plantSize, this->intervalSize);
		// adicionar a formiga ao array de formigas
		this->ants.push_back(a);
	}
}

void ACO::seedInitialPheromone() {
	for (int p = 0; p < this->plantSize; p++) {
		vector<vector<double> > tempIntervalArray;
		for (int i = 0; i < this->intervalSize; i++) {
			vector<double> tempValueArray;
			for (int v = 0; v < this->valueSize; v++) {
				double r = conversor.get_random_number();
				// tempValueArray.push_back(this->pheromoneRate);
				tempValueArray.push_back(r);
			}
			tempIntervalArray.push_back(tempValueArray);
		}
		this->pheromoneLinks.push_back(tempIntervalArray);
	}
}

void ACO::buildSolutions() {
	double energiaArmazenadaSistemaMaxima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMaxima();
	double energiaArmazenadaSistemaMinima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMinima();

	// Para cada formiga
	for (int a = 0; a < this->populationSize; a++) {
		if (this->indexBestAnt != a) {
			ants[a].initSearch();
		}
		// Para cada usina
		for (int p = 0; p < this->plantSize; p++) {
			// Enquanto não passar por todos os intervalos
			while (ants.at(a).getPosition(p) < this->intervalSize) {
				int position = ants[a].getPosition(p);

				double energiaArmazenadaSistema =
						this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistema(
								position);

				// cout << "EAS: " << energiaArmazenadaSistema << endl;

				double energiaArmazenadaSistemaNormalizada =
						(energiaArmazenadaSistema
								- energiaArmazenadaSistemaMinima)
								/ (energiaArmazenadaSistemaMaxima

								- energiaArmazenadaSistemaMinima);

				double volumeHeuristica = sugeno.calcularVolumeHeuristica(p,
						energiaArmazenadaSistemaNormalizada);

				int posicaoHeuristica = this->getPosicao(volumeHeuristica);

				// cout << "xH: " << volumeHeuristica << ", pH:" << posicaoHeuristica << endl;

				double sugestoes[this->valueSize];
				double val = 1.0;
				double drop = val / this->valueSize;
				// double drop = 0.20;
				for (int i = posicaoHeuristica; i < this->valueSize; i++) {
					sugestoes[i] = val;
					if (val > 0.0) {
						val -= drop;
					} else {
						val = 0.0;
					}
				}
				val = 1.0;
				for (int i = posicaoHeuristica; i >= 0; i--) {
					sugestoes[i] = val;
					if (val > 0.0) {
						val -= drop;
					} else {
						val = 0.0;
					}
				}

				double transition_probability[this->valueSize];
				double link_rate_sum = 0.0;
				// Somando as taxas de feromonio e heuristica
				for (int v = 0; v < this->valueSize; v++) {
					link_rate_sum += pow(this->pheromoneLinks[p][position][v],
							ALFA) * pow(sugestoes[v], BETA);
				}

				// Calculando a probabilidade de transição
				string trans_prob_print = "TP u("
						+ this->conversor.double_para_string(p) + ")i("
						+ this->conversor.double_para_string(position) + "): ";
				for (int v = 0; v < this->valueSize; v++) {
					transition_probability[v] = (pow(
							this->pheromoneLinks[p][position][v], ALFA)
							* pow(sugestoes[v], BETA)) / link_rate_sum;
					trans_prob_print += "i("
							+ this->conversor.double_para_string(v) + "): "
							+ this->conversor.double_para_string(
									transition_probability[v]) + ", ";

				}

				// cout << trans_prob_print << endl;

				// Selecionando o próximo nó
				// fazendo a roleta
				double roulette = conversor.get_random_number();

				// cout << "roll: " << roulette << endl;

				double minor = 0.0;
				double major = 0.0;
				for (int v = 0; v < this->valueSize; v++) {
					major += transition_probability[v];
					if (roulette >= minor and roulette <= major) {
						// cout << "v: " << v << endl;
						ants[a].routes[p][position] = this->getValue(v);
						ants[a].increasePosition(p);
						break;
					} else {
						minor = major;
					}
				}
			}
		}
	}
}

void ACO::checkBestSolution() {
	if (this->ants.size() > 0) {
		if (this->bestFitness == INVALID and this->worseFitness == INVALID) {
			this->bestFitness = this->calculateFitness(
					this->ants[0].getRoutes());
			this->bestRoutes = this->ants[0].getRoutes();

			this->worseFitness = this->calculateFitness(
					this->ants[this->populationSize - 1].getRoutes());
			this->worseRoutes =
					this->ants[this->populationSize - 1].getRoutes();
		}
		this->iteractionBestFitness = this->calculateFitness(
				this->ants[0].getRoutes());
		this->iteractionWorseFitness = this->calculateFitness(
				this->ants[this->populationSize - 1].getRoutes());
		for (int a = 0; a < this->populationSize; a++) {
			this->ants[a].setFitness(
					this->calculateFitness(this->ants[a].getRoutes()));
			if (this->ants[a].getFitness() < this->bestFitness) {
				this->indexBestAnt = a;
				this->bestFitness = this->ants[a].getFitness();
				this->bestRoutes = this->ants[a].getRoutes();
				this->bestRouteAt = iteration;
			} else if (this->ants[a].getFitness() > this->worseFitness) {
				this->worseFitness = this->ants[a].getFitness();
				this->worseRoutes = this->ants[a].getRoutes();
			}

			if (this->ants[a].getFitness() < this->iteractionBestFitness) {
				this->iteractionBestFitness = this->ants[a].getFitness();
			} else if (this->ants[a].getFitness()
					> this->iteractionWorseFitness) {
				this->iteractionWorseFitness = this->ants[a].getFitness();
			}
		}
		// Resetando os melhores volumes
		// this->calculateFitness(this->bestRoutes);
	}
}

double ACO::calculateFitness(vector<vector<double> > routes) {
	vector<vector<double> > desnormalizedRoutes;
	for (int p = 0; p < this->plantSize; p++) {
		vector<double> tempRoute;
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(routes[p][i],
					volumeMinimo, volumeMaximo);
			// cout << "xN: " << routes[p][i] << " xDN: " << volume << endl;
			tempRoute.push_back(volume);
		}
		desnormalizedRoutes.push_back(tempRoute);
	}
	this->sistemaHidroeletrico->setVolumes(desnormalizedRoutes);

	double custo = this->sistemaHidroeletrico->calcularCustoTotal();

	// cout << "custo: " << custo << endl;

	return custo;
}

void ACO::pheromoneEvaporates() {
	for (int i = 0; i < this->plantSize; i++) {
		for (int j = 0; j < this->intervalSize; j++) {
			for (int v = 0; v < this->valueSize; v++) {
				this->pheromoneLinks[i][j][v] = (1 - this->evaporationRate)
						* this->pheromoneLinks[i][j][v];
				if (this->pheromoneLinks[i][j][v] < MIN_PHEROMONE) {
					this->pheromoneLinks[i][j][v] = MIN_PHEROMONE;
				}
			}
		}
	}
}

void ACO::updatePheromone() {
	// double maxPheromone = 0.0;
	// double minPheromone = 1000000.0;
	for (int a = 0; a < this->populationSize; a++) {
		// cout << "f(" << a << "): " << this->ants[a].getFitness() << endl;
		// double valor = (this->ants[a].getFitness() - this->iteractionBestFitness) / ((this->iteractionWorseFitness - this->iteractionBestFitness) + MIN_PHEROMONE);
		double valor = this->bestFitness / this->ants[a].getFitness();
		double to_add = this->positiveConstant / (1 + valor);
		// cout << "v(" << a << "): " << valor << ", to_add: " << to_add << endl;
		vector<vector<double> > routes = this->ants[a].getRoutes();
		for (int p = 0; p < this->plantSize; p++) {
			for (int i = 0; i < this->intervalSize; i++) {
				for (int v = 0; v < this->valueSize; v++) {
					if (getPosicao(routes[p][i]) == v) {
						this->pheromoneLinks[p][i][v] += to_add;

						if (this->pheromoneLinks[p][i][v] > MAX_PHEROMONE) {
							this->pheromoneLinks[p][i][v] = MAX_PHEROMONE;
						}
					}
					// Pegar valores máx e min de feromônio
					/*
					 if (this->pheromoneLinks[p][i][v] < minPheromone) {
					 minPheromone = this->pheromoneLinks[p][i][v];
					 }

					 if (this->pheromoneLinks[p][i][v] > maxPheromone) {
					 maxPheromone = this->pheromoneLinks[p][i][v];
					 }
					 */
				}
			}
		}
	}
	/*
	 // Normalizando o feromônio
	 for (int p = 0; p < this->plantSize; p++) {
	 for (int i = 0; i < this->intervalSize; i++) {
	 for (int v = 0; v < (this->valueSize - 1); v++) {
	 this->pheromoneLinks[p][i][v] = (this->pheromoneLinks[p][i][v]
	 - minPheromone) / (maxPheromone - minPheromone);
	 }
	 }
	 }
	 */
}

double ACO::desnormalizarVolume(double valor, double volumeMinimo,
		double volumeMaximo) {
	return valor * (volumeMaximo - volumeMinimo) + volumeMinimo;
}

void ACO::desnormalizarRotas() {
	for (int p = 0; p < this->plantSize; p++) {
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(bestRoutes[p][i],
					volumeMinimo, volumeMaximo);
			bestRoutes[p][i] = volume;
			volume = this->desnormalizarVolume(worseRoutes[p][i], volumeMinimo,
					volumeMaximo);
			worseRoutes[p][i] = volume;
		}
	}
}

void ACO::resetBestRoute() {
	vector<vector<double> > desnormalizedRoutes;
	for (int p = 0; p < this->plantSize; p++) {
		vector<double> tempRoute;
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(bestRoutes[p][i],
					volumeMinimo, volumeMaximo);
			tempRoute.push_back(volume);
		}
	}
	this->sistemaHidroeletrico->setVolumes(desnormalizedRoutes);
}

double ACO::getValue(int position) {
	return ((double) position / (double) this->valueSize);
}

int ACO::getPosicao(double value) {
	if (value < 0.0) {
		return 0;
	} else if (value > 1.0) {
		return this->valueSize - 1;
	} else {
		for (int i = 1; i < this->valueSize; i++) {
			if (this->getValue(i - 1) >= value && value < this->getValue(i)) {
				if (value - this->getValue(i - 1) < this->getValue(i) - value) {
					return (i - 1);
				} else {
					return i;
				}
			}
		}
	}
	return this->valueSize - 1;
}
