/*
 * CasaDeMaquinas.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef CASADEMAQUINAS_H_
#define CASADEMAQUINAS_H_

// Importando bibliotecas úteis
#include <vector> // Para trabalhar com vetores

class CasaDeMaquinas {
public:
	// Atributos da classe Casa de Maquinas
	std::vector<ConjuntoUnidadesGeradoras> listaConjuntoUnidadesGeradoras;

	// Métodos da classe Casa de Maquinas
	CasaDeMaquinas();
};

#endif /* CASADEMAQUINAS_H_ */
