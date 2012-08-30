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

double HidroeletricaFioDaAgua::getVolumeMontante() {
	return volumeMontante;
}

double HidroeletricaFioDaAgua::getVolumeOperativo() {
	return volumeOperativo;
}

void HidroeletricaFioDaAgua::setVolumeMontante(double volumeMontante) {
	this->volumeMontante = volumeMontante;
}

void HidroeletricaFioDaAgua::setVolumeOperativo(double volumeOperativo) {
	this->volumeOperativo = volumeOperativo;
}
