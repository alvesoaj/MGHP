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
#include "ConjuntoUnidadesGeradoras.h"

class CasaDeMaquinas {
private:
	// Atributos privados da classe Casa de Maquinas
	std::vector<ConjuntoUnidadesGeradoras*> listaConjuntoUnidadesGeradoras;
public:
	// Métodos da classe Casa de Maquinas
	CasaDeMaquinas();
	bool adicionarConjuntoUnidadesGeradoras(
			ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradoras);
	bool removerConjuntoUnidadesGeradoras(
			ConjuntoUnidadesGeradoras* conjuntoUnidadesGeradoras);
};

#endif /* CASADEMAQUINAS_H_ */
