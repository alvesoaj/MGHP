/*
 * BCO.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: zerokol
 */
#include "BCO.h"

// Construtor
BCO::BCO(int populationSize, int maxNumCycles, int plantSize, int intervalSize,
		SistemaHidroeletrico* sistemaHidroeletrico) {
	this->populationSize = populationSize;
	this->maxNumCycles = maxNumCycles;
	this->plantSize = plantSize;
	this->intervalSize = intervalSize;
	this->intervalToModify = (intervalSize / 10) + 1;
	this->sistemaHidroeletrico = sistemaHidroeletrico;

	this->foodSourcesSize = this->populationSize / 2;
	this->limit = (this->populationSize * this->intervalSize) / 2;

	this->bestSolutionAt = INVALID;

	this->sugeno = Sugeno();
}

// Métodos públicos
void BCO::calculateSolution() {
	cycle = 0; // Inicializar o contador de interações
	// comandos iniciais
	this->initializeSources();
	// Iniciar ciclos de busca
	while (cycle < this->maxNumCycles) {
		if (cycle % 100 == 0) {
			cout << "---------------------- " << cycle << endl;
		}
		sendEmployedBees();
		calculateProbabilities();
		sendOnlookerBees();
		sendScoutBees();
		calculateAllFitness();
		getBestSource();

		if (cycle % 1000 == 0) {
			string temp = "Ciclo(" + conversor.double_para_string(cycle)
					+ ")->\n";
			for (int p = 0; p < this->plantSize; p++) {
				temp += "\t U(" + conversor.double_para_string(p) + "): ";
				for (int i = 0; i < this->intervalSize; i++) {
					temp += conversor.double_para_string(
							this->bestSolutions[p][i]);
					if (i < this->intervalSize - 1) {
						temp += ", ";
					}
				}
				temp += "\n";
			}
			cout << temp << endl;
		}

		cycle++;
		// cin.get();
	}
	cout << "Melhor sulução encontrada em: " << this->bestSolutionAt << endl;
	this->desnormalizarRotasFinais();
}

// Métodos privados
void BCO::initializeSources() {
	// Iniciar todos os sources
	for (int index = 0; index < this->foodSourcesSize; index++) {
		Source* s = new Source(index, this->plantSize, this->intervalSize);
		s->setFitness(this->calculateFitness(s->solutions));
		this->sources.push_back(s);
	}

	// pegar uma solução qualquer como a melhor
	this->bestFitness = this->sources[0]->getFitness();
	this->worseFitness = this->sources[this->foodSourcesSize - 1]->getFitness();

	// pegar a real melhor solução
	getBestSource();
}

void BCO::getBestSource() {
	for (int index = 0; index < this->foodSourcesSize; index++) {
		if (this->sources[index]->getFitness() < this->bestFitness) {
			this->bestSolutions = this->sources[index]->solutions;
			this->bestFitness = this->sources[index]->getFitness();
			this->bestSolutionAt = this->cycle;
		} else if (this->sources[index]->getFitness() > this->worseFitness) {
			this->worseSolutions = this->sources[index]->solutions;
			this->worseFitness = this->sources[index]->getFitness();
		}
	}
}

double BCO::calculateFitness(vector<vector<double> > solutions) {
	vector<vector<double> > desnormalizedSolutions;
	for (int p = 0; p < this->plantSize; p++) {
		vector<double> tempRoute;
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(solutions[p][i],
					volumeMinimo, volumeMaximo);
			// cout << "xN: " << solutions[p][i] << " xDN: " << volume << endl;
			tempRoute.push_back(volume);
		}
		desnormalizedSolutions.push_back(tempRoute);
	}
	this->sistemaHidroeletrico->setVolumes(desnormalizedSolutions);

	double custo = this->sistemaHidroeletrico->calcularCustoTotal();

	// cout << "custo: " << custo << endl;

	return custo;
}

void BCO::calculateAllFitness() {
	for (int index = 0; index < this->foodSourcesSize; index++) {
		this->sources[index]->setFitness(
				this->calculateFitness(this->sources[index]->solutions));
	}
}

double BCO::desnormalizarVolume(double valor, double volumeMinimo,
		double volumeMaximo) {
	return (valor * (volumeMaximo - volumeMinimo)) + volumeMinimo;
}

