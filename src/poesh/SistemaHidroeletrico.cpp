/*
 * SistemaHidroeletrico.cpp
 *
 *  Created on: Sep 4, 2012
 *      Author: zerokol
 */

#include "SistemaHidroeletrico.h"

SistemaHidroeletrico::SistemaHidroeletrico(int intervalos, int demanda) {
	this->intervalos = intervalos;
	this->demanda = demanda;
}

SistemaHidroeletrico::SistemaHidroeletrico(int intervalos, int demanda,
		vector<vector<double> > volumes, vector<vector<double> > vazoes) {
	this->intervalos = intervalos;
	this->demanda = demanda;
	this->volumes = volumes;
	this->vazoes = vazoes;
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

string SistemaHidroeletrico::getNomeUsina(unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->getNome();
		}
	}
	return "Indefinido";
}

double SistemaHidroeletrico::getVolumeMinimoOperativoUsina(
		unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->getVolumeMinimoOperativo();
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::getVolumeMaximoOperativoUsina(
		unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->getVolumeMaximoOperativo();
		}
	}
	return 0.0;
}

void SistemaHidroeletrico::setVolumes(vector<vector<double> > volumes) {
	this->volumes = volumes;
}

void SistemaHidroeletrico::setVazoes(vector<vector<double> > vazoes) {
	this->vazoes = vazoes;
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
		double volume, double vazaoDefluente) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->calcularEngolimento(volume,
					vazaoDefluente);
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::calcularGeracaoHidraulicaUsina(unsigned int codigo,
		double volume, double vazaoDefluente) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			double engolimento = this->calcularEngolimentoUsina(codigo, volume,
					vazaoDefluente);
			double alturaQuedaLiquida = this->calcularAlturaQuedaLiquidaUsina(
					codigo, volume, vazaoDefluente);
			return this->usinas.at(i)->calcularGeracaoHidraulica(
					alturaQuedaLiquida, vazaoDefluente, engolimento);
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::calcularCustoTotal() {
	double geracao_hidraulica_intervalos[this->intervalos];

	for (int intervalo = 0; intervalo < this->intervalos; intervalo++) {
		double geracao_hidraulica_total = 0.0;

		for (unsigned int indice_usina = 0; indice_usina < this->usinas.size();
				indice_usina++) {

			double geracao_hidraulica = this->calcularGeracaoHidraulicaUsina(
					indice_usina, this->volumes[indice_usina][intervalo],
					this->vazoes[indice_usina][intervalo]);

			geracao_hidraulica_total += geracao_hidraulica;
		}

		geracao_hidraulica_intervalos[intervalo] = geracao_hidraulica_total;
	}

	double needSum = 0.0;
	for (int i = 0; i < this->intervalos; i++) {
		if (this->demanda > geracao_hidraulica_intervalos[i]) {
			needSum += pow(this->demanda - geracao_hidraulica_intervalos[i], 2);
		}
	}

	return needSum / 2.0;
}
