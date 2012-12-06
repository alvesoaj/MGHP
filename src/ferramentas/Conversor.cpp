/*
 * Conversor.h
 *
 *  Created on: Sep 5, 2012
 *      Author: zerokol
 */

#include "Conversor.h"

Conversor::Conversor() {
	// TODO Auto-generated constructor stub
}

std::string Conversor::double_para_string(double d) {
	std::stringstream out;
	out << d;
	return out.str();
}

double Conversor::string_para_double(const std::string& s) {
	std::istringstream instr(s);
	double val;
	instr >> val;
	return val;
}

int Conversor::get_random_number(int from, int to) {
	// Inicializando o gerador de números randômicos com um seed temporal
	srand(time(0));

	return (from < to) ? (rand() % to) + from : 0;
}
