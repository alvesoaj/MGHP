/*
 * UsinaHidroeletrica.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#include "UsinaHidroeletrica.h"

UsinaHidroeletrica::UsinaHidroeletrica() {
}

unsigned int UsinaHidroeletrica::getCodigo() {
	return codigo;
}

std::string UsinaHidroeletrica::getNome() {
	return nome;
}

double UsinaHidroeletrica::getVolumeMorto() {
	return volumeMorto;
}

double UsinaHidroeletrica::getVolumeMaximoMaximorum() {
	return volumeMaximoMaximorum;
}

double UsinaHidroeletrica::getVazaoDefluenteMinima() {
	return vazaoDefluenteMinima;
}

double UsinaHidroeletrica::getVazaoDefluenteMaxima() {
	return vazaoDefluenteMaxima;
}

double UsinaHidroeletrica::getCoeficienteProdutibilidadeEspecifica() {
	return coeficienteProdutibilidadeEspecifica;
}

double UsinaHidroeletrica::getCoeficientePerdaCargaHidraulica() {
	return coeficientePerdaCargaHidraulica;
}

double UsinaHidroeletrica::getNivelMedioJusante() {
	return nivelMedioJusante;
}

CasaDeMaquinas* UsinaHidroeletrica::getCasaDeMaquinas() {
	return casaDeMaquinas;
}

PolinomioJusante* UsinaHidroeletrica::getPolinomioJusante() {
	return polinomioJusante;
}

vector<UsinaHidroeletrica*> UsinaHidroeletrica::getUsinasMontante() {
	return usinasMontante;
}

void UsinaHidroeletrica::setCodigo(unsigned int codigo) {
	this->codigo = codigo;
}

void UsinaHidroeletrica::setNome(std::string nome = "") {
	this->nome = nome;
}

void UsinaHidroeletrica::setVolumeMorto(double volumeMorto) {
	this->volumeMorto = volumeMorto;
}

void UsinaHidroeletrica::setVolumeMaximoMaximorum(
		double volumeMaximoMaximorum) {
	this->volumeMaximoMaximorum = volumeMaximoMaximorum;
}

void UsinaHidroeletrica::setVazaoDefluenteMinima(double vazaoDefluenteMinima) {
	this->vazaoDefluenteMinima = vazaoDefluenteMinima;
}

void UsinaHidroeletrica::setVazaoDefluenteMaxima(double vazaoDefluenteMaxima) {
	this->vazaoDefluenteMaxima = vazaoDefluenteMaxima;
}

void UsinaHidroeletrica::setCoeficientePerdaCargaHidraulica(
		double coeficientePerdaCargaHidraulica) {
	this->coeficientePerdaCargaHidraulica = coeficientePerdaCargaHidraulica;
}

void UsinaHidroeletrica::setCoeficienteProdutibilidadeEspecifica(
		double coeficienteProdutibilidadeEspecifica) {
	this->coeficienteProdutibilidadeEspecifica =
			coeficienteProdutibilidadeEspecifica;
}

void UsinaHidroeletrica::setNivelMedioJusante(double nivelMedioJusante) {
	this->nivelMedioJusante = nivelMedioJusante;
}

void UsinaHidroeletrica::setCasaDeMaquinas(CasaDeMaquinas* casaDeMaquinas) {
	this->casaDeMaquinas = casaDeMaquinas;
}

void UsinaHidroeletrica::setPolinomioJusante(
		PolinomioJusante* polinomioJusante) {
	this->polinomioJusante = polinomioJusante;

}

void UsinaHidroeletrica::adicionarUsinaMontante(
		UsinaHidroeletrica* usinaMontante) {
	this->usinasMontante.push_back(usinaMontante);
}

bool UsinaHidroeletrica::temUsinaMontante() {
	if (this->usinasMontante.size() > 0) {
		return true;
	} else {
		return false;
	}
}

double UsinaHidroeletrica::calcularVazaoDefluente(double volumeAnterior,
		double volumeAtual) {
	return volumeAnterior - volumeAtual;
}

double UsinaHidroeletrica::calcularNivelJusante(double vazaoDefluente) {
	//return this->polinomioJusante->calcularValor(vazaoDefluente + this->nivelMedioJusante);
	return this->polinomioJusante->calcularValor(vazaoDefluente);
}
