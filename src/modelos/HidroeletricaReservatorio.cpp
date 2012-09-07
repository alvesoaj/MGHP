/*
 * HidroeletricaReservatorio.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "HidroeletricaReservatorio.h"

HidroeletricaReservatorio::HidroeletricaReservatorio(unsigned int codigo,
		std::string nome) {
	this->codigo = codigo;
	this->nome = nome;
}

PolinomioMontante* HidroeletricaReservatorio::getPolinomioMontante() {
	return polinomioMontante;
}

double HidroeletricaReservatorio::getVolumeMaximoOperativo() {
	return volumeMaximoOperativo;
}

double HidroeletricaReservatorio::getVolumeMinimoOperativo() {
	return volumeMinimoOperativo;
}

void HidroeletricaReservatorio::setPolinomioMontante(
		PolinomioMontante* polinomioMontante) {
	this->polinomioMontante = polinomioMontante;
}

void HidroeletricaReservatorio::setVolumeMaximoOperativo(
		double volumeMaximoOperativo) {
	this->volumeMaximoOperativo = volumeMaximoOperativo;
}

void HidroeletricaReservatorio::setVolumeMinimoOperativo(
		double volumeMinimoOperativo) {
	this->volumeMinimoOperativo = volumeMinimoOperativo;
}

double HidroeletricaReservatorio::calcularVolumeUtil() {
	return this->volumeMaximoOperativo - this->volumeMinimoOperativo;
}

double HidroeletricaReservatorio::calcularVolumeSeguranca() {
	return this->volumeMaximoMaximorum - this->volumeMaximoOperativo;
}

double HidroeletricaReservatorio::calcularNivelMontante(double volume) {
	return this->polinomioMontante->calcularValor(volume);
}

double HidroeletricaReservatorio::calcularAlturaQuedaBruta(
		double alturaMontante, double alturaJusante) {
	return alturaMontante - alturaJusante;
}

double HidroeletricaReservatorio::calcularPerdaCarga(double alturaQuedaBruta) {
	return this->coeficientePerdaCargaHidraulica * alturaQuedaBruta;
}

double HidroeletricaReservatorio::calcularAlturaQuedaLiquida(
		double alturaQuedaBruta, double perdaCarga) {
	return alturaQuedaBruta - perdaCarga;
}

double HidroeletricaReservatorio::calcularEngolimento(double volume,
		double vazaoDefluente, double tolerancia) {
	double nivelMontante;
	double nivelJusante;
	double vazaoDefluenteBase = vazaoDefluente;
	double altuaraQuedaBruta;
	double perdaCarga;
	double alturaQuedaLiquida;
	double engolimentoEfetivo =
			this->casaDeMaquinas->calcularEngolimentoEfetivoTotal();
	double engolimentoMaximoAtual;
	double engolimentoMaximoAnterior = engolimentoEfetivo;
	// double vazaoTurbinada = engolimentoEfetivo;
	bool convergencia = false;

	do {
		nivelMontante = this->calcularNivelMontante(volume);

		nivelJusante = this->calcularNivelJusante(vazaoDefluente);

		altuaraQuedaBruta = this->calcularAlturaQuedaBruta(nivelMontante,
				nivelJusante);

		perdaCarga = this->calcularPerdaCarga(altuaraQuedaBruta);

		alturaQuedaLiquida = this->calcularAlturaQuedaLiquida(altuaraQuedaBruta,
				perdaCarga);

		engolimentoMaximoAtual =
				this->casaDeMaquinas->calcularEngolimentoMaximoTotal(
						alturaQuedaLiquida);

		if (engolimentoMaximoAtual >= vazaoDefluenteBase) {
			//engolimentoMaximoUsinaAnterior
			vazaoDefluente = engolimentoMaximoAtual;
			// vazaoTurbinada = engolimentoMaximoAtual;
		} else {
			// vazaoTurbinada = engolimentoMaximoAtual;
		}

		// Teste de Convergência
		if (fabs(engolimentoMaximoAtual - engolimentoMaximoAnterior)
				< tolerancia) {
			convergencia = true;
		} else {
			convergencia = false;
			engolimentoMaximoAnterior = engolimentoMaximoAtual;
		}
	} while (convergencia == false);

	return engolimentoMaximoAtual;
}

double HidroeletricaReservatorio::calcularGeracaoHidraulica(
		double alturaQuedaLiquida, double engolimento) {
	double geracaoHidraulica = this->coeficienteProdutibilidadeEspecifica
			* alturaQuedaLiquida * engolimento;
	return geracaoHidraulica;
}

