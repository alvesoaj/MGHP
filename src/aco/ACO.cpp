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

	this->fuzzy = new Fuzzy();

	// FuzzyInput
	this->valorEAS = new FuzzyInput(1);

	this->muitoBaixa = new FuzzySet(0.0, 0.0, 0.1, 0.3);
	this->valorEAS->addFuzzySet(this->muitoBaixa);
	this->baixa = new FuzzySet(0.1, 0.3, 0.3, 0.5);
	this->valorEAS->addFuzzySet(this->baixa);
	this->media = new FuzzySet(0.3, 0.5, 0.5, 0.7);
	this->valorEAS->addFuzzySet(this->media);
	this->alta = new FuzzySet(0.5, 0.7, 0.7, 0.9);
	this->valorEAS->addFuzzySet(this->alta);
	this->muitoAlta = new FuzzySet(0.7, 0.9, 1.0, 1.0);
	this->valorEAS->addFuzzySet(this->muitoAlta);

	this->fuzzy->addFuzzyInput(this->valorEAS);

	// FuzzyOutput
	this->output1 = new FuzzyOutput(1);

	this->powerOf1 = new FuzzySet(0, 10, 10, 20);
	this->output1->addFuzzySet(this->powerOf1);

	// this->output2 = new FuzzyOutput(2);

	this->powerOf2 = new FuzzySet(20, 30, 30, 40);
	this->output1->addFuzzySet(this->powerOf2);

	// this->output3 = new FuzzyOutput(3);

	this->powerOf3 = new FuzzySet(40, 50, 50, 60);
	this->output1->addFuzzySet(this->powerOf3);

	// this->output4 = new FuzzyOutput(4);

	this->powerOf4 = new FuzzySet(60, 70, 70, 80);
	this->output1->addFuzzySet(this->powerOf4);

	// this->output5 = new FuzzyOutput(5);

	this->powerOf5 = new FuzzySet(80, 90, 90, 100);
	this->output1->addFuzzySet(this->powerOf5);

	this->fuzzy->addFuzzyOutput(this->output1);
	// this->fuzzy->addFuzzyOutput(this->output2);
	// this->fuzzy->addFuzzyOutput(this->output3);
	// this->fuzzy->addFuzzyOutput(this->output4);
	// this->fuzzy->addFuzzyOutput(this->output5);

	this->ifEASMuitoBaixa = new FuzzyRuleAntecedent();
	this->ifEASMuitoBaixa->joinSingle(this->muitoBaixa);

	this->thenSetPowerOf1 = new FuzzyRuleConsequent();
	this->thenSetPowerOf1->addOutput(this->powerOf1);

	this->fuzzyRule1 = new FuzzyRule(1, this->ifEASMuitoBaixa,
			this->thenSetPowerOf1);
	this->fuzzy->addFuzzyRule(fuzzyRule1);

	this->ifEASBaixa = new FuzzyRuleAntecedent();
	this->ifEASBaixa->joinSingle(this->baixa);

	this->thenSetPowerOf2 = new FuzzyRuleConsequent();
	this->thenSetPowerOf2->addOutput(this->powerOf2);

	this->fuzzyRule2
			= new FuzzyRule(2, this->ifEASBaixa, this->thenSetPowerOf2);
	this->fuzzy->addFuzzyRule(fuzzyRule2);

	this->ifEASMedia = new FuzzyRuleAntecedent();
	this->ifEASMedia->joinSingle(this->media);

	this->thenSetPowerOf3 = new FuzzyRuleConsequent();
	this->thenSetPowerOf3->addOutput(this->powerOf3);

	this->fuzzyRule3
			= new FuzzyRule(3, this->ifEASMedia, this->thenSetPowerOf3);
	this->fuzzy->addFuzzyRule(fuzzyRule3);

	this->ifEASAlta = new FuzzyRuleAntecedent();
	this->ifEASAlta->joinSingle(this->alta);

	this->thenSetPowerOf4 = new FuzzyRuleConsequent();
	this->thenSetPowerOf4->addOutput(this->powerOf4);

	this->fuzzyRule4 = new FuzzyRule(4, this->ifEASAlta, this->thenSetPowerOf4);
	this->fuzzy->addFuzzyRule(fuzzyRule4);

	this->ifEASMuitoAlta = new FuzzyRuleAntecedent();
	this->ifEASMuitoAlta->joinSingle(this->muitoAlta);

	this->thenSetPowerOf5 = new FuzzyRuleConsequent();
	this->thenSetPowerOf5->addOutput(this->powerOf5);

	this->fuzzyRule5 = new FuzzyRule(5, this->ifEASMuitoAlta,
			this->thenSetPowerOf5);
	this->fuzzy->addFuzzyRule(fuzzyRule5);

	this->a[0][0] = 0.1026;
	this->a[0][1] = 0.9093;
	this->a[0][2] = 1.4882;
	this->a[0][3] = 1.3235;
	this->a[0][4] = 1.4533;

	this->b[0][0] = -0.0044;
	this->b[0][1] = -0.2129;
	this->b[0][2] = -0.4469;
	this->b[0][3] = -0.3404;
	this->b[0][4] = -0.4440;

	this->a[1][0] = 1.1396;
	this->a[1][1] = 2.3585;
	this->a[1][2] = 0.4784;
	this->a[1][3] = 0.5209;
	this->a[1][4] = 0.6147;

	this->b[1][0] = -0.0284;
	this->b[1][1] = -0.2611;
	this->b[1][2] = 0.5234;
	this->b[1][3] = 0.4924;
	this->b[1][4] = 0.4121;
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
	this->desnormalizarRotas();
}

