#include "genus.h"

genus::genus() {
  vector<species> TheGenus;
}

genus::~genus() {
  TheGenus.erase(TheGenus.begin(), TheGenus.end());
}

void genus::NateSpeciation(population* populous) {
  bool JobanAssigned, neigh1Assigned, neigh2Assigned;
  indiv Joban;
  species aSpp;
  species JSpp;
  species n1Spp;
  species n2Spp;
  //*TGIt is a species from TheGenus
  vector<species>::iterator TGIt;
  //*aSppIt is an indiv from *TGIT
  vector<int>::iterator aSppIt;
  //*JTGIt is Joban's species
  vector<species>::iterator JTGIt;
  //*n1TGIt is neigh1's species
  vector<species>::iterator n1TGIt;
  //*n2SppIt is neigh2's species
  vector<species>::iterator n2TGIt;
  int TGi = 0;
  int aSppi = 0;
  int JTGi = -1;
  int n1TGi = -2;
  int n2TGi = -3;
  int lastIndiv = populous->intSizeOfThePopulation();
  int aid;
  int Jid;
  int n1id;
  int n2id;
  //GO TO EACH INDIV OF THE POPULATION
  for (int populousi = 0; populousi < lastIndiv; populousi++) {
    TGIt = TheGenus.begin();
    TGi = 0;
    JobanAssigned = false;
    neigh1Assigned = false;
    neigh2Assigned = false;
    Joban = populous->getThisIndivOfThePopulation(populousi);
    Jid = Joban.getIdentity();
    n1id = Joban.getNeighbor1Identity();
    n2id = Joban.getNeighbor2Identity();
    //GO TO EACH SPECIES OF THE GENUS
    for (TGIt; TGIt < TheGenus.end(); TGIt++) {
      aSpp = getThisSpeciesOfTheGenus(TGi);
      aSppIt = aSpp.beginOfTheSpecies();
      aSppi = 0;
      //GO TO EACH INDIV OF THE SPECIES
      for (aSppIt; aSppIt < (aSpp.endOfTheSpecies()); aSppIt++) {
        //check each indiv in aSpp
        aid = *aSppIt;
        if (Jid == aid) {
          //Joban is at aSppIt in aSpp
          JobanAssigned = true;
          //*TGIt;
          JSpp = getThisSpeciesOfTheGenus(TGi);
          //assign current species iterator
          JTGIt = TGIt;
          //getSpeciesPlaceInTheGenus(JTGIt);
          JTGi = TGi;
          //get the pointer to Joban's species
          if (neigh1Assigned && neigh2Assigned) {
            //break checking once Joban, neigh1 and neigh2
            //are found in species already
            aSppIt = aSpp.endOfTheSpecies() - 1;
            TGIt = TheGenus.end() - 1;
          }
        } else
          //is the address of neigh1 in a species?
          if (n1id == aid) {
            neigh1Assigned = true;
            n1Spp = getThisSpeciesOfTheGenus(TGi);
            n1TGIt = TGIt;
            //getSpeciesPlaceInTheGenus(n1TGIt);
            n1TGi = TGi;
            if (JobanAssigned && neigh2Assigned) {
              aSppIt = aSpp.endOfTheSpecies() - 1;
              TGIt = TheGenus.end() - 1;
            }
          } else
            //is the address of neigh2 in a species?
            if (n2id == aid) {
              neigh2Assigned = true;
              n2Spp = getThisSpeciesOfTheGenus(TGi);
              n2TGIt = TGIt;
              //getSpeciesPlaceInTheGenus(n2TGIt);
              n2TGi = TGi;
              if (JobanAssigned && neigh1Assigned) {
                aSppIt = aSpp.endOfTheSpecies() - 1;
                TGIt = TheGenus.end() - 1;
              }
            }
      }//end for aSppIt
      TGi++;
    }//end for TGIt
    //COMBINE SPECIES or ADD TO SPECIES or DISCOVER A NEW SPECIES
    if (JobanAssigned && neigh1Assigned && neigh2Assigned) {
      //all three are already assigned somewhere	
      if (JTGi != n1TGi) {
        //Joban is not in neigh1's species
        if (JTGi != n2TGi) {
          //Joban is not in neigh1's species
          //Joban is not in neigh2's species either
          if (n1TGi != n2TGi) {
            //each are in separate species
            //Joban's species needs to include neigh1's species
            //Joban's species needs to include neigh2's species
            if (n1TGi < n2TGi) {
              JSpp = combineSpecies(JSpp, n1Spp);
              JSpp = combineSpecies(JSpp, n2Spp);
              replaceSpecies(JTGi, JSpp);
              removeSpecies(n2TGIt); //remove later spp
              removeSpecies(n1TGIt); //remove earlier spp
            } else {
              JSpp = combineSpecies(JSpp, n2Spp);
              JSpp = combineSpecies(JSpp, n1Spp);
              replaceSpecies(JTGi, JSpp);
              removeSpecies(n1TGIt); //remove later spp
              removeSpecies(n2TGIt); //remove earlier spp
            }
          } else {
            //Joban is not in neigh1's species
            //neigh1 is in neigh2's species
            //neigh2 is not in Joban's species 
            //Joban's species needs to include (neigh1 & neigh2)'s species
            JSpp = combineSpecies(JSpp, n1Spp);
            replaceSpecies(JTGi, JSpp);
            removeSpecies(n1TGIt);
          }
        } else {
          //Joban is not in neigh1's species
          //neigh2 is in Joban's species 
          if (n1TGi != n2TGi) {
            //Joban is not in neigh1's species
            //neigh1 is not in neigh2's species
            //neigh2 is in Joban's species 
            //(Joban & neigh2)'s species needs to include neigh1's species
            JSpp = combineSpecies(JSpp, n1Spp);
            replaceSpecies(JTGi, JSpp);
            removeSpecies(n1TGIt);
          }//else {
          //Joban is not in neigh1's species
          //neigh1 is in neigh2's species
          //neigh2 is in Joban's species 
          //(this case should never happen)
          //}
        }
      } else {
        //Joban is in neigh1's species
        if (JTGi != n2TGi) {
          //Joban is in neigh1's species
          //Joban is not in neigh2's species
          //therefore neigh2 is not in neigh1's species
          //(Joban & neigh1)'s species needs to include neigh2's species
          JSpp = combineSpecies(JSpp, n2Spp);
          replaceSpecies(JTGi, JSpp);
          removeSpecies(n2TGIt);
        }//else {
        //Joban is in neigh1's species
        //Joban is in neigh2's species
        //therefore neigh1 is in neigh2's species
        //(each are already in the same species)
        //}
      }
    } else if (JobanAssigned && neigh1Assigned) {
      //neigh2 is not yet in a species
      if (JTGi != n1TGi) {
        //Joban is not in neigh1's species
        //Joban's species needs to include neigh1's species and neigh2
        JSpp = combineSpecies(JSpp, n1Spp);
        JSpp.addToSpecies(n2id);
        replaceSpecies(JTGi, JSpp);
        removeSpecies(n1TGIt);
      } else {
        //Joban is in neigh1's species
        //(Joban & neigh1)'s species needs to include neigh2
        JSpp.addToSpecies(n2id);
        replaceSpecies(JTGi, JSpp);
      }
    } else if (JobanAssigned && neigh2Assigned) {
      //neigh1 is not yet in a species
      if (JTGi != n2TGi) {
        //Joban is not in neigh2's species
        //Joban's species needs to include neigh2's species and neigh1
        JSpp = combineSpecies(JSpp, n2Spp);
        JSpp.addToSpecies(n1id);
        replaceSpecies(JTGi, JSpp);
        removeSpecies(n2TGIt);
      } else {
        //Joban is in neigh2's species
        //(Joban & neigh2)'s species needs to include neigh1
        JSpp.addToSpecies(n1id);
        replaceSpecies(JTGi, JSpp);
      }
    } else if (neigh1Assigned && neigh2Assigned) {
      //Joban is not yet in a species
      if (n1TGi != n2TGi) {
        //neigh1 is not in neigh2's species
        //neigh1's species needs to include neigh2's species and Joban
        n1Spp = combineSpecies(n1Spp, n2Spp);
        n1Spp.addToSpecies(Jid);
        replaceSpecies(n1TGi, n1Spp);
        removeSpecies(n2TGIt);
      } else {
        //neigh1 is in neigh2's species
        //(neigh1 & neigh2)'s species needs to include Joban
        n1Spp.addToSpecies(Jid);
        replaceSpecies(n1TGi, n1Spp);
      }
    } else if (JobanAssigned) {
      //neigh1 and neigh2 are not in any species yet
      //Joban's species needs to include neigh1 and neigh2
      JSpp.addToSpecies(n1id);
      JSpp.addToSpecies(n2id);
      replaceSpecies(JTGi, JSpp);
    } else if (neigh1Assigned) {
      //Joban and neigh2 are not in any species yet
      //neigh1's species needs to include Joban and neigh2
      n1Spp.addToSpecies(Jid);
      n1Spp.addToSpecies(n2id);
      replaceSpecies(n1TGi, n1Spp);
    } else if (neigh2Assigned) {
      //Joban and neigh1 are not in any species yet
      //neigh2's species needs to include Joban and neigh1
      n2Spp.addToSpecies(Jid);
      n2Spp.addToSpecies(n1id);
      replaceSpecies(n2TGi, n2Spp);
    } else {
      //no one is assigned to a species yet
      //Joban, neigh1, and neigh2 are an entirely new species!
      JSpp.addToSpecies(Jid);
      JSpp.addToSpecies(n1id);
      JSpp.addToSpecies(n2id);
      DiscoveredANewSpecies(JSpp);
    }//end assignments
    JTGi = -1;
    n1TGi = -2;
    n2TGi = -3;
    JSpp.resetSpecies();
    n1Spp.resetSpecies();
    n2Spp.resetSpecies();
  }//end populousi
}

