/*
 * ACO.h
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#ifndef ACO_H_
#define ACO_H_

// Importando bibliotecas necessárias
#include <vector>
#include "Ant.h"
#include "../ferramentas/Conversor.h"

using std::vector;

// Constantes
#define INVALID -1

class ACO {
public:
	// Variáveis públicas
	double bestFitness;
	vector<vector<double> > bestRoutes;
	double worseFitness;
	vector<vector<double> > worseRoutes;

	// Construtor
	ACO(int populationSize, int plantSize, int intervalSize, int valueSize,
			int maxIterationSize, double pheromoneRate, double evaporationRate,
			double positiveConstant);

	// Métodos públicos
	void calculateSolution();

private:
	// Variáveis privadas
	int populationSize;
	int plantSize;
	int intervalSize;
	int valueSize;
	int maxIterationSize;
	double pheromoneRate;
	double evaporationRate;
	double positiveConstant;
	vector<vector<vector<double> > > pheromoneLinks;
	vector<Ant*> ants;
	Conversor conversor;

	// Métodos privados
	void initializeAnts();
	void seedInitialPheromone();
	void buildSolutions();
	double getValue(int position);
	void checkBestSolution();
	void pheromoneEvaporates();
	void updatePheromone();
};

#endif /* ACO_H_ */
