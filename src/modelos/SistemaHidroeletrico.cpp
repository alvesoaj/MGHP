/*
 * SistemaHidroeletrico.cpp
 *
 *  Created on: Sep 4, 2012
 *      Author: zerokol
 */

#include "SistemaHidroeletrico.h"

SistemaHidroeletrico::SistemaHidroeletrico() {
	// TODO Auto-generated constructor stub

}

bool SistemaHidroeletrico::adicionarUsinaHidroeletrica(
		UsinaHidroeletrica* usinaHidroeletrica) {
	bool exists = false;
	for (unsigned int i; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo()
				== usinaHidroeletrica->getCodigo()) {
			exists = true;
			break;
		}
	}
	if (!exists) {
		this->usinas.push_back(usinaHidroeletrica);
		return true;
	} else {
		return false;
	}

}

bool SistemaHidroeletrico::removerUsinaHidroeletrica(
		UsinaHidroeletrica* usinaHidroeletrica) {
	int toDelete = -1;
	for (unsigned int i; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo()
				== usinaHidroeletrica->getCodigo()) {
			toDelete = i;
			break;
		}
	}
	if (toDelete != -1) {
		this->usinas.erase(this->usinas.begin() + toDelete);
		return true;
	} else {
		return false;
	}
}

double SistemaHidroeletrico::calcularEngolimentoUsina(unsigned int codigo,
		double volume, double vazaoDefluente, double tolerancia) {
	double geracaoHidraulica = 0.0;
	UsinaHidroeletrica* usina;
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			usina = this->usinas.at(i);
		}
	}

	if (usina->getCodigo() == codigo) {
		geracaoHidraulica = usina->calcularEngolimento(volume, vazaoDefluente,
				tolerancia);
	}

	return geracaoHidraulica;
}
