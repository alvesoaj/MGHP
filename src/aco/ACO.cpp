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
			a->addInRouteAtPositionValue(p, 0, this->getValue(this->valueSize));
		}
		// adicionar a formiga ao aray de formigas
		this->ants.push_back(a);
	}
}

void ACO::seedInitialPheromone() {
	for (int i = 0; i < this->plantSize; i++) {
		vector<vector<double> > tempIntervalArray;
		for (int j = 0; j < this->intervalSize; j++) {
			vector<double> tempValueArray;
			for (int v = 0; v < this->valueSize; v++) {
				tempValueArray.push_back(this->pheromoneRate);
			}
			tempIntervalArray.push_back(tempValueArray);
		}
		this->pheromoneLinks.push_back(tempIntervalArray);
	}
}

void ACO::buildSolutions() {
	// Para cada formiga
	for (int i = 0; i < this->populationSize; i++) {
		ants.at(i)->initSearch();
		// Enquanto não passar por todos os intervalos
		while (ants.at(i)->getPosition() < (this->intervalSize - 1)) {
			int position = ants.at(i)->getPosition();
			double transition_probability[this->plantSize][this->valueSize];
			double link_rate_sum[this->plantSize];
			// Somando as taxas de feromonio e heuristica
			for (int p = 0; p < this->plantSize; p++) {
				link_rate_sum[p] = 0.0;
				for (int j = 0; j < this->valueSize; j++) {
					link_rate_sum[p] += this->pheromoneLinks[p][position][j];
				}
			}
			// Calculando a probabilidade de transição
			for (int p = 0; p < this->plantSize; p++) {
				for (int j = 0; j < this->valueSize; j++) {
					transition_probability[p][j] =
							this->pheromoneLinks[p][position][j]
									/ link_rate_sum[p];
				}
			}
			// fazendo a roleta
			double roulette = (double) conversor.get_random_number(0, 100)
					/ 100.0;
			double minor = 0.0;
			double major = 0.0;
			// Selecionando o próximo nó
			for (int p = 0; p < this->plantSize; p++) {
				for (int j = 0; j < this->valueSize; j++) {
					major += transition_probability[p][j];
					if (roulette >= minor and roulette <= major) {
						ants.at(i)->addInRouteAtPositionValue(p, j,
								this->getValue(j));
						ants.at(i)->incrasePosition();
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
	return (position * 1 / this->valueSize);
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
	this->sistemaHidroeletrico->setVolumes(routes);
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
					int interval = routes[p][i];
					int value = routes[p][i + 1];
					cout << "OK OK OK" << endl;
					this->pheromoneLinks[p][interval][value] +=
							(this->positiveConstant
									/ this->ants.at(a)->getFitness());
				}
			}
		}
	}
}
