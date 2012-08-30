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
public:
	// Atributos da classe Usina Hidroeletrica a Fio D'Água
	double volumeOperativo;
	double volumeMontante;
	// Métodos da classe Usina Hidroeletrica a Fio D'Água
	HidroeletricaFioDaAgua(unsigned int codigo, std::string nome);
};

#endif /* HIDROELETRICAFIODAAGUA_H_ */
