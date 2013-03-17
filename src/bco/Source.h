/*
 * Source.h
 *
 *  Created on: Mar 16, 2013
 *      Author: zerokol
 */

#ifndef Source_H_
#define Source_H_

// Importando bibliotecas necessárias
#include <vector>
#include "../ferramentas/Conversor.h"

using namespace std;

class Source {
public:
	vector<vector<double> > solutions;

	Source(int index, int plantSize, int intervalSize);
	void increasePosition(int plantIndex);
	int getPosition(int plantIndex);
	void initSearch();
	double getFitness();
	void setFitness(double f);
	int getTrail();
	void setTrail(int t);
	double getProbabilitie();
	void setProbabilitie(double p);

private:
	int index;
	int plantSize;
	int intervalSize;
	double fitness;
	int trail;
	double probabilitie;
	vector<int> position;
	Conversor conversor;
};

#endif /* Bee_H_ */
