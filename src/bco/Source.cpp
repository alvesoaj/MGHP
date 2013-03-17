/*
 * Source.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: zerokol
 */

#include "Source.h"

// Construtor
Source::Source(int index, int plantSize, int intervalSize) {
	this->index = index;
	this->plantSize = plantSize;
	this->intervalSize = intervalSize;

	this->initSearch();
}

void Source::increasePosition(int plantIndex) {
	this->position[plantIndex] += 1;
}

int Source::getPosition(int plantIndex) {
	return this->position[plantIndex];
}

void Source::initSearch() {
	vector<vector<double> > tempSolutions;
	vector<int> tempPosition;
	for (int p = 0; p < this->plantSize; p++) {
		vector<double> tempRoute;
		// Iniciar com o reservatório cheio, 100%
		tempRoute.push_back(1.0);
		for (int v = 1; v < this->intervalSize; v++) {
			double r = conversor.get_random_number();
			tempRoute.push_back(r);
		}
		tempSolutions.push_back(tempRoute);
		// a busca inicia na posição 1
		tempPosition.push_back(1);
	}
	this->solutions = tempSolutions;
	this->fitness = 0.0;
	this->trail = 0;
	this->probabilitie = 0.0;
	this->position = tempPosition;
}

double Source::getFitness() {
	return this->fitness;
}

void Source::setFitness(double f) {
	this->fitness = f;
}

int Source::getTrail() {
	return this->trail;
}

void Source::setTrail(int t) {
	this->trail = t;
}

double Source::getProbabilitie() {
	return this->probabilitie;
}

void Source::setProbabilitie(double p) {
	this->probabilitie = p;
}
