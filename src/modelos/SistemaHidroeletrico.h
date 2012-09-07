/*
 * SistemaHidroeletrico.h
 *
 *  Created on: Sep 4, 2012
 *      Author: zerokol
 */

#ifndef SISTEMAHIDROELETRICO_H_
#define SISTEMAHIDROELETRICO_H_
// Importando bibliotecas úteis
#include <iostream> // Biblioteca  padrão de I/O
#include <vector> // Para trabalhar com vetores
#include "../ferramentas/Conversor.h"
#include "UsinaHidroeletrica.h"
//
class SistemaHidroeletrico {
private:
	Conversor conversor;
	std::vector<UsinaHidroeletrica*> usinas;

public:
	SistemaHidroeletrico();

	bool adicionarUsinaHidroeletrica(UsinaHidroeletrica* usinaHidroeletrica);
	bool removerUsinaHidroeletrica(UsinaHidroeletrica* usinaHidroeletrica);

	double calcularEngolimentoUsina(unsigned int codigo, double volume,
			double vazaoDefluente, double tolerancia);
};

#endif /* SISTEMAHIDROELETRICO_H_ */
