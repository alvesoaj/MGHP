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
#include "HidroeletricaReservatorio.h"
//
class SistemaHidroeletrico {
private:
	Conversor conversor;
	std::vector<HidroeletricaReservatorio*> usinas;

public:
	SistemaHidroeletrico();

	bool adicionarUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);
	bool removerUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);

	double calcularAlturaQuedaLiquidaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularEngolimentoUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularGeracaoHidraulicaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);
};

#endif /* SISTEMAHIDROELETRICO_H_ */
