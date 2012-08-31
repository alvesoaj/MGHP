/*
 * Polinomio.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "Polinomio.h"

int Polinomio::getGrau() {
	return this->coeficientes.size();
}

double Polinomio::calcularValor(double volume) {
	double valor = 0.0;
	for (int i = 0; i < this->getGrau(); i++) {
		valor += this->coeficientes.at(i) * volume;
	}
	return valor;
}
