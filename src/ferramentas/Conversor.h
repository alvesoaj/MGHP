/*
 * Conversor.h
 *
 *  Created on: Sep 5, 2012
 *      Author: zerokol
 */

#ifndef CONVERSOR_H_
#define CONVERSOR_H_

// Importando bibliotecas úteis
#include <string> // Para trabalhar fácil com strings
#include <sstream> // Para trabalhar fácil com strings
//
class Conversor {
public:
	// Métodos da classe Conversor
	Conversor();

	std::string double_para_string(double d);
	double string_para_double(const std::string& s);
};

#endif /* CONVERSOR_H_ */