/*
 * main.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

// Importando bibliotecas necessárias
#include <iostream> // Biblioteca  padrão de I/O
#include <algorithm>
#include <fstream> // Para manipular arquivos
#include <vector> // Para fácil uso de vetores
#include <string> // Para trabalhar fácil com strings
#include <sstream> // Para trabalhar fácil com strings
#include <math.h> // Para ajudar em calculos matemáticos
#include <time.h> // Calcular o tempo de execução
#include "poesh/SistemaHidroeletrico.h"
#include "poesh/HidroeletricaReservatorio.h"
#include "ferramentas/Conversor.h"
#include "aco/ACO.h"

using namespace std;

// Constantes POSH
#define INTERVALOS 61
#define DEMANDA 3472 // 3472 MW
#define QUANTIDADE_USINAS 2
// Constantes ACO
#define POPULATION_SIZE 30
#define DISCRETIZACAO 21
#define MAX_ITERATIONS 2500
#define PHEROMONE_RATE 0.1
#define EVAPORATION_RATE 0.5
#define POSITIVE_CONTS 0.75

// Variáveis
Conversor conversor;
vector<vector<double> > volumes;
vector<vector<double> > vazoes;

string number_to_String(double n);
double calcular_tempo(clock_t start, clock_t end);
void carregar_valores();

int main(int argc, char *argv[]) {
	clock_t time_start = clock();

	// Carregar arquivos
	carregar_valores();

	SistemaHidroeletrico* sistemaHidroeletrico = new SistemaHidroeletrico(
			INTERVALOS, DEMANDA, volumes, vazoes);

	// Configurando as usinas
	// Emborcação
	HidroeletricaReservatorio* emborcacao = new HidroeletricaReservatorio(0,
			"Emborcação");

	ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradorasEmborcacao =
			new ConjuntoUnidadesGeradoras(2, 4, 298.0, 262.0, 130.30, 1);
	CasaDeMaquinas* casaDeMaquinasEmborcacao = new CasaDeMaquinas();
	casaDeMaquinasEmborcacao->adicionarConjuntoUnidadesGeradoras(
			conjuntoUnidadesGeradorasEmborcacao);
	emborcacao->setCasaDeMaquinas(casaDeMaquinasEmborcacao);

	vector<double> coeficientesMontanteEmborcacao;
	coeficientesMontanteEmborcacao.push_back(568.09);
	coeficientesMontanteEmborcacao.push_back(1.4506E-02);
	coeficientesMontanteEmborcacao.push_back(-1.2028E-06);
	coeficientesMontanteEmborcacao.push_back(5.8303E-11);
	coeficientesMontanteEmborcacao.push_back(-1.1245E-15);
	PolinomioMontante* polinomioMontanteEmborcacao = new PolinomioMontante(
			coeficientesMontanteEmborcacao);
	emborcacao->setPolinomioMontante(polinomioMontanteEmborcacao);

	vector<double> coeficientesJusanteEmborcacao;
	coeficientesJusanteEmborcacao.push_back(519.78);
	coeficientesJusanteEmborcacao.push_back(3.9966E-03);
	coeficientesJusanteEmborcacao.push_back(-1.0987E-06);
	coeficientesJusanteEmborcacao.push_back(2.3438E-10);
	coeficientesJusanteEmborcacao.push_back(-1.7646E-14);
	PolinomioJusante* polinomioJusanteEmborcacao = new PolinomioJusante(
			coeficientesJusanteEmborcacao);
	emborcacao->setPolinomioJusante(polinomioJusanteEmborcacao);

	emborcacao->setVolumeMinimoOperativo(4669.0);
	emborcacao->setVolumeMaximoOperativo(17190.0);
	emborcacao->setVolumeMaximoMaximorum(17427.0);
	emborcacao->setVazaoDefluenteMinima(77.0);
	emborcacao->setVazaoDefluenteMaxima(1E20);
	emborcacao->setNivelMedioJusante(521.9);
	emborcacao->setCoeficientePerdaCargaHidraulica(0.0127);
	emborcacao->setCoeficienteProdutibilidadeEspecifica(0.008731);

	// Itubiara
	HidroeletricaReservatorio* itumbiara = new HidroeletricaReservatorio(1,
			"Itumbiara");

	ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradorasItumbiara =
			new ConjuntoUnidadesGeradoras(1, 6, 380.0, 537.0, 80.20, 1);
	CasaDeMaquinas* casaDeMaquinasItumbiara = new CasaDeMaquinas();
	casaDeMaquinasItumbiara->adicionarConjuntoUnidadesGeradoras(
			conjuntoUnidadesGeradorasItumbiara);
	itumbiara->setCasaDeMaquinas(casaDeMaquinasItumbiara);

	vector<double> coeficientesMontanteItumbiara;
	coeficientesMontanteItumbiara.push_back(471.16);
	coeficientesMontanteItumbiara.push_back(7.2805E-03);
	coeficientesMontanteItumbiara.push_back(-5.6098E-07);
	coeficientesMontanteItumbiara.push_back(2.59776E-11);
	coeficientesMontanteItumbiara.push_back(-4.845359E-16);
	PolinomioMontante* polinomioMontanteItumbiara = new PolinomioMontante(
			coeficientesMontanteItumbiara);
	itumbiara->setPolinomioMontante(polinomioMontanteItumbiara);

	vector<double> coeficientesJusanteItumbiara;
	coeficientesJusanteItumbiara.push_back(433.0);
	coeficientesJusanteItumbiara.push_back(1.59584E-03);
	coeficientesJusanteItumbiara.push_back(-8.177386E-08);
	coeficientesJusanteItumbiara.push_back(3.1735E-12);
	coeficientesJusanteItumbiara.push_back(0.0);
	PolinomioJusante* polinomioJusanteItumbiara = new PolinomioJusante(
			coeficientesJusanteItumbiara);
	itumbiara->setPolinomioJusante(polinomioJusanteItumbiara);

	itumbiara->setVolumeMinimoOperativo(4573.0);
	itumbiara->setVolumeMaximoOperativo(17027.0);
	itumbiara->setVolumeMaximoMaximorum(17975.0);
	itumbiara->setVazaoDefluenteMinima(254.0);
	itumbiara->setVazaoDefluenteMaxima(1E20);
	itumbiara->setNivelMedioJusante(435.6);
	itumbiara->setCoeficientePerdaCargaHidraulica(0.0120);
	itumbiara->setCoeficienteProdutibilidadeEspecifica(0.008829);

	sistemaHidroeletrico->adicionarUsinaHidroeletrica(itumbiara);

	itumbiara->adicionarUsinaMontante(emborcacao);

	sistemaHidroeletrico->adicionarUsinaHidroeletrica(emborcacao);

	double custo = sistemaHidroeletrico->calcularCustoTotal();

	cout.precision(11);
	cout << "Custo Total (Arquivos): " << custo << endl;

	cin.get();

	ACO* aco = new ACO(POPULATION_SIZE, QUANTIDADE_USINAS, INTERVALOS,
			DISCRETIZACAO, MAX_ITERATIONS, PHEROMONE_RATE, EVAPORATION_RATE,
			POSITIVE_CONTS, sistemaHidroeletrico);

	aco->calculateSolution();

	cout << "\nPior Custo (ACO): " << aco->worseFitness << endl;

	string temp = "";
	for (int u = 0; u < QUANTIDADE_USINAS; u++) {
		for (int i = 0; i < INTERVALOS; i++) {
			temp += number_to_String(aco->worseRoutes[u][i]);
			if (i < (INTERVALOS - 1)) {
				temp += ", ";
			}
		}
		temp += "\n";
	}

	cout << "Pior rota (ACO):\n" << temp << endl;

	sistemaHidroeletrico->setVolumes(aco->worseRoutes);
	sistemaHidroeletrico->calcularCustoTotal();

	cout << "Melhor Custo (ACO): " << aco->bestFitness << endl;

	temp = "";
	for (int u = 0; u < QUANTIDADE_USINAS; u++) {
		for (int i = 0; i < INTERVALOS; i++) {
			temp += number_to_String(aco->bestRoutes[u][i]);
			if (i < (INTERVALOS - 1)) {
				temp += ", ";
			}
		}
		temp += "\n";
	}

	cout << "Melhor rota (ACO):\n" << temp << endl;

	sistemaHidroeletrico->setVolumes(aco->bestRoutes);
	sistemaHidroeletrico->calcularCustoTotal();

	cout << "\nTempo de execução (MGHP): "
			<< calcular_tempo(time_start, clock()) << " ms" << endl;

	//cin.get(); // aguarda por um novo caracter para então encerrar a aplicação
	return 0;
}

string number_to_String(double n) {
	stringstream out;
	out << n;
	return out.str();
}

double calcular_tempo(clock_t start, clock_t end) {
	return 1000.0 * ((double) (end - start) / (double) CLOCKS_PER_SEC);
}

void carregar_valores() {
	string line;

	ifstream emborcacao_volumes_file("./assets/0-Emborcacao-Volumes.txt"); // ifstream = padrão ios:in
	// ifstream emborcacao_volumes_file("./assets/Emborcacao-Volumes-Completos.txt");
	if (emborcacao_volumes_file.is_open()) {
		int contador_interacao = 0;
		//enquanto end of file for false continua
		vector<double> temp_array;
		while (!emborcacao_volumes_file.eof()) {
			getline(emborcacao_volumes_file, line); // como foi aberto em modo texto(padrão), e não binário(ios::bin) pega cada linha
			double d = conversor.string_para_double(line);
			temp_array.push_back(d);
			contador_interacao++;
		}
		volumes.push_back(temp_array);
		emborcacao_volumes_file.close();
	} else {
		cout << "Impossivel abrir o arquivo!";
	}
	//ifstream emborcacao_vazoes_file("./assets/Emborcacao-Vazoes-Naturais-1936-1941.txt"); // ifstream = padrão ios:in
	ifstream emborcacao_vazoes_file("./assets/0-Emborcacao-Vazoes.txt"); // ifstream = padrão ios:in
	if (emborcacao_vazoes_file.is_open()) {
		int contador_interacao = 0;
		//enquanto end of file for false continua
		vector<double> temp_array;
		while (!emborcacao_vazoes_file.eof()) {
			getline(emborcacao_vazoes_file, line); // como foi aberto em modo texto(padrão), e não binário(ios::bin) pega cada linha
			double d = conversor.string_para_double(line);
			temp_array.push_back(d);
			contador_interacao++;
		}
		vazoes.push_back(temp_array);
		emborcacao_vazoes_file.close();
	} else {
		cout << "Impossivel abrir o arquivo!";
	}

	ifstream itumbiara_volumes_file("./assets/0-Itumbiara-Volumes.txt"); // ifstream = padrão ios:in
	// ifstream itumbiara_volumes_file("./assets/Itumbiara-Volumes-Completos.txt");
	if (itumbiara_volumes_file.is_open()) {
		int contador_interacao = 0;
		//enquanto end of file for false continua
		vector<double> temp_array;
		while (!itumbiara_volumes_file.eof()) {
			getline(itumbiara_volumes_file, line); // como foi aberto em modo texto(padrão), e não binário(ios::bin) pega cada linha
			double d = conversor.string_para_double(line);
			temp_array.push_back(d);
			contador_interacao++;
		}
		volumes.push_back(temp_array);
		itumbiara_volumes_file.close();
	} else {
		cout << "Impossivel abrir o arquivo!";
	}
	// ifstream itumbiara_vazoes_file("./assets/Itumbiara-Vazoes-Naturais-1936-1941.txt"); // ifstream = padrão ios:in
	ifstream itumbiara_vazoes_file("./assets/0-Itumbiara-Vazoes.txt"); // ifstream = padrão ios:in
	if (itumbiara_vazoes_file.is_open()) {
		int contador_interacao = 0;
		//enquanto end of file for false continua
		vector<double> temp_array;
		while (!itumbiara_vazoes_file.eof()) {
			getline(itumbiara_vazoes_file, line); // como foi aberto em modo texto(padrão), e não binário(ios::bin) pega cada linha
			double d = conversor.string_para_double(line);
			temp_array.push_back(d);
			contador_interacao++;
		}
		vazoes.push_back(temp_array);
		itumbiara_vazoes_file.close();
	} else {
		cout << "Impossivel abrir o arquivo!";
	}
}
