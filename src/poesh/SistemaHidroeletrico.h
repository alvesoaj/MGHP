/*
 * SistemaHidroeletrico.h
 *
 *  Created on: Sep 4, 2012
 *      Author: zerokol
 */

#ifndef SISTEMAHIDROELETRICO_H_
#define SISTEMAHIDROELETRICO_H_
// Importando bibliotecas úteis
#include <vector> // Para trabalhar com vetores
#include "../ferramentas/Conversor.h"
#include "HidroeletricaReservatorio.h"

using std::vector;

class SistemaHidroeletrico {
private:
	int intervalos;
	int demanda;
	Conversor conversor;
	vector<vector<double> > volumes;
	vector<vector<double> > vazoes;
	vector<HidroeletricaReservatorio*> usinas;

public:
	SistemaHidroeletrico(int intervalos, int demanda,
			vector<vector<double> > volumes, vector<vector<double> > vazoes);

	bool adicionarUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);
	bool removerUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);

	string getNomeUsina(unsigned int codigo);

	double calcularAlturaQuedaLiquidaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularEngolimentoUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularGeracaoHidraulicaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularCustoTotal();
};

#endif /* SISTEMAHIDROELETRICO_H_ */
