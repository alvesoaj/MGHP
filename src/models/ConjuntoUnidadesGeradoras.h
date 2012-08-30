/*
 * ConjuntoUnidadesGeradoras.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef CONJUNTOUNIDADESGERADORAS_H_
#define CONJUNTOUNIDADESGERADORAS_H_

class ConjuntoUnidadesGeradoras {
public:
	// Atributos da classe Conujonto de Unidades Geradoras
	unsigned int id;
	unsigned int numeroUnidadesGeradoras;
	double potenciaEfetiva;
	double engolimentoEfetivo;
	double alutraQuedaEfetiva;
	int tipoTurbinasHidraulicas;

	// Métodos da classe Unidades Geradoras
	ConjuntoUnidadesGeradoras(unsigned int id,unsigned int numeroUnidadesGeradoras,
			double potenciaEfetiva, double engolimentoEfetivo,
			double alutraQuedaEfetiva, int tipoTurbinasHidraulicas);
};

#endif /* CONJUNTOUNIDADESGERADORAS_H_ */
