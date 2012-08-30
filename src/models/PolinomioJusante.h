/*
 * PolinomioJusante.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef POLINOMIOJUSANTE_H_
#define POLINOMIOJUSANTE_H_

#include <vector>
#include "Polinomio.h"

class PolinomioJusante : public Polinomio {
public:
	// Atributos da classe Polinomio de Jusante
	// Métodos da classe Polinomio de Jusante
	PolinomioJusante();
	PolinomioJusante(std::vector<double> coeficientes);
};

#endif /* POLINOMIOJUSANTE_H_ */
