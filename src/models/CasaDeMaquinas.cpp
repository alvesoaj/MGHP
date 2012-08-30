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
		ConjuntoUnidadesGeradoras conjuntoUnidadesGeradoras) {
	bool exists = false;
	for (int i; i < this->listaConjuntoUnidadesGeradoras.size(); i++) {
		if (this->listaConjuntoUnidadesGeradoras[i]
				== conjuntoUnidadesGeradoras) {
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
		ConjuntoUnidadesGeradoras conjuntoUnidadesGeradoras) {
	int toDelete = -1;
	for (int i; i < this->listaConjuntoUnidadesGeradoras.size(); i++) {
		if (this->listaConjuntoUnidadesGeradoras[i]
				== conjuntoUnidadesGeradoras) {
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
