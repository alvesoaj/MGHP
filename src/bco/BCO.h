/*
 * BCO.h
 *
 *  Created on: Mar 16, 2013
 *      Author: zerokol
 */

#ifndef BCO_H_
#define BCO_H_

// Importando bibliotecas necessárias
#include <iostream> // Biblioteca  padrão de I/O
#include <vector>
#include <string> // Para trabalhar fácil com strings
#include <math.h>
#include "Source.h"
#include "../ferramentas/Conversor.h"
#include "../ferramentas/Sugeno.h"
#include "../poesh/SistemaHidroeletrico.h"

using namespace std;

#define INVALID -1

class BCO {
public:
	vector<vector<double> > bestSolutions;
	vector<vector<double> > worseSolutions;
	double bestFitness;
	double worseFitness;
	int bestSolutionAt;

	vector<double> bestFitnessArray;

	// métricas
	double average;
	double variance;
	double standard_deviation;

	BCO(int populationSize, int maxNumCycles, int plantSize, int intervalSize,
			SistemaHidroeletrico* sistemaHidroeletrico);

	// Métodos públicos
	void calculateSolution();

private:
	int cycle;
	int populationSize;
	int maxNumCycles;
	int plantSize;
	int intervalSize;
	int intervalToModify;
	int foodSourcesSize;
	int limit;
	int upperBound;
	int lowerBound;
	// Objects
	Conversor conversor;
	Sugeno sugeno;
	vector<Source*> sources;
	SistemaHidroeletrico* sistemaHidroeletrico;

	// Métodos privados
	void sendEmployedBees();
	void initializeSources();
	void getBestSource();
	double calculateFitness(vector<vector<double> > solutions);
	void calculateAllFitness();
	double desnormalizarVolume(double valor, double volumeMinimo,
			double volumeMaximo);
	void calculateProbabilities();
	void sendOnlookerBees();
	void sendScoutBees();
	void resetBestRoute();
	void desnormalizarRotasFinais();
	void calculateMetrics();
};

#endif /* BCO_H_ */
