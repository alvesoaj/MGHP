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

void Ant::addInRouteAtPositionValue(int routeIndex, int position, double value) {
	this->routes[routeIndex][position] = value;
}

void Ant::initSearch() {
	for (int i = 0; i < this->routeAmount; i++) {
		for (int j = 0; j < this->routeSize; j++) {
			this->routes[i][j] = -1;
		}
	}
	this->fitness = 0.0;
	this->position = 0;
}

double Ant::getFitness() {
	return this->fitness;
}

double Ant::calculateFitness() {
	return this->fitness;
}

vector<vector<double> > Ant::getRoutes() {
	return this->routes;
}