void genus::AdamSpeciation(population* populous) {
  bool JobanAssigned, neigh1Assigned;
  indiv Joban;
  species aSpp;
  species JSpp;
  species n1Spp;
  //*TGIt is a species from TheGenus
  vector<species>::iterator TGIt;
  //*aSppIt is an indiv from *TGIT
  vector<int>::iterator aSppIt;
  //*JTGIt is Joban's species
  vector<species>::iterator JTGIt;
  //*n1TGIt is neigh1's species
  vector<species>::iterator n1TGIt;
  int TGi = 0;
  int aSppi = 0;
  int JTGi = -1;
  int n1TGi = -2;
  int lastIndiv = populous->intSizeOfThePopulation();
  int aid = -3;
  int Jid = -4;
  int n1id = -5;
  //GO TO EACH INDIV OF THE POPULATION
  for (int populousi = 0; populousi < lastIndiv; populousi++) {
    TGIt = TheGenus.begin();
    TGi = 0;
    JobanAssigned = false;
    neigh1Assigned = false;
    Joban = populous->getThisIndivOfThePopulation(populousi);
    Jid = Joban.getIdentity();
    n1id = Joban.getNeighbor1Identity();
    //GO TO EACH SPECIES OF THE GENUS
    for (TGIt; TGIt < TheGenus.end(); TGIt++) {
      aSpp = getThisSpeciesOfTheGenus(TGi);
      aSppIt = aSpp.beginOfTheSpecies();
      aSppi = 0;
      //GO TO EACH INDIV OF THE SPECIES
      for (aSppIt; aSppIt < (aSpp.endOfTheSpecies()); aSppIt++) {
        //check each indiv in aSpp
        aid = *aSppIt;
        if (Jid == aid) {
          //Joban is at aSppIt in aSpp
          JobanAssigned = true;
          //*TGIt;
          JSpp = getThisSpeciesOfTheGenus(TGi);
          //assign current species iterator
          JTGIt = TGIt;
          //getSpeciesPlaceInTheGenus(JTGIt);
          JTGi = TGi;
          //get the pointer to Joban's species
          if (neigh1Assigned) {
            //break checking once Joban, neigh1 and neigh2
            //are found in species already
            aSppIt = aSpp.endOfTheSpecies() - 1;
            TGIt = TheGenus.end() - 1;
          }
        } else
          //is the address of neigh1 in a species?
          if (n1id == aid) {
            neigh1Assigned = true;
            n1Spp = getThisSpeciesOfTheGenus(TGi);
            n1TGIt = TGIt;
            //getSpeciesPlaceInTheGenus(n1TGIt);
            n1TGi = TGi;
            if (JobanAssigned) {
              aSppIt = aSpp.endOfTheSpecies() - 1;
              TGIt = TheGenus.end() - 1;
            }
          }
      }//end for aSppIt
      TGi++;
    }//end for TGIt
    //COMBINE SPECIES or ADD TO SPECIES or DISCOVER A NEW SPECIES
    if (JobanAssigned && neigh1Assigned) {
      //all three are already assigned somewhere	
      if (JTGi != n1TGi) {
        //Joban is not in neigh1's species
        //Joban's species needs to include neigh1's species
        if (JTGi < n1TGi) {
          JSpp = combineSpecies(JSpp, n1Spp);
          replaceSpecies(JTGi, JSpp);
          removeSpecies(n1TGIt);
        } else {
          n1Spp = combineSpecies(n1Spp, JSpp);
          replaceSpecies(n1TGi, JSpp);
          removeSpecies(JTGIt);
        }
      }
    } else if (JobanAssigned) {
      //Joban's species needs to include neigh1;
      JSpp.addToSpecies(n1id);
      replaceSpecies(JTGi, JSpp);
    } else if (neigh1Assigned) {
      //neigh1's species needs to include Joban
      n1Spp.addToSpecies(Jid);
      replaceSpecies(n1TGi, n1Spp);
    } else {
      //no one is assigned to a species yet
      //Joban and neigh1 are an entirely new species!
      JSpp.addToSpecies(Jid);
      JSpp.addToSpecies(n1id);
      DiscoveredANewSpecies(JSpp);
    }//end assignments
    JTGi = -1;
    n1TGi = -2;
    JSpp.resetSpecies();
    n1Spp.resetSpecies();
  }//end populousi
}