void BCO::sendEmployedBees() {
	vector<vector<double> > newSolutions;
	int neighbour = 0;
	double r = 0.0;

	double energiaArmazenadaSistemaMaxima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMaxima();
	double energiaArmazenadaSistemaMinima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMinima();

	for (int i = 0; i < this->foodSourcesSize; i++) {
		/* copiar solução atual */
		newSolutions = this->sources[i]->solutions;

		for (int j = 0; j < this->intervalToModify; j++) {
			r = conversor.get_random_number();

			int param_to_modify = (int) (r * (this->intervalSize - 1)) + 1;

			if (param_to_modify == 0) {
				param_to_modify = 1;
			}

			/* Selecionando uma outra solução para servir de influênica */
			/*
			 do {
			 r = conversor.get_random_number();
			 neighbour = (int) (r * this->foodSourcesSize);
			 } while (neighbour == i); // Impedindo que seja a mesma solução
			 */
			this->resetBestRoute();
			double energiaArmazenadaSistema =
					this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistema(
							param_to_modify);
			// cout << "EAS: " << energiaArmazenadaSistema << endl;

			double energiaArmazenadaSistemaNormalizada =
					(energiaArmazenadaSistema - energiaArmazenadaSistemaMinima)
							/ (energiaArmazenadaSistemaMaxima
									- energiaArmazenadaSistemaMinima);
			// cout << "EASn: " << energiaArmazenadaSistemaNormalizada << endl;

			for (int p = 0; p < this->plantSize; p++) {
				double volumeHeuristica = sugeno.calcularVolumeHeuristica(p,
						energiaArmazenadaSistemaNormalizada);

				// cout << "H: " << volumeHeuristica << endl;
				// cout << "nsV: " << newSolutions[p][param_to_modify] << endl;

				r = conversor.get_random_number();

				// double valueToCompare = (r < 0.5) ? this->sources[neighbour]->solutions[p][param_to_modify] : volumeHeuristica;

				/* v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) */
				r = conversor.get_random_number();

				double phi = (r - 0.5) * 2
						* (1
								- (this->sources[neighbour]->getTrail()
										/ this->limit));

				double newValue = newSolutions[p][param_to_modify]
						+ ((volumeHeuristica - newSolutions[p][param_to_modify])
								* phi);

				if (newValue > 1) {
					newValue = 1.0;
				}
				if (newValue < 0) {
					newValue = 0.0;
				}

				newSolutions[p][param_to_modify] = newValue;
			}
		}

		double newSolutionFitness = this->calculateFitness(newSolutions);

		/* verificar se a nova solução é melhor que a atual */
		if (newSolutionFitness < this->sources[i]->getFitness()) {
			this->sources[i]->solutions = newSolutions;
			this->sources[i]->setFitness(newSolutionFitness);
		} else {
			this->sources[i]->setTrail(this->sources[i]->getTrail() + 1);
		}
	}
}

void BCO::calculateProbabilities() {
	// calcular a probabilidade de cada fonte de comida ser escolhida
	for (int i = 0; i < this->foodSourcesSize; i++) {
		double prob =
				(1 - (this->sources[i]->getFitness() / this->worseFitness))
						+ 0.01;
		// cout << "Prob: " << prob << endl;
		this->sources[i]->setProbabilitie(prob);
	}
}

