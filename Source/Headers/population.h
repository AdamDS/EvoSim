#ifndef POPULATION_H
#define POPULATION_H
//reproduction occurs at the ancestors level
#include "indiv.h"
#include <vector>
//indiv includes:	landscape.h
//landscape includes: randomc.h & general.h
using std::vector;

class population {
public:
	population();
	~population();
	int capacityPop();
	void reservePop(int buffpop);
//ALTER THE POPULATION COMPOSITION
	void addToPopulation(indiv newIndiv);
	vector<indiv>::iterator removeIndivFromThePopulation(vector<indiv>::iterator byeIndiv);
	void resetThePopulation();
	void countIndiv();
//SET INDIV INFORMATION AMONG THE POPULATION
	void setNeighbors(landscape* land);
	void replaceIndiv(int disone, indiv* indi);
	indiv getThisIndivOfThePopulation(int thisIndiv);
	indiv getNeighbor1OfThisIndiv(indiv* div1);
	indiv getNeighbor2OfThisIndiv(indiv* div2);
//ITERATOR ACCESS
	vector<indiv>::iterator beginOfThePopulation();
	vector<indiv>::iterator endOfThePopulation();
//THE POPULATION ACCESS
	vector<indiv> getThePopulation();
	int intSizeOfThePopulation() const;
//CALCULATIONS
	double meanMutability();
	int uniqueMutability();
private:
	vector<indiv> ThePopulation;
	int ThePopulationSize;
//Death Dances
public:
	void RussianRoulette(CRandomMersenne* dice);	//carries out random chance kills
	void CliffJumpers(landscape* cliffs);	//carries out killing indiv's that go off the landscape
	void CrowdControl(CRandomMersenne* R);//landscape* resources);
	void setOverPopulationLimit(double limit);
	void setDeathChance(double unfortunate);
  void setExtinctionLimit(int el);
	int getOPKillCount() const;
	int getRRKillCount() const;
	int getCJKillCount() const;
	int getKillCount() const;
  int getExtinctionLimit() const;
	double getOverPopulationLimit() const;
	double getDeathChance() const;
private:
	void adjustIdentity(int rmvd, vector<indiv>::iterator fixIt);
	/*double getDefaultRange(landscape* smallWorld);
	vector<indiv> OverPopulated(int tempi, vector<indiv> findAgain,
									vector<indiv>::iterator currIt);*/
	void NeighborsRestored(vector<indiv> redoThese, double dR);
	bool checkIdentity(int id);
	double OverPopulationLimit;	//overpop = 0.25 in Matlab
	double DeathChance;	//death_max = 0.70 in Matlab
  int ExtinctionLimit;
	int KilledOP;
	int KilledRR;
	int KilledCJ;
	int Killed;
//CHECKS
public:
	void goodNeighbors(vector<indiv>::iterator ref);
//SORT
private:
  void RandomSortThePopulation(vector<indiv>::iterator checkIt);
};

#endif