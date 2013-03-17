/*
 * Sugeno.h
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#ifndef SUGENO_H_
#define SUGENO_H_

// Importando bibliotecas necessárias
#include <iostream> // Biblioteca  padrão de I/O
#include "../ferramentas/Conversor.h"
#include "../poesh/SistemaHidroeletrico.h"
#include "../fuzzy/FuzzyRule.h"
#include "../fuzzy/FuzzyComposition.h"
#include "../fuzzy/Fuzzy.h"
#include "../fuzzy/FuzzyRuleConsequent.h"
#include "../fuzzy/FuzzyOutput.h"
#include "../fuzzy/FuzzyInput.h"
#include "../fuzzy/FuzzyIO.h"
#include "../fuzzy/FuzzySet.h"
#include "../fuzzy/FuzzyRuleAntecedent.h"

using namespace std;

class Sugeno {
public:
	Sugeno();
	double calcularVolumeHeuristica(int usinaIndice,
			double energiaArmazenadaSistemaNormalizada);
private:
	Fuzzy* fuzzy;
	FuzzyInput* valorEAS;
	FuzzySet* muitoBaixa;
	FuzzySet* baixa;
	FuzzySet* media;
	FuzzySet* alta;
	FuzzySet* muitoAlta;
	FuzzyOutput* output1;
	FuzzyOutput* output2;
	FuzzyOutput* output3;
	FuzzyOutput* output4;
	FuzzyOutput* output5;
	FuzzySet* powerOf1;
	FuzzySet* powerOf2;
	FuzzySet* powerOf3;
	FuzzySet* powerOf4;
	FuzzySet* powerOf5;
	FuzzyRuleAntecedent* ifEASMuitoBaixa;
	FuzzyRuleAntecedent* ifEASBaixa;
	FuzzyRuleAntecedent* ifEASMedia;
	FuzzyRuleAntecedent* ifEASAlta;
	FuzzyRuleAntecedent* ifEASMuitoAlta;
	FuzzyRuleConsequent* thenSetPowerOf1;
	FuzzyRuleConsequent* thenSetPowerOf2;
	FuzzyRuleConsequent* thenSetPowerOf3;
	FuzzyRuleConsequent* thenSetPowerOf4;
	FuzzyRuleConsequent* thenSetPowerOf5;
	FuzzyRule* fuzzyRule1;
	FuzzyRule* fuzzyRule2;
	FuzzyRule* fuzzyRule3;
	FuzzyRule* fuzzyRule4;
	FuzzyRule* fuzzyRule5;
	double a[2][5];
	double b[2][5];
};

#endif /* SUGENO_H_ */
