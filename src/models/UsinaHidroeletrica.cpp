/*
 * UsinaHidroeletrica.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "UsinaHidroeletrica.h"

void UsinaHidroeletrica::setCasaDeMaquinas(CasaDeMaquinas casaDeMaquinas) {
	this->casaDeMaquinas = casaDeMaquinas;
}

void UsinaHidroeletrica::setPolinomioJusante(
		PolinomioJusante polinomioJusante) {
	this->polinomioJusante = polinomioJusante;

}

void UsinaHidroeletrica::setUsinaMontante(UsinaHidroeletrica usinaMontante) {
	this->usinaMontante = usinaMontante;
}
