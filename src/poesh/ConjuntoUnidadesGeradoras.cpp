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

unsigned int ConjuntoUnidadesGeradoras::getId() {
	return this->id;
}

double ConjuntoUnidadesGeradoras::getAlutraQuedaEfetiva() {
	return this->alutraQuedaEfetiva;
}

double ConjuntoUnidadesGeradoras::getEngolimentoEfetivo() {
	return this->engolimentoEfetivo;
}

unsigned int ConjuntoUnidadesGeradoras::getNumeroUnidadesGeradoras() {
	return this->numeroUnidadesGeradoras;
}

double ConjuntoUnidadesGeradoras::getPotenciaEfetiva() {
	return this->potenciaEfetiva;
}

int ConjuntoUnidadesGeradoras::getTipoTurbinasHidraulicas() {
	return this->tipoTurbinasHidraulicas;
}

void ConjuntoUnidadesGeradoras::setAlutraQuedaEfetiva(
		double alutraQuedaEfetiva) {
	this->alutraQuedaEfetiva = alutraQuedaEfetiva;
}

void ConjuntoUnidadesGeradoras::setEngolimentoEfetivo(
		double engolimentoEfetivo) {
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

double ConjuntoUnidadesGeradoras::calcularEngolimentoEfetivo() {
	return this->getEngolimentoEfetivo() * this->getNumeroUnidadesGeradoras();
}

double ConjuntoUnidadesGeradoras::calcularEngolimentoMaximo(
		double alturaQuedaLiquida) {
	double engolimentoMaximo = this->engolimentoEfetivo
			* pow(alturaQuedaLiquida / this->alutraQuedaEfetiva,
					this->calcularAlfa(alturaQuedaLiquida))
			* this->getNumeroUnidadesGeradoras();
	return engolimentoMaximo;
}

double ConjuntoUnidadesGeradoras::calcularAlfa(double alturaQuedaLiquida) {
	double alfa = 0.0;
	if (alturaQuedaLiquida >= this->alutraQuedaEfetiva) {
		alfa = -1;
	} else if (alturaQuedaLiquida < this->alutraQuedaEfetiva
			&& (tipoTurbinasHidraulicas == FRANCIS
					|| tipoTurbinasHidraulicas == PELTRON)) {
		alfa = 0.5;
	} else if (alturaQuedaLiquida
			< this->alutraQuedaEfetiva&& tipoTurbinasHidraulicas == KAPLAN) {
		alfa = 0.2;
	}
	return alfa;
}
