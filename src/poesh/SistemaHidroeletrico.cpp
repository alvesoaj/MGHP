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
	bool existe = false;
	for (unsigned int i; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == usinaHidroeletrica->getCodigo()) {
			existe = true;
			break;
		}
	}
	if (!existe) {
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

double SistemaHidroeletrico::calcularAlturaQuedaLiquidaMediaUsina(
		unsigned int codigo, double volumeMedio) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			double nivelMontanteMedio =
					this->usinas.at(i)->calcularNivelMontante(volumeMedio);

			double nivelJusanteMedio =
					this->usinas.at(i)->getNivelMedioJusante();

			double altuaraQuedaBrutaMedia =
					this->usinas.at(i)->calcularAlturaQuedaBruta(
							nivelMontanteMedio, nivelJusanteMedio);

			double perdaCargaMedia = this->usinas.at(i)->calcularPerdaCarga(
					altuaraQuedaBrutaMedia);

			return this->usinas.at(i)->calcularAlturaQuedaLiquida(
					altuaraQuedaBrutaMedia, perdaCargaMedia);
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::calcularEngolimentoMaximoUsina(
		unsigned int codigo, double volume, double vazaoDefluente) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			return this->usinas.at(i)->calcularEngolimentoMaximo(volume,
					vazaoDefluente);
		}
	}
	return 0.0;
}

double SistemaHidroeletrico::calcularGeracaoHidraulicaUsina(
		unsigned int codigo, double volume, double vazaoDefluente) {
	for (unsigned int i = 0; i < this->usinas.size(); i++) {
		if (this->usinas.at(i)->getCodigo() == codigo) {
			double engolimentoMaximo = this->calcularEngolimentoMaximoUsina(
					codigo, volume, vazaoDefluente);
			double engolimento = 0.0;

			if (engolimentoMaximo >= vazaoDefluente) {
				engolimento = vazaoDefluente;
			} else {
				engolimento = engolimentoMaximo;
			}
			/*
			 if (true) {
			 cout << "qMax(" << i << "): " << engolimentoMaximo << endl;
			 cout << "q(" << i << "): " << engolimento << endl;
			 }
			 */
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
			double volumeMedio = (this->volumes[indiceUsina][intervalo - 1]
					+ this->volumes[indiceUsina][intervalo]) / 2.0;
			double geracao_hidraulica = this->calcularGeracaoHidraulicaUsina(
					indiceUsina, volumeMedio,
					this->calcularVazaoDefluente(indiceUsina, intervalo));

			geracaoHidraulicaTotal += geracao_hidraulica;

			// cout << "gh(" << intervalo << ", " << indiceUsina << "): " << geracao_hidraulica << endl;
		}
		geracaoHidraulicaIntervalos[intervalo] = geracaoHidraulicaTotal;

		// cout << "ghTOT(" << intervalo << "): " << geracaoHidraulicaTotal << endl;
	}

	double needSum = 0.0;
	for (int i = 1; i < this->intervalos; i++) {
		double geracaoComplementar;
		if (this->demanda >= geracaoHidraulicaIntervalos[i]) {
			geracaoComplementar = pow(
					this->demanda - geracaoHidraulicaIntervalos[i], 2);
		} else {
			geracaoComplementar = 0.0;
		}
		// cout << "GC(" << i << "): " << geracaoComplementar << endl;
		needSum += geracaoComplementar;
	}

	return needSum / 2.0;
}

double SistemaHidroeletrico::calcularVazaoAfluenteIncremental(int indiceUsina,
		int intervalo) {
	double vazaoAfluenteIncremental = 0.0;
	double vazaoNaturalMontante = 0.0;
	UsinaHidroeletrica* usina = this->getUsina(indiceUsina);
	vector<UsinaHidroeletrica*> usinasMontante = usina->getUsinasMontante();

	for (unsigned int i = 0; i < usinasMontante.size(); i++) {
		usina = usinasMontante.at(i);
		int indiceUsinaMontante = usina->getCodigo();
		vazaoNaturalMontante
				+= this->vazoes[indiceUsinaMontante][intervalo - 1];
	}
	vazaoAfluenteIncremental = this->vazoes[indiceUsina][intervalo - 1]
			- vazaoNaturalMontante;
	/*
	 if (indiceUsina > -1) {
	 cout << "yINC(" << intervalo << ", " << indiceUsina << "): "
	 << vazaoAfluenteIncremental << endl;
	 }
	 */
	return vazaoAfluenteIncremental;
}

