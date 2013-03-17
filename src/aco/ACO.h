/*
 * ACO.h
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#ifndef ACO_H_
#define ACO_H_

// Importando bibliotecas necessárias
#include <iostream> // Biblioteca  padrão de I/O
#include <vector>
#include <string> // Para trabalhar fácil com strings
#include "Ant.h"
#include "../ferramentas/Conversor.h"
#include "../ferramentas/Sugeno.h"
#include "../poesh/SistemaHidroeletrico.h"

using namespace std;

// Constantes
#define INVALID -1
#define ALFA 1
#define BETA 1
#define MIN_PHEROMONE 0.01
#define MAX_PHEROMONE 1.0

class ACO {
public:
	// Variáveis públicas
	double bestFitness;
	double iteractionBestFitness;
	vector<vector<double> > bestRoutes;
	int indexBestAnt;
	double worseFitness;
	double iteractionWorseFitness;
	vector<vector<double> > worseRoutes;

	// Construtor
	ACO(int populationSize, int plantSize, int intervalSize, int valueSize,
			int maxIterationSize, double pheromoneRate, double evaporationRate,
			double positiveConstant,
			SistemaHidroeletrico* sistemaHidroeletrico);

	// Métodos públicos
	void calculateSolution();

private:
	// Variáveis privadas
	int iteration;
	int bestRouteAt;
	int populationSize;
	int plantSize;
	int intervalSize;
	int valueSize;
	int maxIterationSize;
	double pheromoneRate;
	double evaporationRate;
	double positiveConstant;
	vector<vector<vector<double> > > pheromoneLinks;
	vector<Ant> ants;
	Conversor conversor;
	Sugeno sugeno;
	SistemaHidroeletrico* sistemaHidroeletrico;
	// Métodos privados
	void initializeAnts();
	void seedInitialPheromone();
	void buildSolutions();
	double getValue(int position);
	void checkBestSolution();
	double calculateFitness(vector<vector<double> > routes);
	void pheromoneEvaporates();
	void updatePheromone();
	double desnormalizarVolume(double valor, double volumeMinimo,
			double volumeMaximo);
	void desnormalizarRotas();
	void resetBestRoute();
	int getPosicao(double value);
};

#endif /* ACO_H_ */
