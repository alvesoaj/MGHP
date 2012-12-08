/*
 * Ant.h
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#ifndef ANT_H_
#define ANT_H_

// Importando bibliotecas necessárias
#include <vector>
using std::vector;

class Ant {
public:
	// Variáveis
	vector<vector<double> > routes;

	// Construtor
	Ant(int id, int routeAmount, int routeSize);
	// Métodos
	int getID();
	void incrasePosition(int plantIndex);
	int getPosition(int plantIndex);
	void initSearch();
	double getFitness();
	void setFitness(double fitness);
	vector<vector<double> > getRoutes();

private:
	// Variáveis
	int id;
	int routeAmount;
	int routeSize;
	vector<int> position;
	double fitness;
};

#endif /* ANT_H_ */
