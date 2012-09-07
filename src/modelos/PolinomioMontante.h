/*
 * PolinomioMontante.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef POLINOMIOMONTANTE_H_
#define POLINOMIOMONTANTE_H_

#include <vector>
#include "Polinomio.h"

class PolinomioMontante: public Polinomio {
public:
	// Métodos da classe Polinomio de Montante
	PolinomioMontante();
	PolinomioMontante(std::vector<double> coeficientes);
};

#endif /* POLINOMIOMONTANTE_H_ */
