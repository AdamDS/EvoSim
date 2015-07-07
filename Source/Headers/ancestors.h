#ifndef ANCESTORS_H
#define ANCESTORS_H

#include "genus.h"
//genus includes: species.h
//species includes: population.h
//population includes: indiv.h
//indiv includes:	landscape.h
//landscape includes: randomc.h & general.h
class ancestors {
public:
	ancestors(void);
	ancestors(int buffanc);
	~ancestors(void);
//ANCESTORS INTERACTIONS
	void setTempPopulation(population tp);
	void addToTheAncestors(population oldGen);
	void removePopulation(vector<population>::iterator byeGen);
	void resetTheAncestors();
	void replacePopulation(int disone, population* indi);
	population assortativeMating(landscape* babylaw, population* oldPop,
		CRandomMersenne* raNuGe);
	population cleaving(landscape* babylaw, population* oldPop,
		CRandomMersenne* raNuGe);
//ITERATOR ACCESS
	vector<population>::iterator beginOfTheAncestors();
	vector<population>::iterator endOfTheAncestors();
//THE ANCESTORS ACCESS
	population getThisPopulationOfTheAncestors(int thisPopulation);
	vector<population> getTheAncestors();
	int intSizeOfTheAncestors() const;
	int getPopulationSize(int k) const;
	int getParent1s(int k) const;
	int getParent2s(int k) const;
	int getNeighbor1s(int k) const;
	int getNeighbor2s(int k) const;
	double getMutabilities(int k) const;
	double getPhenotypeXs(int k) const;
	double getPhenotypeYs(int k) const;
	void doubleCheck(population* P) const;
private:
	vector<population> TheAncestors;
	vector<int> PopulationSize;
	vector<int> Parent1s;
	vector<int> Parent2s;
	vector<int> Neighbor1s;
	vector<int> Neighbor2s;
	vector<double> Mutabilities;
	vector<double> PhenotypeXs;
	vector<double> PhenotypeYs;

public:
	void addToTheNations(genus oldGenus);
	void removeGenus(vector<genus>::iterator byeGenus);
	void resetTheNations();
	void replaceGenus(int disone, genus* genulogy);
	genus getThisGenusOfTheNations(int thisGenus);
//ITERATOR ACCESS
	vector<genus>::iterator beginOfTheNations();
	vector<genus>::iterator endOfTheNations();
//THE ANCESTORS ACCESS
	vector<genus> getTheNations();
	int intSizeOfTheNations() const;
private:
	vector<genus> TheNations;

public:
	void setSaveCommands(char* popc, char* phnc, char* parc, char* nghc, 
		char* mutc, char* genc, char* spsc, char* spCc, char* spdc, 
                char* spic, char* sptc, char* expc);
	char* getIMeanMutabilityCommand() const;
	char* getPopulationCommand() const;
	char* getPhenotypeCommand() const;
	char* getParentCommand() const;
	char* getNeighborCommand() const;
	char* getMutabilityCommand() const;
	char* getGenusCommand() const;
	char* getSpeciesDetailCommand() const;
	char* getSpeciesIndivsCommand() const;
	bool checkCommand(char* command) const;
	int checkCommand() const;
	void writeAncestors(int simu, int gens);
private:
	char* Popc;  //population
	char* Phnc;  //phenotype
	char* Parc;  //parent
	char* Nghc;  //neighbor
	char* Mutc;  //mutability
	char* Genc;  //genus
	char* Spsc;  //species size
	char* SpCc;  //species centroid
	char* Spdc;  //species density
	char* Spic;  //species indivs (identities)
	char* Sptc;  //speciation type (parent2 neighbor2)
  char* Expc;  //experiment type
};
#endif