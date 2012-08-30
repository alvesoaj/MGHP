/*
 * ConjuntoUnidadesGeradoras.h
 *
 *  Created on: Aug 28, 2012
 *      Author: zerokol
 */

#ifndef CONJUNTOUNIDADESGERADORAS_H_
#define CONJUNTOUNIDADESGERADORAS_H_

class ConjuntoUnidadesGeradoras {
private:
	// Atributos privados da classe Conujonto de Unidades Geradoras
	unsigned int id;
	double alutraQuedaEfetiva;
	double engolimentoEfetivo;
	unsigned int numeroUnidadesGeradoras;
	double potenciaEfetiva;
	int tipoTurbinasHidraulicas;

public:
	// Métodos da classe Unidades Geradoras
	ConjuntoUnidadesGeradoras(unsigned int id,
			unsigned int numeroUnidadesGeradoras, double potenciaEfetiva,
			double engolimentoEfetivo, double alutraQuedaEfetiva,
			int tipoTurbinasHidraulicas);

	unsigned int getId() const;
	double getAlutraQuedaEfetiva() const;
	double getEngolimentoEfetivo() const;
	unsigned int getNumeroUnidadesGeradoras() const;
	double getPotenciaEfetiva() const;
	int getTipoTurbinasHidraulicas() const;
	void setAlutraQuedaEfetiva(double alutraQuedaEfetiva);
	void setEngolimentoEfetivo(double engolimentoEfetivo);
	void setNumeroUnidadesGeradoras(unsigned int numeroUnidadesGeradoras);
	void setPotenciaEfetiva(double potenciaEfetiva);
	void setTipoTurbinasHidraulicas(int tipoTurbinasHidraulicas);
};

#endif /* CONJUNTOUNIDADESGERADORAS_H_ */
