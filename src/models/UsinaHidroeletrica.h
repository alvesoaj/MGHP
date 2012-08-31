/*
 * UsinaHidroeletrica.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef USINAHIDROELETRICA_H_
#define USINAHIDROELETRICA_H_

// Importando bibliotecas úteis
#include <string> // Para trabalhar com strings
#include "CasaDeMaquinas.h"
#include "PolinomioJusante.h"

class UsinaHidroeletrica {
protected:
	// Atributos privados da classe Usina
	unsigned int codigo;
	std::string nome;
	double volumeMorto;
	double volumeMaximoMaximorum;
	double vazaoDefluenteMinima;
	double vazaoDefluenteMaxima;
	double nivelMedioJusante;
	double coeficientePerdaCargaHidraulica;
	double produtibilidadeEspecifica;
	CasaDeMaquinas* casaDeMaquinas;
	PolinomioJusante* polinomioJusante;
	UsinaHidroeletrica* usinaMontante;

public:
	// Métodos da classe Usina
	UsinaHidroeletrica();

	unsigned int getCodigo();
	std::string getNome();
	double getVolumeMorto();
	double getVolumeMaximoMaximorum();
	double getVazaoDefluenteMinima();
	double getVazaoDefluenteMaxima();
	double getNivelMedioJusante();
	double getCoeficientePerdaCargaHidraulica();
	double getProdutibilidadeEspecifica();
	CasaDeMaquinas* getCasaDeMaquinas();
	PolinomioJusante* getPolinomioJusante();
	UsinaHidroeletrica* getUsinaMontante();

	void setCodigo(unsigned int codigo);
	void setNome(std::string nome);
	void setVolumeMorto(double volumeMorto);
	void setVolumeMaximoMaximorum(double volumeMaximoMaximorum);
	void setVazaoDefluenteMinima(double vazaoDefluenteMinima);
	void setVazaoDefluenteMaxima(double vazaoDefluenteMaxima);
	void setNivelMedioJusante(double nivelMedioJusante);
	void setProdutibilidadeEspecifica(double produtibilidadeEspecifica);
	void setCoeficientePerdaCargaHidraulica(
			double coeficientePerdaCargaHidraulica);
	void setCasaDeMaquinas(CasaDeMaquinas* casaDeMaquinas);
	void setPolinomioJusante(PolinomioJusante* polinomioJusante);
	void setUsinaMontante(UsinaHidroeletrica* usinaMontante);

	double calcularVazaoDefluente(double volumeAnterior, double volumeAtual,
			double vazaoIncremental);
};

#endif /* USINAHIDROELETRICA_H_ */
