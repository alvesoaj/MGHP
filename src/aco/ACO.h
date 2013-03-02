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
#include "Ant.h"
#include "../ferramentas/Conversor.h"
#include "../poesh/SistemaHidroeletrico.h"
#include "../fuzzy/FuzzyRule.h"
#include "../fuzzy/FuzzyComposition.h"
#include "../fuzzy/Fuzzy.h"
#include "../fuzzy/FuzzyRuleConsequent.h"
#include "../fuzzy/FuzzyOutput.h"
#include "../fuzzy/FuzzyInput.h"
#include "../fuzzy/FuzzyIO.h"
#include "../fuzzy/FuzzySet.h"
#include "../fuzzy/FuzzyRuleAntecedent.h"

using std::vector;

// Constantes
#define INVALID -1
#define ALFA 3
#define BETA 1

class ACO {
public:
	// Variáveis públicas
	double bestFitness;
	vector<vector<double> > bestRoutes;
	int indexBestAnt;
	double worseFitness;
	vector<vector<double> > worseRoutes;
	Fuzzy* fuzzy;
	FuzzyInput* valorEAS;
	FuzzySet* muitoBaixa;
	FuzzySet* baixa;
	FuzzySet* media;
	FuzzySet* alta;
	FuzzySet* muitoAlta;
	FuzzyOutput* output1;
	FuzzyOutput* output2;
	FuzzyOutput* output3;
	FuzzyOutput* output4;
	FuzzyOutput* output5;
	FuzzySet* powerOf1;
	FuzzySet* powerOf2;
	FuzzySet* powerOf3;
	FuzzySet* powerOf4;
	FuzzySet* powerOf5;
	FuzzyRuleAntecedent* ifEASMuitoBaixa;
	FuzzyRuleAntecedent* ifEASBaixa;
	FuzzyRuleAntecedent* ifEASMedia;
	FuzzyRuleAntecedent* ifEASAlta;
	FuzzyRuleAntecedent* ifEASMuitoAlta;
	FuzzyRuleConsequent* thenSetPowerOf1;
	FuzzyRuleConsequent* thenSetPowerOf2;
	FuzzyRuleConsequent* thenSetPowerOf3;
	FuzzyRuleConsequent* thenSetPowerOf4;
	FuzzyRuleConsequent* thenSetPowerOf5;
	FuzzyRule* fuzzyRule1;
	FuzzyRule* fuzzyRule2;
	FuzzyRule* fuzzyRule3;
	FuzzyRule* fuzzyRule4;
	FuzzyRule* fuzzyRule5;

	// Construtor
	ACO(int populationSize, int plantSize, int intervalSize, int valueSize,
			int maxIterationSize, double pheromoneRate, double evaporationRate,
			double positiveConstant,
			SistemaHidroeletrico* sistemaHidroeletrico);

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
	SistemaHidroeletrico* sistemaHidroeletrico;
	double a[2][5];
	double b[2][5];
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
	double calcularVolumeHeuristica(int usinaIndice,
			double energiaArmazenadaSistemaNormalizada);
	int getPosicao(double value);
};

#endif /* ACO_H_ */
