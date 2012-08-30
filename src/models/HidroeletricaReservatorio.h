/*
 * HidroeletricaReservatorio.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef HIDROELETRICARESERVATORIO_H_
#define HIDROELETRICARESERVATORIO_H_

class HidroeletricaReservatorio : public UsinaHidroeletrica {
public:
	// Atributos da classe Usina Hidroeletrica a Reservatório
	double volumeMaximoOperativo;
	double volumeMinimoOperativo;
	double volumeUtil;
	// Métodos da classe Usina Hidroeletrica a Reservatório
	HidroeletricaReservatorio(unsigned int codigo, std::string nome);
};

#endif /* HIDROELETRICARESERVATORIO_H_ */
