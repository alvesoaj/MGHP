/*
 * ConjuntoUnidadesGeradoras.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef CONJUNTOUNIDADESGERADORAS_H_
#define CONJUNTOUNIDADESGERADORAS_H_

// Para ajudar em calculos matemáticos
#include <math.h>

// Constantes
#define FRANCIS	 1
#define KAPLAN	 2
#define PELTRON	 3

class ConjuntoUnidadesGeradoras {
private:
	// Atributos privados da classe Conujonto de Unidades Geradoras
	unsigned int id;
	double alutraQuedaEfetiva;
	double engolimentoEfetivo;
	unsigned int numeroUnidadesGeradoras;
	double potenciaEfetiva;
	int tipoTurbinasHidraulicas;

	double calcularAlfa(double alturaQuedaLiquida);

public:
	// Métodos da classe Unidades Geradoras
	ConjuntoUnidadesGeradoras(unsigned int id,
			unsigned int numeroUnidadesGeradoras, double potenciaEfetiva,
			double engolimentoEfetivo, double alutraQuedaEfetiva,
			int tipoTurbinasHidraulicas);

	unsigned int getId();
	double getAlutraQuedaEfetiva();
	double getEngolimentoEfetivo();
	unsigned int getNumeroUnidadesGeradoras();
	double getPotenciaEfetiva();
	int getTipoTurbinasHidraulicas();
	void setAlutraQuedaEfetiva(double alutraQuedaEfetiva);
	void setEngolimentoEfetivo(double engolimentoEfetivo);
	void setNumeroUnidadesGeradoras(unsigned int numeroUnidadesGeradoras);
	void setPotenciaEfetiva(double potenciaEfetiva);
	void setTipoTurbinasHidraulicas(int tipoTurbinasHidraulicas);

	double calcularEngolimentoMaximo(double alturaQuedaLiquida);
};

#endif /* CONJUNTOUNIDADESGERADORAS_H_ */
