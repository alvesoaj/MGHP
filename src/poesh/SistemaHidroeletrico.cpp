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
		if (this->usinas.at(i)->getCodigo() == usinaHidroeletrica->getCodigo()) {
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
		if (this->usinas.at(i)->getCodigo() == usinaHidroeletrica->getCodigo()) {
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

double SistemaHidroeletrico::getVolumeMinimoOperativoUsina(unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->getVolumeMinimoOperativo();
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::getVolumeMaximoOperativoUsina(unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->getVolumeMaximoOperativo();
		}
	}
	return 0.0;
}

HidroeletricaReservatorio* SistemaHidroeletrico::getUsina(unsigned int codigo) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i);
		}
	}
	return NULL;
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

double SistemaHidroeletrico::calcularGeracaoHidraulicaUsina(
		unsigned int codigo, double volume, double vazaoDefluente) {
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
	double geracaoHidraulicaIntervalos[this->intervalos];

	for (int intervalo = 1; intervalo < this->intervalos; intervalo++) {
		double geracaoHidraulicaTotal = 0.0;

		for (unsigned int indiceUsina = 0; indiceUsina < this->usinas.size(); indiceUsina++) {

			double geracao_hidraulica = this->calcularGeracaoHidraulicaUsina(
					indiceUsina, this->volumes[indiceUsina][intervalo],
					this->calcularVazaoAfluente(indiceUsina, intervalo));

			geracaoHidraulicaTotal += geracao_hidraulica;
		}
		geracaoHidraulicaIntervalos[intervalo] = geracaoHidraulicaTotal;
		//cout << "I(" << intervalo << "): " << geracaoHidraulicaTotal << endl;
	}

	double needSum = 0.0;
	for (int i = 0; i < this->intervalos; i++) {
		if (this->demanda > geracaoHidraulicaIntervalos[i]) {
			needSum += pow(this->demanda - geracaoHidraulicaIntervalos[i], 2);
		}
	}

	return needSum / 2.0;
}

double SistemaHidroeletrico::calcularVazaoAfluente(int indiceUsina,
		int intervalo) {
	double vazaoAfluente = 0.0;
	UsinaHidroeletrica* usina = this->getUsina(indiceUsina);
	vector<UsinaHidroeletrica*> usinasMontante = usina->getUsinasMontante();

	if (usinasMontante.size() == 0) {
		vazaoAfluente = this->vazoes[indiceUsina][intervalo - 1];
	} else {
		double vazaoNaturalMontante = 0.0;
		double vazaoDefluenteMontante = 0.0;
		for (unsigned int i = 0; i < usinasMontante.size(); i++) {
			usina = usinasMontante.at(i);
			int indiceUsinaMontante = usina->getCodigo();
			vazaoNaturalMontante += this->vazoes[indiceUsinaMontante][intervalo
					- 1];
			double temp = this->volumes[indiceUsinaMontante][intervalo - 1]
					- this->volumes[indiceUsinaMontante][intervalo];
			if (temp > 0.0) {
				vazaoDefluenteMontante += temp;
			}
		}
		double vazaoIncremental = this->vazoes[indiceUsina][intervalo - 1]
				- vazaoNaturalMontante;
		vazaoAfluente = vazaoIncremental + vazaoDefluenteMontante;
	}
	return vazaoAfluente;
}