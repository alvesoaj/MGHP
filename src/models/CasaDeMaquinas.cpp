/*
 * CasaDeMaquinas.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "CasaDeMaquinas.h"

CasaDeMaquinas::CasaDeMaquinas() {
	// TODO Auto-generated constructor stub
}

bool CasaDeMaquinas::adicionarConjuntoUnidadesGeradoras(
		ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradoras) {
	bool exists = false;
	for (unsigned int i; i < this->listaConjuntoUnidadesGeradoras.size(); i++) {
		if (this->listaConjuntoUnidadesGeradoras.at(i)->getId()
				== conjuntoUnidadesGeradoras->getId()) {
			exists = true;
			break;
		}
	}
	if (!exists) {
		this->listaConjuntoUnidadesGeradoras.push_back(
				conjuntoUnidadesGeradoras);
		return true;
	} else {
		return false;
	}
}

bool CasaDeMaquinas::removerConjuntoUnidadesGeradoras(
		ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradoras) {
	int toDelete = -1;
	for (unsigned int i; i < this->listaConjuntoUnidadesGeradoras.size(); i++) {
		if (this->listaConjuntoUnidadesGeradoras.at(i)->getId()
				== conjuntoUnidadesGeradoras->getId()) {
			toDelete = i;
			break;
		}
	}
	if (toDelete != -1) {
		this->listaConjuntoUnidadesGeradoras.erase(
				this->listaConjuntoUnidadesGeradoras.begin() + toDelete);
		return true;
	} else {
		return false;
	}
}

double CasaDeMaquinas::calcularEngolimentoEfetivoTotal() {
	double engolimentoEfetivoTotal = 0.0;
	for (unsigned int i = 0; i < this->listaConjuntoUnidadesGeradoras.size();
			i++) {
		engolimentoEfetivoTotal +=
				this->listaConjuntoUnidadesGeradoras.at(i)->getEngolimentoEfetivo();
	}
	return engolimentoEfetivoTotal;
}

double CasaDeMaquinas::calcularEngolimentoMaximoTotal(
		double alturaQuedaLiquida) {
	double engolimentoMaximoTotal = 0.0;
	for (unsigned int i = 0; i < this->listaConjuntoUnidadesGeradoras.size();
			i++) {
		engolimentoMaximoTotal +=
				this->listaConjuntoUnidadesGeradoras.at(i)->calcularEngolimentoMaximo(
						alturaQuedaLiquida);
	}
	return engolimentoMaximoTotal;
}
