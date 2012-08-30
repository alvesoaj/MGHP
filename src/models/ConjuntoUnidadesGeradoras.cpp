/*
 * ConjuntoUnidadesGeradoras.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "ConjuntoUnidadesGeradoras.h"

ConjuntoUnidadesGeradoras::ConjuntoUnidadesGeradoras(unsigned int id,
		unsigned int numeroUnidadesGeradoras, double potenciaEfetiva,
		double engolimentoEfetivo, double alutraQuedaEfetiva,
		int tipoTurbinasHidraulicas) {
	this->id = id;
	this->numeroUnidadesGeradoras = numeroUnidadesGeradoras;
	this->potenciaEfetiva = potenciaEfetiva;
	this->engolimentoEfetivo = engolimentoEfetivo;
	this->alutraQuedaEfetiva = alutraQuedaEfetiva;
	this->tipoTurbinasHidraulicas = tipoTurbinasHidraulicas;
}

unsigned int ConjuntoUnidadesGeradoras::getId() const {
	return id;
}

double ConjuntoUnidadesGeradoras::getAlutraQuedaEfetiva() const {
	return alutraQuedaEfetiva;
}

double ConjuntoUnidadesGeradoras::getEngolimentoEfetivo() const {
	return engolimentoEfetivo;
}

unsigned int ConjuntoUnidadesGeradoras::getNumeroUnidadesGeradoras() const {
	return numeroUnidadesGeradoras;
}

double ConjuntoUnidadesGeradoras::getPotenciaEfetiva() const {
	return potenciaEfetiva;
}

int ConjuntoUnidadesGeradoras::getTipoTurbinasHidraulicas() const {
	return tipoTurbinasHidraulicas;
}

void ConjuntoUnidadesGeradoras::setAlutraQuedaEfetiva(double alutraQuedaEfetiva) {
	this->alutraQuedaEfetiva = alutraQuedaEfetiva;
}

void ConjuntoUnidadesGeradoras::setEngolimentoEfetivo(double engolimentoEfetivo) {
	this->engolimentoEfetivo = engolimentoEfetivo;
}

void ConjuntoUnidadesGeradoras::setNumeroUnidadesGeradoras(
		unsigned int numeroUnidadesGeradoras) {
	this->numeroUnidadesGeradoras = numeroUnidadesGeradoras;
}

void ConjuntoUnidadesGeradoras::setPotenciaEfetiva(double potenciaEfetiva) {
	this->potenciaEfetiva = potenciaEfetiva;
}

void ConjuntoUnidadesGeradoras::setTipoTurbinasHidraulicas(
		int tipoTurbinasHidraulicas) {
	this->tipoTurbinasHidraulicas = tipoTurbinasHidraulicas;
}
