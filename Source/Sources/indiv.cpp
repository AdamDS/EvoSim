#include "indiv.h"

//default constructor for indiv
indiv::indiv() { 
	//default Identities to -1 since no indiv has a negative id
	setIdentity(-1);
	setNeighbor1Identity(-1);
	setNeighbor2Identity(-1);
	setParent1Identity(-1);
	setParent2Identity(-1);
	//default off of fitness landscape (CliffJumpers will kill those
	//	that are not set properly
	setPhenotypeX(-1);
	setPhenotypeY(-1);
	//default requires a value for mutation rate (I'm picking zero)
	setMutability(0);
	//default to some large, ridiculous distance
	setNeighbor1Distance(1000000);
	setNeighbor2Distance(1000000);
}
//destructor for indiv
indiv::~indiv() {	0; }
void indiv::setIndiv(int ident, landscape *cartographer, 
						 double randomX, double randomY, double rmma) {
	setIdentity(ident);
	setNeighbor1Identity(-1);
	setNeighbor2Identity(-1);
	setParent1Identity(-1);
	setParent2Identity(-1);
	setPhenotypeCoordinate(cartographer,randomX,randomY);
	setMutability(rmma);
	double max = cartographer->getMaximumDistance();
	setNeighbor1Distance(max);
	setNeighbor2Distance(max);
}
void indiv::setBaby(int babeid, int par1, int par2, double babeX, double babeY, double parMR) {
	setIdentity(babeid);
	setParent1Identity(par1);
	setParent2Identity(par2);
	setPhenotypeX(babeX);
	setPhenotypeY(babeY);
	setNeighbor1Identity(-1);
	setNeighbor2Identity(-1);
	setNeighbor1Distance(101010);
	setNeighbor2Distance(101010);
	setMutability(parMR);
}
void indiv::setBaby(int babeid, int par1, double babeX, double babeY, double parMR) {
	setIdentity(babeid);
	setParent1Identity(par1);
	setParent2Identity(-1);
	setPhenotypeX(babeX);
	setPhenotypeY(babeY);
	setNeighbor1Identity(-1);
	setNeighbor2Identity(-1);
	setNeighbor1Distance(101010);
	setNeighbor2Distance(101010);
	setMutability(parMR);
}
//INDIV'S IDENTITY
void indiv::setIdentity(int thisis) { Identity = thisis; }
int indiv::getIdentity() const { return Identity; }
//PARENT IDENTITIES
void indiv::setParent1Identity(int parent1id) { Parent1Identity = parent1id; }
void indiv::setParent2Identity(int parent2id) { Parent2Identity = parent2id; }
int indiv::getParent1Identity() const { return Parent1Identity; }
int indiv::getParent2Identity() const { return Parent2Identity; }
//NEIGHBOR IDENTITIES AND DISTANCES TO INDIV
void indiv::setNeighbor1Identity(int neighbor1ident) { 
	Neighbor1Identity = neighbor1ident; 
}
void indiv::setNeighbor2Identity(int neighbor2ident) { 
	Neighbor2Identity = neighbor2ident; 
}
void indiv::setNeighbor1Distance(double dist2Mate) {
	Neighbor1Distance = dist2Mate;
}
void indiv::setNeighbor2Distance(double dist2ImmSppEdge) {
	Neighbor2Distance = dist2ImmSppEdge;
}
int indiv::getNeighbor1Identity() const { return Neighbor1Identity; }
int indiv::getNeighbor2Identity() const { return Neighbor2Identity; }
double indiv::getNeighbor1Distance() const { return Neighbor1Distance; }
double indiv::getNeighbor2Distance() const { return Neighbor2Distance; }
//INDIV'S PHENOTYPE LOCATION
void indiv::setPhenotypeX(double phenox) { PhenotypeX = phenox; }
void indiv::setPhenotypeY(double phenoy) { PhenotypeY = phenoy; }
void indiv::setPhenotypeCoordinate(landscape* land, 
																	 double randX, double randY) {
	double MaxX = land->getMaxXOfTheLandscape();
	double MaxY = land->getMaxYOfTheLandscape();
	setPhenotypeX(MaxX*randX);
	setPhenotypeY(MaxY*randY);
}
double indiv::getPhenotypeX() const { return PhenotypeX; }
double indiv::getPhenotypeY() const { return PhenotypeY; }
void indiv::setMutability(double mutatRat) {
	Mutability = mutatRat;
}
double indiv::getMutability() const { return Mutability; }



