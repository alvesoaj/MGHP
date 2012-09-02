/*
 * HidroeletricaFioDaAgua.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "HidroeletricaFioDaAgua.h"

HidroeletricaFioDaAgua::HidroeletricaFioDaAgua(unsigned int codigo,
		std::string nome) {
	this->codigo = codigo;
	this->nome = nome;
}

double HidroeletricaFioDaAgua::getVolumeOperativo() {
	return volumeOperativo;
}

void HidroeletricaFioDaAgua::setVolumeOperativo(double volumeOperativo) {
	this->volumeOperativo = volumeOperativo;
}

void HidroeletricaFioDaAgua::setNivelMontante(double nivelMontante) {
	this->nivelMontante = nivelMontante;
}

double HidroeletricaFioDaAgua::calcularNivelMontante(double volume) {
	return this->nivelMontante;
}