double SistemaHidroeletrico::calcularVazaoDefluente(int indiceUsina,
		int intervalo) {
	double vazaoDefluente = 0.0;
	double vazaoDefluenteMontante = 0.0;
	UsinaHidroeletrica* usina = this->getUsina(indiceUsina);
	vector<UsinaHidroeletrica*> usinasMontante = usina->getUsinasMontante();

	for (unsigned int i = 0; i < usinasMontante.size(); i++) {
		usina = usinasMontante.at(i);
		int indiceUsinaMontante = usina->getCodigo();
		vazaoDefluenteMontante += this->calcularVazaoDefluente(
				indiceUsinaMontante, intervalo);
	}

	double vazaoAfluenteIncremental = this->calcularVazaoAfluenteIncremental(
			indiceUsina, intervalo);

	vazaoDefluente = vazaoAfluenteIncremental + vazaoDefluenteMontante
			+ ((this->volumes[indiceUsina][intervalo - 1]
					- this->volumes[indiceUsina][intervalo]) / 2.628);
	/*
	 if (indiceUsina > -1) {
	 cout << "u(" << intervalo << ", " << indiceUsina << "): "
	 << vazaoDefluente << endl;
	 }
	 */
	return vazaoDefluente;
}

double SistemaHidroeletrico::calcularEnergiaArmazenadaSistema(int intervalo) {
	HidroeletricaReservatorio* usina;
	double somaProdutividadeMedia = 0.0;
	double produto = 0.0;

	for (int indiceUsina = (this->usinas.size() - 1); indiceUsina >= 0; indiceUsina--) {
		usina = this->getUsina(indiceUsina);

		double volumeMedio = (this->volumes[indiceUsina][intervalo - 1]
				+ this->volumes[indiceUsina][intervalo]) / 2.0;

		double alturaQuedaLiquidaMedia = calcularAlturaQuedaLiquidaMediaUsina(
				usina->getCodigo(), volumeMedio);

		double produtividadeMedia =
				usina->getCoeficienteProdutibilidadeEspecifica()
						* alturaQuedaLiquidaMedia;

		somaProdutividadeMedia += produtividadeMedia;

		double diferenca = this->volumes[indiceUsina][intervalo]
				- usina->getVolumeMinimoOperativo();

		produto += somaProdutividadeMedia * diferenca;
	}

	return Fc * produto;
}

double SistemaHidroeletrico::calcularEnergiaArmazenadaSistemaMaxima() {
	HidroeletricaReservatorio* usina;
	double somaProdutividadeMedia = 0.0;
	double produto = 0.0;

	for (int indiceUsina = (this->usinas.size() - 1); indiceUsina >= 0; indiceUsina--) {
		usina = this->getUsina(indiceUsina);

		double volumeMedio = usina->getVolumeMaximoOperativo();

		double alturaQuedaLiquidaMedia = calcularAlturaQuedaLiquidaMediaUsina(
				usina->getCodigo(), volumeMedio);

		double produtividadeMedia =
				usina->getCoeficienteProdutibilidadeEspecifica()
						* alturaQuedaLiquidaMedia;

		somaProdutividadeMedia += produtividadeMedia;

		double diferenca = usina->getVolumeMaximoOperativo()
				- usina->getVolumeMinimoOperativo();

		produto += somaProdutividadeMedia * diferenca;
	}

	return Fc * produto;
}

double SistemaHidroeletrico::calcularEnergiaArmazenadaSistemaMinima() {
	return 0.0;
}
