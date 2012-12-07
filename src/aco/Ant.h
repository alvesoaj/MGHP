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
	// Construtor
	Ant(int id, int routeAmount, int routeSize);
	// Métodos
	int getID();
	void incrasePosition();
	int getPosition();
	void addInRouteAtPositionValue(int routeIndex, int position, double value);
	void initSearch();
	double getFitness();
	void setFitness(double fitness);
	vector<vector<double> > getRoutes();

private:
	// Variáveis
	int id;
	int routeAmount;
	int routeSize;
	int position;
	double fitness;
	vector<vector<double> > routes;
};

#endif /* ANT_H_ */
