/*
 * Sugeno.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: zerokol
 */

#include "Sugeno.h"

// Construtor
Sugeno::Sugeno() {
	this->fuzzy = new Fuzzy();

	// FuzzyInput
	this->valorEAS = new FuzzyInput(1);

	this->muitoBaixa = new FuzzySet(0.0, 0.0, 0.1, 0.3);
	this->valorEAS->addFuzzySet(this->muitoBaixa);
	this->baixa = new FuzzySet(0.1, 0.3, 0.3, 0.5);
	this->valorEAS->addFuzzySet(this->baixa);
	this->media = new FuzzySet(0.3, 0.5, 0.5, 0.7);
	this->valorEAS->addFuzzySet(this->media);
	this->alta = new FuzzySet(0.5, 0.7, 0.7, 0.9);
	this->valorEAS->addFuzzySet(this->alta);
	this->muitoAlta = new FuzzySet(0.7, 0.9, 1.0, 1.0);
	this->valorEAS->addFuzzySet(this->muitoAlta);

	this->fuzzy->addFuzzyInput(this->valorEAS);

	// FuzzyOutput
	this->output1 = new FuzzyOutput(1);

	this->powerOf1 = new FuzzySet(0, 10, 10, 20);
	this->output1->addFuzzySet(this->powerOf1);

	// this->output2 = new FuzzyOutput(2);

	this->powerOf2 = new FuzzySet(20, 30, 30, 40);
	this->output1->addFuzzySet(this->powerOf2);

	// this->output3 = new FuzzyOutput(3);

	this->powerOf3 = new FuzzySet(40, 50, 50, 60);
	this->output1->addFuzzySet(this->powerOf3);

	// this->output4 = new FuzzyOutput(4);

	this->powerOf4 = new FuzzySet(60, 70, 70, 80);
	this->output1->addFuzzySet(this->powerOf4);

	// this->output5 = new FuzzyOutput(5);

	this->powerOf5 = new FuzzySet(80, 90, 90, 100);
	this->output1->addFuzzySet(this->powerOf5);

	this->fuzzy->addFuzzyOutput(this->output1);
	// this->fuzzy->addFuzzyOutput(this->output2);
	// this->fuzzy->addFuzzyOutput(this->output3);
	// this->fuzzy->addFuzzyOutput(this->output4);
	// this->fuzzy->addFuzzyOutput(this->output5);

	this->ifEASMuitoBaixa = new FuzzyRuleAntecedent();
	this->ifEASMuitoBaixa->joinSingle(this->muitoBaixa);

	this->thenSetPowerOf1 = new FuzzyRuleConsequent();
	this->thenSetPowerOf1->addOutput(this->powerOf1);

	this->fuzzyRule1 = new FuzzyRule(1, this->ifEASMuitoBaixa,
			this->thenSetPowerOf1);
	this->fuzzy->addFuzzyRule(fuzzyRule1);

	this->ifEASBaixa = new FuzzyRuleAntecedent();
	this->ifEASBaixa->joinSingle(this->baixa);

	this->thenSetPowerOf2 = new FuzzyRuleConsequent();
	this->thenSetPowerOf2->addOutput(this->powerOf2);

	this->fuzzyRule2 = new FuzzyRule(2, this->ifEASBaixa,
			this->thenSetPowerOf2);
	this->fuzzy->addFuzzyRule(fuzzyRule2);

	this->ifEASMedia = new FuzzyRuleAntecedent();
	this->ifEASMedia->joinSingle(this->media);

	this->thenSetPowerOf3 = new FuzzyRuleConsequent();
	this->thenSetPowerOf3->addOutput(this->powerOf3);

	this->fuzzyRule3 = new FuzzyRule(3, this->ifEASMedia,
			this->thenSetPowerOf3);
	this->fuzzy->addFuzzyRule(fuzzyRule3);

	this->ifEASAlta = new FuzzyRuleAntecedent();
	this->ifEASAlta->joinSingle(this->alta);

	this->thenSetPowerOf4 = new FuzzyRuleConsequent();
	this->thenSetPowerOf4->addOutput(this->powerOf4);

	this->fuzzyRule4 = new FuzzyRule(4, this->ifEASAlta, this->thenSetPowerOf4);
	this->fuzzy->addFuzzyRule(fuzzyRule4);

	this->ifEASMuitoAlta = new FuzzyRuleAntecedent();
	this->ifEASMuitoAlta->joinSingle(this->muitoAlta);

	this->thenSetPowerOf5 = new FuzzyRuleConsequent();
	this->thenSetPowerOf5->addOutput(this->powerOf5);

	this->fuzzyRule5 = new FuzzyRule(5, this->ifEASMuitoAlta,
			this->thenSetPowerOf5);
	this->fuzzy->addFuzzyRule(fuzzyRule5);

	this->a[0][0] = 0.9286;
	this->a[0][1] = 1.0500;
	this->a[0][2] = 1.1898;
	this->a[0][3] = 1.1999;
	this->a[0][4] = 1.2115;

	this->b[0][0] = -0.0976;
	this->b[0][1] = -0.1328;
	this->b[0][2] = -0.1964;
	this->b[0][3] = -0.2033;
	this->b[0][4] = -0.2126;

	this->a[1][0] = 1.4355;
	this->a[1][1] = 0.9878;
	this->a[1][2] = 0.4386;
	this->a[1][3] = 0.2391;
	this->a[1][4] = 0.1044;

	this->b[1][0] = 0.3022;
	this->b[1][1] = 0.4225;
	this->b[1][2] = 0.6676;
	this->b[1][3] = 0.7921;
	this->b[1][4] = 0.9002;
}