// Métodos privados
void ACO::initializeAnts() {
	for (int i = 0; i < this->populationSize; i++) {
		Ant *a = new Ant(i, this->plantSize, this->intervalSize);
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
	double
			energiaArmazenadaSistemaMaxima =
					this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMaxima();
	double
			energiaArmazenadaSistemaMinima =
					this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistemaMinima();

	// Para cada formiga
	for (int a = 0; a < this->populationSize; a++) {
		ants.at(a)->initSearch();
		// para cada usina
		for (int p = 0; p < this->plantSize; p++) {
			// Enquanto não passar por todos os intervalos
			while (ants.at(a)->getPosition(p) < (this->intervalSize - 1)) {
				int position = ants.at(a)->getPosition(p);

				double
						energiaArmazenadaSistema =
								this->sistemaHidroeletrico->calcularEnergiaArmazenadaSistema(
										position);

				double energiaArmazenadaSistemaNormalizada =
						(energiaArmazenadaSistema
								- energiaArmazenadaSistemaMinima)
								/ (energiaArmazenadaSistemaMaxima

								- energiaArmazenadaSistemaMinima);

				double volumeHeuristica = calcularVolumeHeuristica(p,
						energiaArmazenadaSistemaNormalizada);

				int posicaoHeuristica = this->getPosicao(volumeHeuristica);

				double sugestoes[this->valueSize];
				double val = 1.0;
				for (int i = posicaoHeuristica; i < this->valueSize; i++) {
					sugestoes[i] = val;
					if (val > 0.0) {
						val -= 0.34;
					}
					if (val < 0.0) {
						val = 0.0;
					}
				}
				val = 1.0;
				for (int i = posicaoHeuristica; i >= 0; i--) {
					sugestoes[i] = val;
					if (val > 0.0) {
						val -= 0.34;
					}
					if (val < 0.0) {
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
				for (int v = 0; v < this->valueSize; v++) {
					transition_probability[v] = (pow(
							this->pheromoneLinks[p][position][v], ALFA) * pow(
							sugestoes[v], BETA)) / link_rate_sum;
				}

				// Selecionando o próximo nó
				// fazendo a roleta
				double roulette = conversor.get_random_number();

				double minor = 0.0;
				double major = 0.0;
				for (int v = 0; v < this->valueSize; v++) {
					major += transition_probability[v];
					if (roulette >= minor and roulette <= major) {
						ants.at(a)->routes[p][position + 1] = this->getValue(v);
						ants.at(a)->increasePosition(p);
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
			this->worseRoutes
					= this->ants.at(this->populationSize - 1)->getRoutes();
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

double ACO::calcularVolumeHeuristica(int usinaIndice,
		double energiaArmazenadaSistemaNormalizada) {
	double produtoSoma = 0.0;
	double pertinenciaSoma = 0.0;

	this->fuzzy->setInput(1, energiaArmazenadaSistemaNormalizada);
	this->fuzzy->fuzzify();
	// this->fuzzy->defuzzify(1);

	if (this->powerOf1->getPertinence() > 0) {
		double saida = this->a[usinaIndice][0]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][0];
		produtoSoma += this->powerOf2->getPertinence() * saida;
		pertinenciaSoma += this->powerOf2->getPertinence();
	}
	if (this->powerOf2->getPertinence() > 0) {
		double saida = this->a[usinaIndice][1]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][1];
		produtoSoma += this->powerOf2->getPertinence() * saida;
		pertinenciaSoma += this->powerOf2->getPertinence();
	}
	if (this->powerOf3->getPertinence() > 0) {
		double saida = this->a[usinaIndice][2]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][2];
		produtoSoma += this->powerOf3->getPertinence() * saida;
		pertinenciaSoma += this->powerOf3->getPertinence();
	}
	if (this->powerOf4->getPertinence() > 0) {
		double saida = this->a[usinaIndice][3]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][3];
		produtoSoma += this->powerOf4->getPertinence() * saida;
		pertinenciaSoma += this->powerOf4->getPertinence();
	}
	if (this->powerOf5->getPertinence() > 0) {
		double saida = this->a[usinaIndice][4]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][4];
		produtoSoma += this->powerOf5->getPertinence() * saida;
		pertinenciaSoma += this->powerOf5->getPertinence();
	}

	return produtoSoma / pertinenciaSoma;
}

int ACO::getPosicao(double value) {
	if (value < 0.0) {
		return 0;
	} else if (value > 1.0) {
		return this->valueSize - 1;
	} else {
		for (int i = (0 + 1); i < this->valueSize; i++) {
			if (this->getValue(i - 1) >= value && this->getValue(i) < value) {
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