//UNUSED, OLD CODE

//INDIV'S MUTATION RATE (BIRTH NOISE)
//void indiv::initMutability(CRandomMersenne mutr) {//int seeder) {	//NEED TO SEED PROPERLY!
//	//CRandomMersenne mutr(seeder);// = map->getRandom();
//	Mutability = mutr.Random();	//CRandomMersenne class
//	//map->setRandom(mutr);
//}

//int indiv::getIndivsSpecies() const { return Species; }

/*void indiv::setNearestNeighbors(landscape land, population pops) {
	double currX, currY;
	double temp1X, temp1Y;
	double temp2X, temp2Y;
	double currDist, tempDist
	indiv *tempN = new indiv();
	std::vector<indiv>::iterator popsIt = pops.beginOfThePopulation;
	//CHECK TO MAKE SURE ALL IS WELL
//	try(size<3) { 
//	}catch {
//	}
	currX = getPhenotypeX();
	currY = getPhenotypeY();
	//set all other indiv distances 1 unit farther than the maximum
	//need to find the minimum distances, but those are found later
	temp1Dist = 1+((land.getMaxPhenoX())^2+(land.getMaxPhenoY())^2)^0.5;
	temp2Dist = temp1Dist;
	for(popsIt; popsIt<pops.endOfThePopulation; popsIt++) {
		tempN = *Pop[*popsIt];//????return pointer to an indiv by passing reference of iterator?
		tempX = tempN->getPhenotypeX();
		tempY = tempN->getPhenotypeY();
		currDist = ((currX-tempX)^2 + (currY-tempY)^2)^(0.5); 
		//currID!=i ensures nothing serious happens when tempN is the reference indiv
		if(currID!=i && currDist<tempDist) {
			setNeighbor1(i); //Neighbor1's Identity is i
			temp1Dist = currDist; //reset nearest neighbor distance
		}else if(currID!=i && currDist<tempDist) {
			setNeighbor1(2); //Neighbor2's Identity is i
			temp2Dist = currDist; //reset second closest neighbor distance
		}
	}
}*/

/*void indiv::setSpecies(int species) {
	Species = species;
}*/

/*//set indiv values with no parent ID (type 0)
indiv::setIndiv0(int gen, int id, int n1, double px, double py, double mutable) {
	setGeneration(gen); //Generation
	setIdentity(id); //Identity
	setNeighbor1(n1); //Neighbor1;
	if(gen==1) {
		setPhenotypeCoordinate(px,py);	//PhenotypeX, PhenotypeY
		setMutability(ma); //Mutability
	}else {
		
	}
}*/

/*//set indiv values with one parent ID (type 1)
indiv::setIndiv1(int gen, int id, double px, double py, double mutable, int par1id) {
	setGeneration(gen); //Generation
	setIdentity(id); //Identity
	setParentIdentity(par1id); //Parent1Identity
	if(gen==1) {
		setPhenotypeCoordinate(px,py); //PhenotypeX,PhenotypeY
		setMutability(ma); //Mutability
	}else {
//?		indiv.getParIDs();
	}
}*/

/*//set indiv values with two parent IDs (type 2)
indiv::setIndiv2(int gen, int id, double px, double py, double mutable, int par1id, int par2id) {
	setGeneration(gen); //Generation
	setIdentity(id); //Identity
	setParentIdentities(par1id,par2id); //Parent1Identity,Parent2Identity
	if(gen==1) {
		setPhenotypeCoordinate(px,py);	//PhenotypeX,PhenotypeY
		setMutability(ma);				
	}else {
//?		indiv.getParIDs();
	}
}*/

/*void indiv::setMutationRange(double low, double high) {
	double mean_ma = 1;
	while( mean_ma > high || mean_ma < low ) {
		for( int i = 0; i<IPOP; i++ ) {
//?			CMersenneRandom bn;
//?			population().setMutRate(bn.Random());
		}
		mean_ma = MeanMutability(population());
	}
}*/
