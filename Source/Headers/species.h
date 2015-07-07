#ifndef SPECIES_H
#define SPECIES_H

#include "population.h"
//population includes: indiv.h
//indiv includes:	landscape.h
//landscape includes: randomc.h & general.h

class species {
public:
	species();
	~species();
	void addToSpecies(int broMontana);
	void setCentroid(double cX, double cY);
	void setDensity(double density);
	void resetSpecies();
	vector<int>::iterator beginOfTheSpecies();
	vector<int>::iterator endOfTheSpecies();
	int getThisIndivOfTheSpecies(int individ) const;
	int intSizeOfTheSpecies() const;
	vector<int> getTheSpecies() const;
	double getCentroidX() const;
	double getCentroidY() const;
	double getDensity() const;
private:
	double CentroidX;
	double CentroidY;
	double Density;
	vector<int> TheSpecies;
};

#endif

/*if(Pati>(po->intSizeOfThePopulation()) || Pati<0) {
				std::cout << "Pati isn't in the population:  " << Pati << std::endl;
				std::cout << "The population only includes " << po->intSizeOfThePopulation();
				std::cout << " indivs." << std::endl;
				std::cout << "The current species has " << (*zeSpp).intSizeOfTheSpecies() << " indivs.";
				std::cout << std::endl;
				std::cin >> Pati;
			}*/
//get each indiv in the species
			/*if(i>(*zeSpp).intSizeOfTheSpecies() || i<0) {
				std::cout << "Pati isn't in the species:  " << Pati << std::endl;
				std::cout << "The species only includes " << (*zeSpp).intSizeOfTheSpecies();
				std::cout << " indivs." << std::endl;
				std::cin >> Pati;
			}*/