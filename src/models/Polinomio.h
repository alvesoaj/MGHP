/*
 * Polinomio.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef POLINOMIO_H_
#define POLINOMIO_H_

// Importando bibliotecas úteis
#include <vector> // Para trabalhar com vetores

class Polinomio {
protected:
	// Atributos da classe Polinomio
	std::vector<double> coeficientes;

public:
	// Métodos da classe Polinomio
	int getGrau();

	double calcularValor(double volume);
};

#endif /* POLINOMIO_H_ */
