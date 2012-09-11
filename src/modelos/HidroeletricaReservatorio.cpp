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
		double vazaoDefluente) {
	bool convergencia = false;
	double tolerancia = 1.0;
	double nivelMontante = this->calcularNivelMontante(volume);
	double vazaoDefluenteBase = vazaoDefluente;
	// double vazaoTurbinada = engolimentoEfetivo;
	// double vazaoVertida = 0.0;
	double nivelJusante = this->calcularNivelJusante(vazaoDefluente);
	double altuaraQuedaBruta = this->calcularAlturaQuedaBruta(nivelMontante,
			nivelJusante);
	double perdaCarga = this->calcularPerdaCarga(altuaraQuedaBruta);
	double alturaQuedaLiquida = this->calcularAlturaQuedaLiquida(
			altuaraQuedaBruta, perdaCarga);
	double engolimentoEfetivo =
			this->casaDeMaquinas->calcularEngolimentoEfetivoTotal();
	double engolimentoMaximoAnterior = engolimentoEfetivo;
	double engolimentoMaximoAtual =
			this->casaDeMaquinas->calcularEngolimentoMaximoTotal(
					alturaQuedaLiquida);

	do {
		if (engolimentoMaximoAtual >= vazaoDefluenteBase) {
			vazaoDefluente = engolimentoMaximoAtual;
			// vazaoTurbinada = engolimentoMaximoAtual;
		} else {
			// vazaoTurbinada = engolimentoMaximoAtual;
			// vazaoVertida = vazaoDefluente - vazaoTurbinada;
		}

		cout << "x: " + conversor.double_para_string(volume) << endl;
		cout << "u: " + conversor.double_para_string(vazaoDefluente) << endl;

		nivelMontante = this->calcularNivelMontante(volume);

		cout << "hm: " + conversor.double_para_string(nivelMontante) << endl;

		nivelJusante = this->calcularNivelJusante(vazaoDefluente);

		cout << "hj: " + conversor.double_para_string(nivelJusante) << endl;

		altuaraQuedaBruta = this->calcularAlturaQuedaBruta(nivelMontante,
				nivelJusante);

		cout << "hb: " + conversor.double_para_string(altuaraQuedaBruta)
				<< endl;

		perdaCarga = this->calcularPerdaCarga(altuaraQuedaBruta);

		cout << "hp: " + conversor.double_para_string(perdaCarga) << endl;

		alturaQuedaLiquida = this->calcularAlturaQuedaLiquida(altuaraQuedaBruta,
				perdaCarga);

		cout << "hl: " + conversor.double_para_string(alturaQuedaLiquida)
				<< endl;

		engolimentoMaximoAtual =
				this->casaDeMaquinas->calcularEngolimentoMaximoTotal(
						alturaQuedaLiquida);

		cout << "qmax: " + conversor.double_para_string(engolimentoMaximoAtual)
				<< endl;

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

