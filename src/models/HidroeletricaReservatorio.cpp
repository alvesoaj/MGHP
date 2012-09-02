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

