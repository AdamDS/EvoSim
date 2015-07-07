#include "species.h"

species::species() {
	vector<indiv *> TheSpecies;
	CentroidX = 0;
	CentroidY = 0;
}
species::~species()	{ 
	CentroidX = 0;
	CentroidY = 0;
	TheSpecies.erase(TheSpecies.begin(),TheSpecies.end()); 
}
void species::addToSpecies(int broMontana) {
	TheSpecies.push_back(broMontana);
}
//sets both CentroidX and CentroidY by an average of the Inlaws phenotypes
void species::setCentroid(double cX, double cY) {
	CentroidX = cX;
	CentroidY = cY;
}
void species::setDensity(double density) {	Density = density; }
void species::resetSpecies() {
	CentroidX = 0;
	CentroidY = 0;
	TheSpecies.erase(TheSpecies.begin(),TheSpecies.end());
}
vector<int>::iterator species::beginOfTheSpecies() {
	return TheSpecies.begin();
}
vector<int>::iterator species::endOfTheSpecies() {
	return TheSpecies.end();
}
//get functions
int species::getThisIndivOfTheSpecies(int individ) const {
	return TheSpecies[individ];
}
vector<int> species::getTheSpecies() const { 
	return TheSpecies; 
}
int species::intSizeOfTheSpecies() const {
	return int(TheSpecies.size());
}
double species::getCentroidX() const {	return CentroidX; }
double species::getCentroidY() const {	return CentroidY; }
double species::getDensity() const {	return Density; }
/*void species::RepIsoSpecPeripat2(indiv * Joban, population * populous) {
	//tell whether Joban or neighbors are in a species
	bool Assigned, n1Assigned, n2Assigned;
	//how many species there are & how many indiv's in a species
	int numSpp, numInlaws;
	//Neighbor1 and Neighbor2 identities
	int neigh1ID, neigh2ID;
//	//species place in TheSpecies (zeSpp)
//	int sppJoban, sppneigh1, sppneigh2; 
	//indiv's Neighbor1 and Neighbor2
	indiv * neigh1();
	indiv * neigh2();
	//population::TheSpecies
	vector<species *> * zeSpp; 
	vector<int>::iterator zeSppIt;
	//used as a temporary species in zeSpp
	species * aSpp; 
	vector<int>::iterator aSppIt;
	//Joban's and his neighbors' species
	species * JobansSpp;
	vector<int>::iterator JobanSppIt;
	species * neigh1sSpp;
	vector<int>::iterator neigh1SppIt;
	species * neigh2sSpp;
	vector<int>::iterator neigh2SppIt;
	//start the assignments as unassigned (false)
	Assigned = false;
	n1Assigned = false;
	n2Assigned = false;
	//zeSpp acts as population::TheSpecies
	//TheSpecies is the vector of pointers to each species
	zeSpp = populous->getTheSpecies();//????Scope????
	//get the number of species
	numSpp = populous->getNumberOfSpecies();//????Scope????
	//get Joban's neighbors
	neigh1 = Joban->getNeighbor1(& populous);
	neigh2 = Joban->getNeighbor2(& populous);
//get Joban's species
//and see if neigh1 and neigh2 are included
//if a neighbor is not included, 
//add that neighbor's species
//Must add to the species occurring earliest in zeSpp
//then downcount the total number of species
//(remove neigh1sSpp from zeSpp)
vector<int> myIntVector;
vector<int>::iterator myIntVectorIterator;

// Add some elements to myIntVector
myIntVector.push_back(1);
myIntVector.push_back(4);
myIntVector.push_back(8);

for(myIntVectorIterator = myIntVector.begin(); 
        myIntVectorIterator != myIntVector.end();
        myIntVectorIterator++)
{
    cout<<*myIntVectorIterator<<" ";
    //Should output 1 4 8

	//checking each species in zeSpp
	for(zeSppIt = zeSpp.begin(); zeSppIt != zeSpp.end(); zeSppIt++) {
	//for(int i=0; i<=numSpp; i++) {
		//aSpp is the ith species in zeSpp
		aSpp = zeSppIt;
		//aSpp = zeSpp[i];
		//get the number of indiv's in the aSpp
		//numInlaws = aSpp->getSizeOfSpecies();
		//check each indiv in aSpp
		for(aSppIt = aSpp.begin(); aSppIt != aSpp.end(); aSppIt++) {
		//for(int j=0; j<=numInlaws; j++) {
			//is the address of Joban in a species?
			if(Joban==* aSppIt) {
			//if(Joban==& aSpp[j]) {
				//Joban is somewhere in aSpp
				Assigned = true;
				//get the pointer to Joban's species
				JobansSpp = zeSpp[i];
				if(neigh1Assigned) {
					if(neigh2Assigned) {
						//break checking once Joban, neigh1 and neigh2
						//are found in species already
						i = numSpp;
						j = numInlaws;
					}//if(neigh2Assigned)
				}//if(neigh1Assigned)
			}//if(Joban==&aSpp[j])

			//is the address of neigh1 in a species?
			if(neigh1==& aSpp[j]) {
				neigh1Assigned = true;
				neigh1sSpp = zeSpp[i];
//				afterneigh1 = numInlaws-j;
				sppneigh1 = i;
				if(Assigned) {
					if(neigh2Assigned) {
						//break checking once Joban, neigh1 and neigh2
						//are found in species already
						i = numSpp;
						j = numInlaws;
					}
				}
			}
			//is the address of neigh2 in a species?
			if(neigh2==&aSpp[j]) {
				neigh2Assigned = true;
				neigh2sSpp = zeSpp[i];
//				afterneigh2 = numInlaws-j;
				sppneigh2 = i;
				if(Assigned) {
					if(neigh1Assigned) {
						//break checking once Joban, neigh1 and neigh2
						//are found in species already
						i = numSpp;
						j = numInlaws;
					}//if(Assigned)
				}//if(neigh1Assigned)
			}//if(neigh2==&aSpp[j])
		}//for(int j=0; j<numInlaws; j++)
	}//for(int i=0; i<numSpp; i++)

	
	if(Assigned && neigh1Assigned && neigh2Assigned) {
	//all three are already assigned somewhere	
		if(Jobansspp!=neigh1sspp) {
		//Joban is not in neigh1's species
			if(Jobansspp!=neigh2sspp) {
			//Joban is not in neigh1's species
			//Joban is not in neigh2's species either
				if(neigh1sspp!=neigh2sspp) {
				//Joban is not in neigh1's species
				//neigh1 is not in neigh2's species
				//neigh2 is not in Joban's species 
				//(Joban's species needs to include neigh1's species)
				//(Joban's species needs to include neigh2's species)
					Jobansspp.insert(Jobansspp.end(),neigh1sspp.begin(),neigh1sspp.end());
					Jobansspp.insert(Jobansspp.end(),neigh2sspp.begin(),neigh2sspp.end());
					zeSpp.removeSpecies(sppneigh1);
					zeSpp.removeSpecies(sppneigh2-1);
				}else {
				//Joban is not in neigh1's species
				//neigh1 is in neigh2's species
				//neigh2 is not in Joban's species 
				//(Joban's species needs to include neigh1's and neigh2's species)
					Jobansspp.insert(Jobansspp.end(),neigh1sspp.begin(),neigh1sspp.end());
					zeSpp.removeSpecies(sppneigh1);
				}
			}else {
			//Joban is not in neigh1's species
			//neigh2 is in Joban's species 
				if(neigh1sspp!=neigh2sspp) {
				//Joban is not in neigh1's species
				//neigh1 is not in neigh2's species
				//neigh2 is in Joban's species 
				//(Joban's and neigh2's species needs to include neigh1's species)
					Jobansspp.insert(Jobansspp.end(),neigh1sspp.begin(),neigh1sspp.end());
					zeSpp.removeSpecies(sppneigh1);
				}//else {
				//Joban is not in neigh1's species
				//neigh1 is in neigh2's species
				//neigh2 is in Joban's species 
				//(this case should never happen)
				//}
			}
		}else {
		//Joban is in neigh1's species
			if(Jobasspp!=neigh2sspp) {
			//Joban is in neigh1's species
			//Joban is not in neigh2's species
			//therefore neigh2 is not in neigh1's species
			//(Joban's and neigh1's species needs to include neigh2's species
				Jobansspp.insert(Jobansspp.end(),neigh2sspp.begin(),neigh2sspp.end());
				zeSpp.removeSpecies(sppneigh2);
			}//else {
			//Joban is in neigh1's species
			//Joban is in neigh2's species
			//therefore neigh1 is in neigh2's species
			//(each are already in the same species)
			//}
		}
	}else if(Assigned && neigh1Assigned) {
	//neigh2 is not yet in a species
		if(Jobansspp!=neigh1sspp) {
		//Joban is not in neigh1's species
			Jobansspp.insert(Jobansspp.end(),neigh1sspp.begin(),neigh1sspp.end());
			zeSpp.removeSpecies(sppneigh1);
			Jobansspp.addToSpecies(neigh2);
		}else {
		//Joban is in neigh1's species
			Jobansspp.addToSpecies(neigh2);
		}
	}else if(Assigned && neigh2Assigned){
	//neigh1 is not yet in a species
		if(Jobansspp!=neigh2sspp) {
		//Joban is not in neigh2's species
			Jobansspp.insert(Jobansspp.end(),neigh2sspp.being(),neigh2sspp.end());
			zeSpp.removeSpecies(sppneigh2);
			Jobansspp.addToSpecies(neigh1);
		}else {
		//Joban is in neigh2's species
			Jobansspp.addToSpecies(neigh1);
		}
	}else if(neigh1Assigned && neigh2Assigned) {
	//Joban is not yet in a species
		if(neigh1sspp!=neigh2sspp) {
		//neigh1 is not in neigh2's species
			neigh1sspp.insert(neigh1sspp.end(),neigh2sspp.begin(),neigh2sspp.end());
			zeSpp.removeSpecies(sppneigh2);
			neigh1sspp.addToSpecies(Joban);
		}else {
		//neigh1 is in neigh2's species
			neigh1sspp.addToSpecies(Joban);
		}
	}else if(Assigned) {
	//neigh1 and neigh2 are not in any species yet
		Jobansspp.addToSpecies(neigh1);
		Jobansspp.addToSpecies(neigh2);
	}else if(neigh1Assigned) {
	//Joban and neigh2 are not in any species yet
		neigh1sspp.addToSpecies(Joban);
		neigh1sspp.addToSpecies(neigh2);
	}else if(neigh2Assigned) {
	//Joban and neigh1 are not in any species yet
		neigh2sspp.addToSpecies(Joban);
		neigh2sspp.addToSpecies(neigh1);
	}else {
	//no one is assigned to a species yet
		populous.DiscoveredANewSpecies(Jobansspp);
		Jobansspp.addToSpecies(neigh1sspp);
		Jobansspp.addToSpecies(neigh2sspp);
	}
}*/


//Old/unnecessary functions
/*bool species::AreYouRelated(indiv Bob) {
	
}*/

/*void species::setInlaw(indiv inlaw) {
	Inlaws[SizeOfSpecies] = &inlaw;//?????????????????????????????
//	++SizeOfSpecies;
}*/

/*void species::setCentroidX(indiv &group) {
	size = *group.getSize();
	double *x;
	double *y;
	x = new double[size];
	y = new double[size];
	int comparisons, k;
	for(int i = 0; i<size; i++) {
		x[i] = group.getInlaw(i).getPhenotypeX();//???????????????????
		y[i] = group.getInlaw(i).getPhenotypeY();//???????????????????
	}
	comparisons = size*(size+1)/2;
	k = 0;
	for(int i = 0; i<comparisons; i++) {
		for(int j = i+1; j<size; j++) {
			distx[k] = (x[i]^2 + x[j]^2)^0.5;
			disty[k] = (y[i]^2 + y[j]^2)^0.5;
			k++;
		}
	}
	CentroidX = 
}*/


/*void species::setCentroidY(indiv *group) {
	size = group.getSizeOfSpecies();
	
	CentroidY = 
}*/