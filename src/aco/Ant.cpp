/*
 * Ant.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#include "Ant.h"

// Implementação do construtor
Ant::Ant(int id, int routeAmount, int routeSize) {
	this->id = id;
	this->routeAmount = routeAmount;
	this->routeSize = routeSize;

	this->initSearch();
}

// Implementação dos métodos
int Ant::getID() {
	return this->id;
}

void Ant::increasePosition(int plantIndex) {
	this->position[plantIndex] += 1;
}

int Ant::getPosition(int plantIndex) {
	return this->position[plantIndex];
}

void Ant::initSearch() {
	vector<vector<double> > tempRoutes;
	vector<int> tempPosition;
	for (int p = 0; p < this->routeAmount; p++) {
		vector<double> tempRoute;
		for (int v = 0; v < this->routeSize; v++) {
			// Iniciar com o reservatório cheio, 100%
			tempRoute.push_back(1.0);
		}
		tempRoutes.push_back(tempRoute);
		tempPosition.push_back(0);
	}
	this->routes = tempRoutes;
	this->fitness = 0.0;
	this->position = tempPosition;
}

double Ant::getFitness() {
	return this->fitness;
}

void Ant::setFitness(double fitness) {
	this->fitness = fitness;
}

vector<vector<double> > Ant::getRoutes() {
	return this->routes;
}
