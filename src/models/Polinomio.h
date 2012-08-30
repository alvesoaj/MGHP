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
public:
	// Atributos da classe Polinomio
	std::vector<double> coeficientes;

	// Métodos da classe Polinomio
	int getGrau();
};

#endif /* POLINOMIO_H_ */