void genus::DiscoveredANewSpecies(species newSpp) {
  TheGenus.push_back(newSpp);
}

species genus::combineSpecies(species these, species those) {
  vector<int>::iterator thoIt;
  thoIt = those.beginOfTheSpecies();
  for (thoIt; thoIt < (those.endOfTheSpecies()); thoIt++) {
    these.addToSpecies(*thoIt);
  }
  return these;
}

void genus::removeSpecies(vector<species>::iterator away) {
  away = TheGenus.erase(away);
}

void genus::replaceSpecies(int deezGuys, species daGuys) {
  TheGenus[deezGuys] = daGuys;
}

void genus::Centroids(population* theIndivs) {
  double xindiv, yindiv, xall, yall;
  double centroidX, centroidY;
  vector<species>::iterator zeSpp = TheGenus.begin();
  indiv zeIndiv;
  vector<int>::iterator zeIt;
  int a;
  for (zeSpp; zeSpp < (TheGenus.end()); zeSpp++) {
    xall = 0;
    yall = 0;
    centroidX = 0;
    centroidY = 0;
    zeIt = (*zeSpp).beginOfTheSpecies();
    for (zeIt; zeIt < ((*zeSpp).endOfTheSpecies()); zeIt++) {
      if (*zeIt < 0) {
        cout << *zeIt << " does not exist." << endl;
        cin >> a;
      }
      if (*zeIt < 0 || *zeIt > (theIndivs->intSizeOfThePopulation())) {
        cout << "centroids has a bug! " << *zeIt << endl;
        cin >> a;
      }
      zeIndiv = theIndivs->getThisIndivOfThePopulation(*zeIt);
      //get indiv's phenotype coordinate
      xindiv = zeIndiv.getPhenotypeX();
      yindiv = zeIndiv.getPhenotypeY();
      //add each indiv's phenotype coordinates with the related Inlaws
      xall = xindiv + xall;
      yall = yindiv + yall;
    }//indiv's in the species
    //calculate the average phenotype coordinate
    centroidX = xall / ((*zeSpp).intSizeOfTheSpecies());
    centroidY = yall / ((*zeSpp).intSizeOfTheSpecies());
    (*zeSpp).setCentroid(centroidX, centroidY);
  }//species of the genus
}

