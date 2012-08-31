/*
 * main.cpp
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
#include "models/HidroeletricaReservatorio.h"

using namespace std;

// Constantes
#define INTERVALOS 10
#define QUANTIDADE_USINAS 2

// Variáveis
HidroeletricaReservatorio* hidroeletricas[QUANTIDADE_USINAS];
double volumes[INTERVALOS][QUANTIDADE_USINAS] = { { 250.0, 152.0 }, { 300.0,
		200.0 }, { 290.0, 100.0 }, { 785.0, 123.0 }, { 500.0, 369.0 }, { 456.0,
		265.0 }, { 158.0, 421.0 }, { 364.0, 965.0 }, { 154.0, 369.0 }, { 234.0,
		165.0 } };
double vazoes[INTERVALOS][QUANTIDADE_USINAS] = { { 25.0, 15.0 }, { 30.0, 20.0 },
		{ 29.0, 10.0 }, { 78.0, 12.0 }, { 50.0, 36.0 }, { 45.0, 26.0 }, { 15.0,
				42.0 }, { 36.0, 96.0 }, { 15.0, 36.0 }, { 23.0, 16.0 } };
double geracao_hidraulica_total = 0.0;

string number_to_string(double n);

int main(int argc, char *argv[]) {
	int contador_usina = 0;

	// Configurando as usinas
	// Itubiara
	HidroeletricaReservatorio* itumbiara = new HidroeletricaReservatorio(1,
			"Itumbiara");

	ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradorasItumbiara =
			new ConjuntoUnidadesGeradoras(1, 4, 298.0, 262.0, 130.30, 1);
	CasaDeMaquinas* casaDeMaquinasItumbiara = new CasaDeMaquinas();
	casaDeMaquinasItumbiara->adicionarConjuntoUnidadesGeradoras(
			conjuntoUnidadesGeradorasItumbiara);
	itumbiara->setCasaDeMaquinas(casaDeMaquinasItumbiara);

	vector<double> coeficientesMontanteItumbiara;
	coeficientesMontanteItumbiara.push_back(568.09);
	coeficientesMontanteItumbiara.push_back(1.4506E-02);
	coeficientesMontanteItumbiara.push_back(-1.2028E-06);
	coeficientesMontanteItumbiara.push_back(5.8303E-11);
	coeficientesMontanteItumbiara.push_back(-1.1245E-15);
	PolinomioMontante* polinomioMontanteItumbiara = new PolinomioMontante(
			coeficientesMontanteItumbiara);
	itumbiara->setPolinomioMontante(polinomioMontanteItumbiara);

	vector<double> coeficientesJusanteItumbiara;
	coeficientesJusanteItumbiara.push_back(519.78);
	coeficientesJusanteItumbiara.push_back(3.9966E-03);
	coeficientesJusanteItumbiara.push_back(-1.0987E-06);
	coeficientesJusanteItumbiara.push_back(2.3438E-10);
	coeficientesJusanteItumbiara.push_back(-1.7646E-14);
	PolinomioJusante* polinomioJusanteItumbiara = new PolinomioJusante(
			coeficientesJusanteItumbiara);
	itumbiara->setPolinomioJusante(polinomioJusanteItumbiara);

	itumbiara->setVolumeMinimoOperativo(4669.0);
	itumbiara->setVolumeMaximoOperativo(17190.0);
	itumbiara->setVolumeMaximoMaximorum(17427.0);
	itumbiara->setVazaoDefluenteMinima(77.0);
	itumbiara->setVazaoDefluenteMaxima(1E20);
	itumbiara->setNivelMedioJusante(521.9);
	itumbiara->setCoeficientePerdaCargaHidraulica(0.0127);
	itumbiara->setProdutibilidadeEspecifica(0.008731);

	hidroeletricas[contador_usina] = itumbiara;
	contador_usina++;

	// Emborcação
	HidroeletricaReservatorio* emborcacao = new HidroeletricaReservatorio(2,
			"Emborcação");

	ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradorasEmborcacao =
			new ConjuntoUnidadesGeradoras(2, 6, 380.0, 537.0, 80.20, 1);
	CasaDeMaquinas* casaDeMaquinasEmborcacao = new CasaDeMaquinas();
	casaDeMaquinasEmborcacao->adicionarConjuntoUnidadesGeradoras(
			conjuntoUnidadesGeradorasEmborcacao);
	emborcacao->setCasaDeMaquinas(casaDeMaquinasEmborcacao);

	vector<double> coeficientesMontanteEmborcacao;
	coeficientesMontanteEmborcacao.push_back(471.16);
	coeficientesMontanteEmborcacao.push_back(7.2805E-03);
	coeficientesMontanteEmborcacao.push_back(-5.6098E-07);
	coeficientesMontanteEmborcacao.push_back(2.59776E-11);
	coeficientesMontanteEmborcacao.push_back(-4.845359E-16);
	PolinomioMontante* polinomioMontanteEmborcacao = new PolinomioMontante(
			coeficientesMontanteEmborcacao);
	emborcacao->setPolinomioMontante(polinomioMontanteEmborcacao);

	vector<double> coeficientesJusanteEmborcacao;
	coeficientesJusanteEmborcacao.push_back(433.0);
	coeficientesJusanteEmborcacao.push_back(1.59584E-03);
	coeficientesJusanteEmborcacao.push_back(-8.177386E-08);
	coeficientesJusanteEmborcacao.push_back(3.1735E-12);
	coeficientesJusanteEmborcacao.push_back(0.0);
	PolinomioJusante* polinomioJusanteEmborcacao = new PolinomioJusante(
			coeficientesJusanteEmborcacao);
	emborcacao->setPolinomioJusante(polinomioJusanteEmborcacao);

	emborcacao->setVolumeMinimoOperativo(4573.0);
	emborcacao->setVolumeMaximoOperativo(17027.0);
	emborcacao->setVolumeMaximoMaximorum(17975.0);
	emborcacao->setVazaoDefluenteMinima(254.0);
	emborcacao->setVazaoDefluenteMaxima(1E20);
	emborcacao->setNivelMedioJusante(435.6);
	emborcacao->setCoeficientePerdaCargaHidraulica(0.0120);
	emborcacao->setProdutibilidadeEspecifica(0.008829);

	emborcacao->setUsinaMontante(itumbiara);

	hidroeletricas[contador_usina] = emborcacao;
	contador_usina++;

	for (int intervalo = 1; intervalo < INTERVALOS; intervalo++) {
		double geracao_hidraulica = 0.0;
		for (int indice_usina = 0; indice_usina < QUANTIDADE_USINAS;
				indice_usina++) {
			double altura_montante =
					hidroeletricas[indice_usina]->calcularAlturaMontante(
							volumes[intervalo][indice_usina]);
			double vazao_defluente =
					hidroeletricas[indice_usina]->calcularVazaoDefluente(
							volumes[intervalo - 1][indice_usina],
							volumes[intervalo][indice_usina],
							vazoes[intervalo][indice_usina]);
			cout << altura_montante << endl;
			cout << vazao_defluente << endl;
		}
	}

	//cin.get(); // aguarda por um novo caracter para então encerrar a aplicação

	return 0;
}

string number_to_string(double n) {
	stringstream out;
	out << n;
	return out.str();
}
