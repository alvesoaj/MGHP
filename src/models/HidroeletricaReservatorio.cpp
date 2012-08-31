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

double HidroeletricaReservatorio::getVolumeUtil() {
	return volumeUtil;
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

void HidroeletricaReservatorio::setVolumeUtil(double volumeUtil) {
	this->volumeUtil = volumeUtil;
}

double HidroeletricaReservatorio::calcularAlturaMontante(double volume) {
	return this->polinomioMontante->calcularValor(volume);
}

