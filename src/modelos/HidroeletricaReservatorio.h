/*
 * HidroeletricaReservatorio.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef HIDROELETRICARESERVATORIO_H_
#define HIDROELETRICARESERVATORIO_H_

#include <math.h> // Para ajudar em calculos matemáticos
#include "UsinaHidroeletrica.h"
#include "PolinomioMontante.h"

class HidroeletricaReservatorio: public UsinaHidroeletrica {
private:
	// Atributos da classe Usina Hidroeletrica a Reservatório
	PolinomioMontante* polinomioMontante;
	double volumeMaximoOperativo;
	double volumeMinimoOperativo;

public:
	// Métodos da classe Usina Hidroeletrica a Reservatório
	HidroeletricaReservatorio(unsigned int codigo, std::string nome);

	PolinomioMontante* getPolinomioMontante();
	double getVolumeMaximoOperativo();
	double getVolumeMinimoOperativo();
	void setPolinomioMontante(PolinomioMontante* polinomioMontante);
	void setVolumeMaximoOperativo(double volumeMaximoOperativo);
	void setVolumeMinimoOperativo(double volumeMinimoOperativo);

	double calcularVolumeUtil();
	double calcularVolumeSeguranca();
	double calcularNivelMontante(double volume);
	double calcularAlturaQuedaBruta(double alturaMontante,
			double alturaJusante);
	double calcularPerdaCarga(double alturaQuedaBruta);
	double calcularAlturaQuedaLiquida(double alturaQuedaBruta,
			double perdaCarga);
	double calcularEngolimento(double volume, double vazaoDefluente, double tolerancia);
	double calcularGeracaoHidraulica(double alturaQuedaLiquida,
			double engolimento);
};

#endif /* HIDROELETRICARESERVATORIO_H_ */