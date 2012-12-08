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
	this->sistemaHidroeletrico = sistemaHidroeletrico;
}

// Métodos públicos
void ACO::calculateSolution() {
	int iteration = 0;
	// Inicializando os objetos formigas
	this->initializeAnts();
	// Configurando as concetrações iniciais de feromônio
	this->seedInitialPheromone();

	while (iteration < maxIterationSize) {
		this->buildSolutions();
		this->checkBestSolution();
		this->pheromoneEvaporates();
		this->updatePheromone();
		iteration++;
	}
}

// Métodos privados
void ACO::initializeAnts() {
	for (int i = 0; i < this->populationSize; i++) {
		Ant *a = new Ant(i, this->plantSize, this->intervalSize);
		// Iniciar com o reservatório cheio, 100%
		for (int p = 0; p < this->plantSize; p++) {
			a->routes[p][0] = this->getValue(this->valueSize);
		}
		// adicionar a formiga ao aray de formigas
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
				tempValueArray.push_back(r);
			}
			tempIntervalArray.push_back(tempValueArray);
		}
		this->pheromoneLinks.push_back(tempIntervalArray);
	}
}

void ACO::buildSolutions() {
	// Para cada formiga
	for (int a = 0; a < this->populationSize; a++) {
		ants.at(a)->initSearch();
		// Enquanto não passar por todos os intervalos
		while (ants.at(a)->getPosition() < (this->intervalSize - 1)) {
			int position = ants.at(a)->getPosition();
			double transition_probability[this->plantSize][this->valueSize];
			double link_rate_sum[this->plantSize];
			// Somando as taxas de feromonio e heuristica
			for (int p = 0; p < this->plantSize; p++) {
				link_rate_sum[p] = 0.0;
				for (int v = 0; v < this->valueSize; v++) {
					link_rate_sum[p] += this->pheromoneLinks[p][position][v];
				}
			}
			// Calculando a probabilidade de transição
			for (int p = 0; p < this->plantSize; p++) {
				for (int v = 0; v < this->valueSize; v++) {
					transition_probability[p][v] =
							this->pheromoneLinks[p][position][v]
									/ link_rate_sum[p];
				}
			}

			// Selecionando o próximo nó
			for (int p = 0; p < this->plantSize; p++) {
				// fazendo a roleta
				double roulette = conversor.get_random_number();

				double minor = 0.0;
				double major = 0.0;
				for (int v = 0; v < this->valueSize; v++) {
					major += transition_probability[p][v];
					if (roulette >= minor and roulette <= major) {
						ants.at(a)->routes[p][v] = this->getValue(v);
						ants.at(a)->incrasePosition();
						break;
					} else {
						minor = major;
					}
				}
			}
		}
	}
}

double ACO::getValue(int position) {
	return ((double) position / (double) this->valueSize);
}

void ACO::checkBestSolution() {
	if (this->ants.size() > 0) {
		if (this->bestFitness == INVALID and this->worseFitness == INVALID) {
			this->bestFitness = this->calculateFitness(
					this->ants.at(0)->getRoutes());
			this->bestRoutes = this->ants.at(0)->getRoutes();

			this->worseFitness = this->calculateFitness(
					this->ants.at(this->populationSize - 1)->getRoutes());
			this->worseRoutes =
					this->ants.at(this->populationSize - 1)->getRoutes();
		}
		for (int i = 0; i < this->populationSize; i++) {
			this->ants.at(i)->setFitness(
					this->calculateFitness(this->ants.at(i)->getRoutes()));
			if (this->ants.at(i)->getFitness() < this->bestFitness) {
				this->bestFitness = this->ants.at(i)->getFitness();
				this->bestRoutes = this->ants.at(i)->getRoutes();
			} else if (this->ants.at(i)->getFitness() > this->worseFitness) {
				this->worseFitness = this->ants.at(i)->getFitness();
				this->worseRoutes = this->ants.at(i)->getRoutes();
			}
		}
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
			tempRoute.push_back(volume);
		}
		desnormalizedRoutes.push_back(tempRoute);
	}
	this->sistemaHidroeletrico->setVolumes(desnormalizedRoutes);
	return this->sistemaHidroeletrico->calcularCustoTotal();
}

void ACO::pheromoneEvaporates() {
	for (int i = 0; i < this->plantSize; i++) {
		for (int j = 0; j < this->intervalSize; j++) {
			for (int v = 0; v < this->valueSize; v++) {
				this->pheromoneLinks[i][j][v] = (1 - this->evaporationRate)
						* this->pheromoneLinks[i][j][v];
			}
		}
	}
}

void ACO::updatePheromone() {
	for (int a = 0; a < this->populationSize; a++) {
		for (int p = 0; p < this->plantSize; p++) {
			for (int i = 0; i < this->intervalSize; i++) {
				vector<vector<double> > routes = this->ants.at(a)->getRoutes();
				for (int v = 0; v < (this->valueSize - 1); v++) {
					this->pheromoneLinks[p][i][v] += (this->positiveConstant
							/ this->ants.at(a)->getFitness());
				}
			}
		}
	}
}

double ACO::desnormalizarVolume(double valor, double volumeMinimo,
		double volumeMaximo) {
	return valor * (volumeMaximo - volumeMinimo) + volumeMinimo;
}