double Sugeno::calcularVolumeHeuristica(int usinaIndice,
		double energiaArmazenadaSistemaNormalizada) {
	double produtoSoma = 0.0;
	double pertinenciaSoma = 0.0;

	this->fuzzy->setInput(1, energiaArmazenadaSistemaNormalizada);
	this->fuzzy->fuzzify();
	// this->fuzzy->defuzzify(1);

	// cout << "EAS: " << energiaArmazenadaSistemaNormalizada << endl;
	// cout << "U: " << usinaIndice << endl;

	// cout << "p1: " << this->powerOf1->getPertinence() << endl;
	if (this->powerOf1->getPertinence() > 0) {
		double saida = this->a[usinaIndice][0]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][0];
		produtoSoma += this->powerOf1->getPertinence() * saida;
		pertinenciaSoma += this->powerOf1->getPertinence();
	}
	// cout << "p2: " << this->powerOf2->getPertinence() << endl;
	if (this->powerOf2->getPertinence() > 0) {
		double saida = this->a[usinaIndice][1]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][1];
		produtoSoma += this->powerOf2->getPertinence() * saida;
		pertinenciaSoma += this->powerOf2->getPertinence();
	}
	// cout << "p3: " << this->powerOf3->getPertinence() << endl;
	if (this->powerOf3->getPertinence() > 0) {
		double saida = this->a[usinaIndice][2]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][2];
		produtoSoma += this->powerOf3->getPertinence() * saida;
		pertinenciaSoma += this->powerOf3->getPertinence();
	}
	// cout << "p4: " << this->powerOf4->getPertinence() << endl;
	if (this->powerOf4->getPertinence() > 0) {
		double saida = this->a[usinaIndice][3]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][3];
		produtoSoma += this->powerOf4->getPertinence() * saida;
		pertinenciaSoma += this->powerOf4->getPertinence();
	}
	// cout << "p5: " << this->powerOf5->getPertinence() << endl;
	if (this->powerOf5->getPertinence() > 0) {
		double saida = this->a[usinaIndice][4]
				* energiaArmazenadaSistemaNormalizada + b[usinaIndice][4];
		produtoSoma += this->powerOf5->getPertinence() * saida;
		pertinenciaSoma += this->powerOf5->getPertinence();
	}

	double response = produtoSoma / pertinenciaSoma;
	// cout << "res: " << response << endl;
	// cin.get();

	return response;
}
