#ifndef GENUS_H
#define GENUS_H
/*
	NateSpeciation(indiv,population) must be run AFTER 
	population::setNeighbors(
*/
#include "species.h"
//species include: population.h
//population includes: indiv.h
//indiv includes:	landscape.h
//landscape includes: randomc.h & general.h

class genus {
public:
	genus();
	~genus();
	void NateSpeciation(population* populous);
	void AdamSpeciation(population* populous);
	void Centroids(population* theIndivs);
	void Densities(population* theIndivs);
	vector<species>::iterator beginOfTheGenus();
	vector<species>::iterator endOfTheGenus();
	int intSizeOfTheGenus() const;
	vector<species> getTheGenus() const;
	species getThisSpeciesOfTheGenus(int thisSpecies) const;
	int getSpeciesPlaceInTheGenus(
			vector<species>::iterator theyreHere);//?????????????
	void replaceSpecies(int deezGuys, species daGuys);
	void resetGenus();
private://used in NateSpeciation
	void DiscoveredANewSpecies(species newSpp);
	species combineSpecies(species these, species those);
	void removeSpecies(
			vector<species>::iterator away);
private:
	vector<species> TheGenus;
};

#endif