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
		HidroeletricaReservatorio* usinaHidroeletrica) {
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
		HidroeletricaReservatorio* usinaHidroeletrica) {
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

double SistemaHidroeletrico::calcularAlturaQuedaLiquidaUsina(
		unsigned int codigo, double volume, double vazaoDefluente) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			double nivelMontante = this->usinas.at(i)->calcularNivelMontante(
					volume);

			double nivelJusante = this->usinas.at(i)->calcularNivelJusante(
					vazaoDefluente);

			double altuaraQuedaBruta =
					this->usinas.at(i)->calcularAlturaQuedaBruta(nivelMontante,
							nivelJusante);

			double perdaCarga = this->usinas.at(i)->calcularPerdaCarga(
					altuaraQuedaBruta);

			return this->usinas.at(i)->calcularAlturaQuedaLiquida(
					altuaraQuedaBruta, perdaCarga);
		}
	}
	return 0.0;

}

double SistemaHidroeletrico::calcularEngolimentoUsina(unsigned int codigo,
		double volume, double vazaoDefluente, double tolerancia) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->calcularEngolimento(volume,
					vazaoDefluente, tolerancia);
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::calcularGeracaoHidraulicaUsina(unsigned int codigo,
		double volume, double vazaoDefluente, double tolerancia) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			double nivelMontante = this->usinas.at(i)->calcularNivelMontante(
					volume);

			double nivelJusante = this->usinas.at(i)->calcularNivelJusante(
					vazaoDefluente);

			double altuaraQuedaBruta =
					this->usinas.at(i)->calcularAlturaQuedaBruta(nivelMontante,
							nivelJusante);

			double perdaCarga = this->usinas.at(i)->calcularPerdaCarga(
					altuaraQuedaBruta);

			double alturaQuedaLiquida =
					this->usinas.at(i)->calcularAlturaQuedaLiquida(
							altuaraQuedaBruta, perdaCarga);

			double engolimento = this->usinas.at(i)->calcularEngolimento(volume,
					vazaoDefluente, tolerancia);

			return this->usinas.at(i)->calcularGeracaoHidraulica(
					alturaQuedaLiquida, engolimento);
		}
	}
	return 0.0;
}
