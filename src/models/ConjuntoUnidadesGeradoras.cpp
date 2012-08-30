/*
 * ConjuntoUnidadesGeradoras.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "ConjuntoUnidadesGeradoras.h"

ConjuntoUnidadesGeradoras::ConjuntoUnidadesGeradoras(unsigned int id,
		unsigned int numeroUnidadesGeradoras, double potenciaEfetiva,
		double engolimentoEfetivo, double alutraQuedaEfetiva, int tipoTurbinasHidraulicas) {
	this->id = id;
	this->numeroUnidadesGeradoras = numeroUnidadesGeradoras;
	this->potenciaEfetiva = potenciaEfetiva;
	this->engolimentoEfetivo = engolimentoEfetivo;
	this->alutraQuedaEfetiva = alutraQuedaEfetiva;
	this->tipoTurbinasHidraulicas = tipoTurbinasHidraulicas;
}

