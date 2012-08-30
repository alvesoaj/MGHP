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
class UsinaHidroeletrica {
private:
	// Atributos privados da classe Usina
	unsigned int codigo;
	std::string nome = "";
	double volumeMorto;
	double volumeMaximoMaximorum;
	double vazaoDefluenteMinima;
	double vazaoDefluenteMaxima;
	double nivelMedioJusante;
	double produtibilidadeEspecifica;
	CasaDeMaquinas casaDeMaquinas = NULL;
	PolinomioJusante polinomioJusante = NULL;
	UsinaHidroeletrica usinaMontante = NULL;

public:
	// Métodos da classe Usina
	void setCasaDeMaquinas(CasaDeMaquinas casaDeMaquinas);
	void setPolinomioJusante(PolinomioJusante polinomioJusante);
	void setUsinaMontante(UsinaHidroeletrica usinaMontante);
};

#endif /* USINAHIDROELETRICA_H_ */