void genus::Densities(population* theIndivs) {
  int N;
  double x, y, distances, dens;
  vector<species>::iterator zeSpp = beginOfTheGenus();
  vector<int>::iterator i1, i2;
  indiv indiv1, indiv2;
  while (zeSpp < endOfTheGenus()) {
    distances = 0;
    i1 = (*zeSpp).beginOfTheSpecies();
    while (i1 < ((*zeSpp).endOfTheSpecies())) {
      indiv1 = theIndivs->getThisIndivOfThePopulation(*i1);
      i2 = ((*zeSpp).beginOfTheSpecies())++;
      while (i2 < (*zeSpp).endOfTheSpecies()) {
        indiv2 = theIndivs->getThisIndivOfThePopulation(*i2);
        //get zeIndiv's phenotype coordinate
        x = indiv1.getPhenotypeX();
        x = x - indiv2.getPhenotypeX();
        x = pow(x, 2);
        y = indiv1.getPhenotypeY();
        y = y - indiv2.getPhenotypeY();
        y = pow(y, 2);
        distances = pow((x + y), 0.5) + distances;
        i2++;
      }//indiv2 in the species
      i1++;
    }//indiv1 in the species
    //calculate the average phenotype coordinate
    N = (*zeSpp).intSizeOfTheSpecies();
    dens = distances / ((N * (N - 1)) / 2);
    (*zeSpp).setDensity(dens);
    zeSpp++;
  }//zeSpp of the genus
}

void genus::resetGenus() {
  vector<species>::iterator restartGenus;
  restartGenus = TheGenus.erase(TheGenus.begin(), TheGenus.end());
}

vector<species>::iterator genus::beginOfTheGenus() {
  return TheGenus.begin();
}

vector<species>::iterator genus::endOfTheGenus() {
  return TheGenus.end();
}

int genus::intSizeOfTheGenus() const {
  return int(TheGenus.size());
}

vector<species> genus::getTheGenus() const {
  return TheGenus;
}

int genus::getSpeciesPlaceInTheGenus(vector<species>::iterator theyreHere) {
  vector<species>::iterator findThem;
  findThem = TheGenus.begin();
  int countem = 0;
  for (findThem; findThem < (TheGenus.end()); findThem++) {
    if (findThem != theyreHere) {
      countem++;
    } else {
      findThem = (TheGenus.end()) - 1;
    }
  }
  return countem;
}

species genus::getThisSpeciesOfTheGenus(int thisSpecies) const {//std::vector<species *>::iterator thisSpecies) {
  return TheGenus[thisSpecies];
}