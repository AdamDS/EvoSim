#ifndef INDIV_H
#define INDIV_H

#include "landscape.h"
//landscape includes: randomc.h & general.h

class indiv {
public:
    indiv();
    ~indiv();
    void setBaby(int babeid, int par1, int par2,
            double babeX, double babeY, double parMR);
    void setBaby(int babeid, int par1,
            double babeX, double babeY, double parMR);
    //void setIndiv(int ident, double ex, double why, int cede, landscape *carto);
    void setIndiv(int ident, landscape *carto, double randomX,
            double randomY, double rmma);
    //INDIV'S IDENTITY
public:
    void setIdentity(int thisis); //set indiv identity
    int getIdentity() const; //get indiv identity among it's generation
private:
    int Identity; //indiv's identity
    //PARENT IDENTITIES
public:
    //set indiv's (type 1) parent
    void setParent1Identity(int parent1id);
    //set indiv's (type 2) parents
    void setParent2Identity(int parent2id);
    //get indiv's parent 1 identity
    int getParent1Identity() const;
    //get indiv's parent 2 identity
    int getParent2Identity() const;
private:
    //indiv's mutation rate determining parent identity
    int Parent1Identity;
    //indiv's other parent identity
    int Parent2Identity;
    //NEIGHBOR IDENTITIES AND DISTANCES TO INDIV
public:
    //set and get Neighbor's identity
    void setNeighbor1Identity(int neighbor1ident);
    void setNeighbor2Identity(int neighbor2ident);
    int getNeighbor1Identity() const;
    int getNeighbor2Identity() const;
    //set and get Neighbor's distance from indiv
    void setNeighbor1Distance(double dist2Mate);
    void setNeighbor2Distance(double dist2ImmSppEdge);
    double getNeighbor1Distance() const;
    double getNeighbor2Distance() const;
private:
    //identity of indiv's nearest neighbor
    int Neighbor1Identity;
    //identity of indiv's second closest neighbor
    int Neighbor2Identity;
    double Neighbor1Distance;
    double Neighbor2Distance;
    //INDIV'S PHENOTYPE LOCATION
public:
    //set indiv's phenotype x,y-coordinates - only for initialization of first generation
    void setPhenotypeCoordinate(landscape *land,
            double randX, double randY);
    double getPhenotypeX() const; //get indiv's phenotype x-coordinate
    double getPhenotypeY() const; //get indiv's phenotype y-coordinate
    void setPhenotypeX(double phenox);
    void setPhenotypeY(double phenoy);
private:
    double PhenotypeX; //indiv's phenotype x-coordinate
    double PhenotypeY; //indiv's phenotype y-coordinate
    //INDIV'S MUTABILITY (BIRTH NOISE)
public:
    //void initMutability(double mutr);
    void setMutability(double mutatRat); //landscape *map); //set indiv's mutation rate - only for initialization of first generation
    double getMutability() const; //get indiv's mutation rate
private:
    double Mutability; //indiv's mutation rate
};

#endif