/*
 * HidroeletricaReservatorio.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

// Importando bibliotecas necessárias
#include <iostream>
#include <vector> // Para fácil uso de vetores
#include <string> // Para trabalhar fácil com strings
#include <sstream> // Para trabalhar fácil com strings
#include <math.h> // Para ajudar em calculos matemáticos
#include <ctime>  // Para usar o time() e fornecer um bom seed para o random
#include <cstdlib> // Para gerar numeros randômicos
#include "models/HidroeletricaReservatorio.h"

// Constantes
#define INVALID -1

using namespace std;

// Variáveis
HidroeletricaReservatorio* itumbiara = new HidroeletricaReservatorio(1,
		"Itumbiara");
HidroeletricaReservatorio* emborcacao = new HidroeletricaReservatorio(2,
		"Emborcação");

int main(int argc, char *argv[]) {
	// Configurando as usinas
	// Itubiara
	ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradoras =
			new ConjuntoUnidadesGeradoras(1, 4, 298, 262, 130.30, 1);
	CasaDeMaquinas* casaDeMaquinas = new CasaDeMaquinas();
	casaDeMaquinas->adicionarConjuntoUnidadesGeradoras(conjuntoUnidadesGeradoras);
	itumbiara->setCasaDeMaquinas(casaDeMaquinas);

	vector<double> coeficientesJusante;
	coeficientesJusante.push_back(519.78);
	coeficientesJusante.push_back(3.9966E-03);
	coeficientesJusante.push_back(-1.0987E-06);
	coeficientesJusante.push_back(2.3438E-10);
	coeficientesJusante.push_back(-1.7646E-14);
	PolinomioJusante* polinomioJusante = new PolinomioJusante(
			coeficientesJusante);
	itumbiara->setPolinomioJusante(polinomioJusante);

	vector<double> coeficientesMontante;
	coeficientesMontante.push_back(568.09);
	coeficientesMontante.push_back(1.4506E-02);
	coeficientesMontante.push_back(-1.2028E-06);
	coeficientesMontante.push_back(5.8303E-11);
	coeficientesMontante.push_back(-1.1245E-15);
	PolinomioMontante* polinomioMontante = new PolinomioMontante(
			coeficientesMontante);
	itumbiara->setPolinomioMontante(polinomioMontante);

	itumbiara->setVolumeMinimoOperativo(4669);
	itumbiara->setVolumeMaximoOperativo(17190);
	itumbiara->setVolumeMaximoMaximorum(17427);
	itumbiara->setVazaoDefluenteMinima(77);
	itumbiara->setVazaoDefluenteMaxima(1E20);
	itumbiara->setNivelMedioJusante(521.9);
	itumbiara->setProdutibilidadeEspecifica(0.008731);

	// Emborcação

	//cin.get(); // aguarda por um novo caracter para então encerrar a aplicação

	return 0;
}
