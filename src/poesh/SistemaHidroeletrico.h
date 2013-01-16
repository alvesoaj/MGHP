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

using std::vector;

#define Fc 2628000 // Fc = 10⁶/deltaT (Duração em segundos)
class SistemaHidroeletrico {
private:
	int intervalos;
	int demanda;
	Conversor conversor;
	vector<vector<double> > volumes;
	vector<vector<double> > vazoes;
	vector<HidroeletricaReservatorio*> usinas;

public:
	SistemaHidroeletrico(int intervalos, int demanda);

	SistemaHidroeletrico(int intervalos, int demanda,
			vector<vector<double> > volumes, vector<vector<double> > vazoes);

	bool adicionarUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);
	bool removerUsinaHidroeletrica(
			HidroeletricaReservatorio* usinaHidroeletrica);

	string getNomeUsina(unsigned int codigo);

	double getVolumeMinimoOperativoUsina(unsigned int codigo);

	double getVolumeMaximoOperativoUsina(unsigned int codigo);

	HidroeletricaReservatorio* getUsina(unsigned int codigo);

	void setVolumes(vector<vector<double> > volumes);

	void setVazoes(vector<vector<double> > vazoes);

	double calcularAlturaQuedaLiquidaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularAlturaQuedaLiquidaMediaUsina(unsigned int codigo,
			double volumeMedio);

	double calcularEngolimentoUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularGeracaoHidraulicaUsina(unsigned int codigo, double volume,
			double vazaoDefluente);

	double calcularCustoTotal();

	double calcularVazaoAfluente(int indiceUsina, int intervalo);

	double calcularEnergiaArmazenadaSistema(int intervalo);
};

#endif /* SISTEMAHIDROELETRICO_H_ */