void BCO::sendOnlookerBees() {
	int foodSourceIndex = 0;
	int transitorIndex = 0;
	vector<vector<double> > newSolutions;
	int neighbour = 0;
	double r = 0.0;

	double energiaArmazenadaSistemaMaxima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMaxima();
	double energiaArmazenadaSistemaMinima =
			this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMinima();

	while (transitorIndex < this->foodSourcesSize) {
		/* copiar solução atual */
		newSolutions = this->sources[foodSourceIndex]->solutions;

		for (int j = 0; j < this->intervalToModify; j++) {
			r = conversor.get_random_number();
			/* Escolhendo uma fonte de comida, depende da probabilidade */
			// cout << "r: " << r << ", p: " << this->sources[foodSourceIndex]->getProbabilitie() << endl;
			if (this->sources[foodSourceIndex]->getProbabilitie() > r) {
				transitorIndex++;

				r = conversor.get_random_number();

				int param_to_modify = (int) (r * (this->intervalSize - 1)) + 1;

				if (param_to_modify == 0) {
					param_to_modify = 1;
				}

				/* Selecionando uma outra solução para servir de influênica */
				/*
				 do {
				 r = conversor.get_random_number();
				 neighbour = (int) (r * this->foodSourcesSize);
				 } while (neighbour == foodSourceIndex); // Impedindo que seja a mesma solução
				 */
				this->resetBestRoute();
				double energiaArmazenadaSistema =
						this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistema(
								param_to_modify);

				// cout << "EAS: " << energiaArmazenadaSistema << endl;

				double energiaArmazenadaSistemaNormalizada =
						(energiaArmazenadaSistema
								- energiaArmazenadaSistemaMinima)
								/ (energiaArmazenadaSistemaMaxima

								- energiaArmazenadaSistemaMinima);

				// cout << "EASn: " << energiaArmazenadaSistemaNormalizada << endl;

				for (int p = 0; p < this->plantSize; p++) {
					double volumeHeuristica = sugeno.calcularVolumeHeuristica(p,
							energiaArmazenadaSistemaNormalizada);

					// cout << "H: " << volumeHeuristica << endl;
					// cout << "nsV: " << newSolutions[p][param_to_modify] << endl;

					/* v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij}) */
					r = conversor.get_random_number();

					double phi = (r)
							* (1
									- (this->sources[neighbour]->getTrail()
											/ this->limit));

					double newValue = newSolutions[p][param_to_modify]
							+ ((volumeHeuristica
									- newSolutions[p][param_to_modify]) * phi);

					if (newValue > 1) {
						newValue = 1.0;
					}
					if (newValue < 0) {
						newValue = 0.0;
					}

					newSolutions[p][param_to_modify] = newValue;
				}
			}

			double newSolutionFitness = this->calculateFitness(newSolutions);

			/* verificar se a nova solução é melhor que a atual */
			if (newSolutionFitness
					< this->sources[foodSourceIndex]->getFitness()) {
				this->sources[foodSourceIndex]->solutions = newSolutions;
				this->sources[foodSourceIndex]->setFitness(newSolutionFitness);
			} else {
				this->sources[foodSourceIndex]->setTrail(
						this->sources[foodSourceIndex]->getTrail() + 1);
			}
		}
		foodSourceIndex++;
		if (foodSourceIndex == this->foodSourcesSize) {
			foodSourceIndex = 0;
		}
	}
}

void BCO::sendScoutBees() {
	int maxTrailIndex = 0;
	for (int i = 1; i < this->foodSourcesSize; i++) {
		if (this->sources[i]->getTrail()
				> this->sources[maxTrailIndex]->getTrail()) {
			maxTrailIndex = i;
		}
	}
	if (this->sources[maxTrailIndex]->getTrail() >= this->limit) {
		this->sources[maxTrailIndex]->initSearch();
	}
}

void BCO::resetBestRoute() {
	vector<vector<double> > desnormalizedRoutes;
	for (int p = 0; p < this->plantSize; p++) {
		vector<double> tempRoute;
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(bestSolutions[p][i],
					volumeMinimo, volumeMaximo);
			tempRoute.push_back(volume);
		}
	}
	this->sistemaHidroeletrico->setVolumes(desnormalizedRoutes);
}

void BCO::desnormalizarRotasFinais() {
	for (int p = 0; p < this->plantSize; p++) {
		double volumeMinimo =
				this->sistemaHidroeletrico->getVolumeMinimoOperativoUsina(p);
		double volumeMaximo =
				this->sistemaHidroeletrico->getVolumeMaximoOperativoUsina(p);
		for (int i = 0; i < this->intervalSize; i++) {
			double volume = this->desnormalizarVolume(this->bestSolutions[p][i],
					volumeMinimo, volumeMaximo);
			this->bestSolutions[p][i] = volume;
			volume = this->desnormalizarVolume(this->worseSolutions[p][i],
					volumeMinimo, volumeMaximo);
			this->worseSolutions[p][i] = volume;
		}
	}
}
