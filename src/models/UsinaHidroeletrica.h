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
public:
	// Atributos da classe Usina
	std::string nome = "";
	unsigned int codigo;
	double volumeMorto;
	double volumeMaximoMaximorum;
	double vazaoDefluenteMinima;
	double vazaoDefluenteMaxima;
	double nivelMedioJusante;
	double produtibilidadeEspecifica;
	CasaDeMaquinas casaDeMaquinas;
	UsinaHidroeletrica* usinaMontante;
	PolinomioJusante polinomioJusante;

	// Métodos da classe Usina
	UsinaHidroeletrica();
};

#endif /* USINAHIDROELETRICA_H_ */
