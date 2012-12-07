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

void Ant::incrasePosition() {
	this->position += 1;
}

int Ant::getPosition() {
	return this->position;
}

void Ant::addInRouteAtPositionValue(int routeIndex, int position,
		double value) {
	this->routes[routeIndex][position] = value;
}

void Ant::initSearch() {
	vector<vector<double> > tempRoutes;
	for (int i = 0; i < this->routeAmount; i++) {
		vector<double> tempRoute;
		for (int j = 0; j < this->routeSize; j++) {
			tempRoute.push_back(-1);
		}
		tempRoutes.push_back(tempRoute);
	}
	this->routes = tempRoutes;
	this->fitness = 0.0;
	this->position = 0;
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
