/*
 * HidroeletricaFioDaAgua.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef HIDROELETRICAFIODAAGUA_H_
#define HIDROELETRICAFIODAAGUA_H_

class HidroeletricaFioDaAgua : public UsinaHidroeletrica {
public:
	// Atributos da classe Usina Hidroeletrica a Fio D'Água
	double volumeOperativo;
	double volumeMontante;
	// Métodos da classe Usina Hidroeletrica a Fio D'Água
	HidroeletricaFioDaAgua();
};

#endif /* HIDROELETRICAFIODAAGUA_H_ */
