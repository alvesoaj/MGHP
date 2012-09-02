/*
 * HidroeletricaFioDaAgua.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef HIDROELETRICAFIODAAGUA_H_
#define HIDROELETRICAFIODAAGUA_H_

#include "UsinaHidroeletrica.h"

class HidroeletricaFioDaAgua: public UsinaHidroeletrica {
private:
	// Atributos da classe Usina Hidroeletrica a Fio D'Água
	double volumeMontante;
	double volumeOperativo;
	double nivelMontante;

public:
	// Métodos da classe Usina Hidroeletrica a Fio D'Água
	HidroeletricaFioDaAgua(unsigned int codigo, std::string nome);

	double getVolumeMontante();
	double getVolumeOperativo();
	void setVolumeMontante(double volumeMontante);
	void setVolumeOperativo(double volumeOperativo);
	void setNivelMontante(double nivelMontante);

	double calcularNivelMontante(double volume);
};

#endif /* HIDROELETRICAFIODAAGUA_H_ */
