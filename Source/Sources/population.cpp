#include "population.h"

population::population() {
  vector<indiv> ThePopulation;
  ThePopulationSize = 0;
  Killed = 0;
  KilledOP = 0;
  KilledRR = 0;
  KilledCJ = 0;
  ExtinctionLimit = 3;
}

population::~population() {
  ThePopulation.erase(ThePopulation.begin(), ThePopulation.end());
}

void population::addToPopulation(indiv newIndiv) {
  ThePopulation.push_back(newIndiv);
  ThePopulationSize++;
}

vector<indiv>::iterator population::removeIndivFromThePopulation(
  vector<indiv>::iterator byeIndiv) {
    ThePopulationSize--;
    Killed++;
    return ThePopulation.erase(byeIndiv);
}

void population::resetThePopulation() {
  vector<indiv>::iterator redo;
  ThePopulationSize = 0;
  Killed = 0;
  KilledOP = 0;
  KilledRR = 0;
  KilledCJ = 0;
  redo = ThePopulation.erase(ThePopulation.begin(), ThePopulation.end());
}

void population::setNeighbors(landscape* land) {

  bool double_checking;
  vector<indiv>::iterator currIt, tempIt;
  int curri, n1Iden, n2Iden, tempi;
  double currX, currY, currDist;
  double tempX, tempY, n1Dist;
  int r = 0;
  double maxDist;
  maxDist = land->getMaximumDistance();
  double range1[8] = {1, 2, 4, 8, 16, 32, maxDist, maxDist};
  double range2[9] = {0, 1.5, 2.9, 5.7, 11.4, 22.7, maxDist, maxDist, maxDist};
  double upperX, lowerX, upperY, lowerY;
  int iSOTP = intSizeOfThePopulation();
  double *Xs = new double[iSOTP];
  double *Ys = new double[iSOTP];

  double_checking = false;

  //can optimize this function by having a density dependence on which method to use
  //for determining nearest neighbors and their distances

  tempIt = beginOfThePopulation();
  for (int t = 0; t < intSizeOfThePopulation(); t++) {
    Xs[t] = (*tempIt).getPhenotypeX();
    Ys[t] = (*tempIt).getPhenotypeY();
    tempIt++;
  }
  //*currIt is the indiv whose Neighbors information we are setting
  currIt = beginOfThePopulation();
  while (currIt < endOfThePopulation()) {
    curri = (*currIt).getIdentity();
    currX = (*currIt).getPhenotypeX();
    currY = (*currIt).getPhenotypeY();
    n1Iden = (*currIt).getNeighbor1Identity();
    n2Iden = (*currIt).getNeighbor2Identity();
    if (n1Iden != -1 && n2Iden != -1) {
      double_checking = true;
    }
    if (double_checking == false) {
      lowerX = currX - range1[r];
      upperX = currX + range1[r];
      lowerY = currY - range1[r];
      upperY = currY + range1[r];
    } else {
      lowerX = currX - range2[r];
      upperX = currX + range2[r];
      lowerY = currY - range2[r];
      upperY = currY + range2[r];
    }
    //*tempIt is the indiv who may become *currIt's neighbor
    tempIt = beginOfThePopulation();
    for (int t = 0; t < intSizeOfThePopulation(); t++) {
      if (intSizeOfThePopulation() >= getExtinctionLimit()) {
        tempi = (*tempIt).getIdentity();
        if (tempi != curri && tempi != n1Iden && tempi != n2Iden) {
          tempX = Xs[t];
          if (lowerX < tempX && tempX < upperX) {
            tempY = Ys[t];
            if (lowerY < tempY && tempY < upperY) {
              n1Iden = (*currIt).getNeighbor1Identity();
              n2Iden = (*currIt).getNeighbor2Identity();
              if (tempi != n1Iden) {
                if (tempi != n2Iden) { //is this check necessary?
                  //distance from *tempIt to *currIt is not known, so calculate it
                  currDist = pow(pow((currX - tempX), 2) + pow((currY - tempY), 2), 0.5);
                  n1Dist = (*currIt).getNeighbor1Distance();
                  //is *tempIt closer to *currIt than the current Neighbor1?
                  if (currDist < n1Dist) {
                    //bump old Neighbor1 info to Neighbor2 info for *currIt
                    (*currIt).setNeighbor2Identity(n1Iden);
                    (*currIt).setNeighbor2Distance(n1Dist);
                    //*tempIt is currently closer to *currIt than all others checked
                    //set *tempIt information under *currIt's Neighbor1 info
                    (*currIt).setNeighbor1Identity(tempi);
                    (*currIt).setNeighbor1Distance(currDist);
                    //is *tempIt closer to *currIt than the current Neighbor2?
                  } else if (currDist < ((*currIt).getNeighbor2Distance())) {
                    //set *tempIt information under *currIt's Neighbor2 info
                    (*currIt).setNeighbor2Identity(tempi);
                    (*currIt).setNeighbor2Distance(currDist);
                  }//assignments
                }//check if already assigned as one of currIndiv's neighbors
              }
            }
          }
        }
      }
      tempIt++;
    }
    /*while (tempIt < endOfThePopulation()) {
      //can optimize this by calling and storing all X and Y coords of the population, 
      //then checking through that list as opposed to calling up the indiv's each time
      //and then checking their X and Y coords numerous times.
      tempX = (*tempIt).getPhenotypeX();
      tempY = (*tempIt).getPhenotypeY();
      tempi = (*tempIt).getIdentity();
      if (tempi != curri) {
        //check if tempX is within search range
        if (lowerX < tempX && tempX < upperX) {
          //check if tempY is within search range
          if (lowerY < tempY && tempY < upperY) {
            //*tempIt's location is within search region
            n1Iden = (*currIt).getNeighbor1Identity();
            n2Iden = (*currIt).getNeighbor2Identity();
            //check if *tempIt is *currIt's neighbor
            if (tempi != n1Iden || tempi != n2Iden) {
              //distance from *tempIt to *currIt is not known, so calculate it
              currDist = pow(pow((currX - tempX), 2) + pow((currY - tempY), 2), 0.5);
              n1Dist = (*currIt).getNeighbor1Distance();
              //is *tempIt closer to *currIt than the current Neighbor1?
              if (currDist < n1Dist) {
                //bump old Neighbor1 info to Neighbor2 info for *currIt
                (*currIt).setNeighbor2Identity(n1Iden);
                (*currIt).setNeighbor2Distance(n1Dist);
                //*tempIt is currently closer to *currIt than all others checked
                //set *tempIt information under *currIt's Neighbor1 info
                (*currIt).setNeighbor1Identity(tempi);
                (*currIt).setNeighbor1Distance(currDist);
                //is *tempIt closer to *currIt than the current Neighbor2?
              } else if (currDist < ((*currIt).getNeighbor2Distance())) {
                //set *tempIt information under *currIt's Neighbor2 info
                (*currIt).setNeighbor2Identity(tempi);
                (*currIt).setNeighbor2Distance(currDist);
              }//assignments
            }//check if already assigned as one of currIndiv's neighbors
          }//check Y
        }//check X
      }//tempi is not curri
      tempIt++;
    }//while tempIt
    */
    if (double_checking == false) {
      r = r + 1;
      if (r > 8) {
        cout << "whoops! " << curri << " is related to " << n1Iden << " & " << n2Iden << endl;
        currIt++;
      }
    } else {
      //both neighbors are set, go to next indiv, and reset range to default
      currIt++;
      double_checking = false;
      r = 0;
    }
  }//for currIt
  delete[] Xs;
  delete[] Ys;
}

void population::goodNeighbors(vector<indiv>::iterator ref) {
  int refId, neigh1Id, neigh2Id;
  refId = (*ref).getIdentity();
  neigh1Id = (*ref).getNeighbor1Identity();
  neigh2Id = (*ref).getNeighbor2Identity();
  if (neigh1Id > ThePopulationSize) {
    cout << "Indiv " << refId << " has impossible neighbor 1, " << neigh1Id;
    cout << "." << endl;
  }
  if (neigh2Id > ThePopulationSize) {
    cout << "Indiv " << refId << " has impossible neighbor 2, " << neigh2Id;
    cout << "." << endl;
  }
}

void population::replaceIndiv(int disone, indiv* indi) {
  ThePopulation[disone] = *indi;
}

indiv population::getThisIndivOfThePopulation(int thisIndiv) {
  indiv na;
  if (checkIdentity(thisIndiv)) {
    return ThePopulation[thisIndiv];
  } else {
    return na;
  }
}

indiv population::getNeighbor1OfThisIndiv(indiv* div1) {
  int na1id = div1->getNeighbor1Identity();
  indiv na;
  if (checkIdentity(na1id)) {
    return ThePopulation[na1id];
  } else {
    return na;
  }
}

indiv population::getNeighbor2OfThisIndiv(indiv* div2) {
  int na2id = div2->getNeighbor2Identity();
  indiv na;
  if (checkIdentity(na2id)) {
    return ThePopulation[na2id];
  } else {
    return na;
  }
}

vector<indiv>::iterator population::beginOfThePopulation() {
  return ThePopulation.begin();
}

vector<indiv>::iterator population::endOfThePopulation() {
  return ThePopulation.end();
}

vector<indiv> population::getThePopulation() {
  return ThePopulation;
}

int population::intSizeOfThePopulation() const {
  return int(ThePopulation.size());
}

double population::meanMutability() {
  vector<indiv>::iterator It;
  double mutability, avgMut;
  It = beginOfThePopulation();
  avgMut = 0;
  for (It; It < endOfThePopulation(); It++) {
    mutability = (*It).getMutability();
    avgMut = avgMut + mutability;
  }
  avgMut = avgMut / intSizeOfThePopulation();
  return avgMut;
}

int population::uniqueMutability() {
  vector<indiv>::iterator thisIt = beginOfThePopulation();
  double noise;
  bool addNoise;
  vector<double> mutabilities;
  vector<double>::iterator mutIt, mutItEnd;
  for (thisIt; thisIt < endOfThePopulation(); thisIt++) {
    addNoise = true;
    noise = (*thisIt).getMutability();
    mutIt = mutabilities.begin();
    for (mutIt; mutIt < (mutabilities.end()); mutIt++) {
      if (noise == (*mutIt)) {
        addNoise = false;
      }
    }
    if (addNoise == true) {
      mutabilities.push_back(noise);
    }
  }
  return int(mutabilities.size());
}
///////////////////////////////////////////////////////////////
//DEATH DANCES
///////////////////////////////////////////////////////////////

void population::setOverPopulationLimit(double limit) {
  OverPopulationLimit = limit;
}

void population::setDeathChance(double unfortunate) {
  DeathChance = unfortunate;
}

void population::setExtinctionLimit(int el) {
  ExtinctionLimit = el;
}

double population::getOverPopulationLimit() const {
  return OverPopulationLimit;
}

double population::getDeathChance() const {
  return DeathChance;
}

int population::getExtinctionLimit() const {
  return ExtinctionLimit;
}

void population::CliffJumpers(landscape* cliffs) {
  vector<indiv>::iterator chance;
  int X, Y;
  double x, y;
  int id;

  //kill off any indivs outside the phenospace
  X = cliffs->getMaxXOfTheLandscape();
  Y = cliffs->getMaxYOfTheLandscape();
  chance = beginOfThePopulation();
  while (chance < (endOfThePopulation()) && intSizeOfThePopulation() >= getExtinctionLimit()) {
    id = (*chance).getIdentity();
    x = (*chance).getPhenotypeX();
    y = (*chance).getPhenotypeY();
    if (x > X || x < 0) {
      if (chance == endOfThePopulation()) {
        ThePopulation.pop_back();
        KilledCJ++;
      } else {
        chance = removeIndivFromThePopulation(chance);
        KilledCJ++;
      }
    } else if (y > Y || y < 0) {
      if (chance == endOfThePopulation()) {
        ThePopulation.pop_back();
        KilledCJ++;
      } else {
        chance = removeIndivFromThePopulation(chance);
        KilledCJ++;
      }
    } else if (KilledCJ > 0) {
      adjustIdentity(KilledCJ, chance);
      chance++;
    } else {
      chance++;
    }
  }
}

void population::RussianRoulette(CRandomMersenne* dice) {
  int deathRequest, roll;
  int* chosenList;
  double risk;
  int A, B;
  int count;
  vector<indiv>::iterator chosen;
  int id;
  int j = 0;

  //determine number of indivs to kill and which ones
  risk = DeathChance * (dice->Random());  //risk = 0.7*0.5 = 0.35
  deathRequest = int(risk * ThePopulationSize); //deathRequest = 0.35*300 = 105
  //cout << "Should randomly kill:  " << deathRequest << endl;
  /*chosenList = new int[deathRequest]; //105 elements in chosenList
  //I forget how this works
  for (int i = 0; i < deathRequest; i++) {
    chosenList[i] = int(1 + ((ThePopulationSize - 1)*(dice->Random())));  //1 +((300-1)*
    while (j < i) {
      if (chosenList[i] == chosenList[j]) {
        i--;
      }
      j++;
    }
    j = 0;
  }

  //is this necessary?
  //sort chosenList
  for (int a = 0; a < deathRequest; a++) {
    for (int b = 0; b < deathRequest; b++) {
      if (a != b) {
        A = chosenList[a];
        B = chosenList[b];
        if (A < B && a > b) { //if A is before B but A is located after B then swap
          chosenList[a] = A; //does this ever occur?
          chosenList[b] = B;
        } else if (A > B && a < b) { //if A is after B but A is located before B then swap
          chosenList[a] = B;
          chosenList[b] = A;
        }
      }
    }
  }
  */
  if (deathRequest > 0) {
    //step 2:  match list to indiv's in ThePopulation and remove them	
    roll = 0;
    count = 0;
    chosen = beginOfThePopulation();
    while (chosen < (endOfThePopulation())) {
      id = (*chosen).getIdentity();
      if (count == chosenList[roll]) {
        chosen = removeIndivFromThePopulation(chosen);
        roll++;
        KilledRR++;
      } else if (KilledRR > 0) {
        adjustIdentity(KilledRR, chosen);
        chosen++;
      } else {
        chosen++;
      }
      count++;
    }
    if (roll > 1) {
      delete [] chosenList;
    } else {
      delete chosenList;
    }
  }
}

void population::CrowdControl(CRandomMersenne* R) {
  int refi, checki, removed, refItgone;
  double refx, refy, checkx, checky, dist, limit;
  double* r = new double[intSizeOfThePopulation()];
  int* order = new int[intSizeOfThePopulation()];
  int tempa;
  double temp, rr;
  //double** r = new double*[2];
  //r = double[intSizeOfThePopulation()][2];
  //vector<double[2]> rands, ordered;
  //vector<double[2]>::iterator randIt, orderIt;
  vector<indiv>::iterator checkIt, offed;
  indiv refI;

  //Could not do this sort and just randomly pick who to kill

  /* PUT THIS SORT IN ITS OWN FUNCTION */
  //rands.reserve(intSizeOfThePopulation());
  //randIt = rands.begin();
  //give each indiv a random number
  int a = 0;
  checkIt = beginOfThePopulation();
  while (checkIt < endOfThePopulation()) {
    rr = R->Random();
    r[a] = rr;
    order[a] = a;
    //r[2*a+1] = a;
    //randIt* = r;
    //rands.assign(r,1);
    //rands.push_back(r);
    checkIt++;
    a++;
  }

  //sort indivs according to their random number
  int c;
  //cout << "beginning to sort" << endl;
  for (int b = 0; b < intSizeOfThePopulation(); b++) {
    c = 0; //index c counts through population
    while (c < intSizeOfThePopulation()) {
      if (r[b] < r[c]) { //if b's random number is < c's
        tempa = order[b]; //get b's place in the order
        temp = r[b]; //get b's random number
        order[b] = order[c]; //assign c's place in the order to b's
        r[b] = r[c]; //assign c's random number to b's
        order[c] = tempa; //reassign b's place to c's
        r[c] = temp; //reassign b's random number to c's
      }
      c++;
    }
  }

  //cout << "finished sorting" << endl;
  //    ofstream sout;
  //    ostringstream fname;
  //    string sfile;
  //    //if(sim==2) {
  //    fname.str("");
  //    fname << sfile << ".txt";
  //    sfile = "sort";
  //    sfile = sfile + fname.str();
  //    sout.open(sfile.c_str());
  //    for (int i = 0; i < intSizeOfThePopulation(); i++) {
  ////        cout << r[i] << ' ' << order[i] << endl;
  //        sout << r[i] << ',' << order[i] << endl;
  //    }
  //    sout.close();
  //    sfile.clear();
  //    }
  refItgone = 0;
  limit = pow(OverPopulationLimit,2);  //avoiding use of sqrt
  c = 0;
  while (c < intSizeOfThePopulation() && intSizeOfThePopulation() >= getExtinctionLimit()) {
    refI = getThisIndivOfThePopulation(order[c]);
    refx = refI.getPhenotypeX();
    if (refx != -1) {
      refi = refI.getIdentity();
      refy = refI.getPhenotypeY();
      checkIt = beginOfThePopulation();
      removed = 0;
      //check each indiv for overcrowding
      while (checkIt < endOfThePopulation()) {
        checki = (*checkIt).getIdentity();
        //only check if *refIt and *checkIt are different indivs
        if (refi != checki) {
          checkx = (*checkIt).getPhenotypeX();
          checky = (*checkIt).getPhenotypeY();
          if (checkx != -1) {
            dist = pow((refx - checkx), 2) + pow((refy - checky),2);
            //too close?
            if (dist < limit && dist != 0) {
              //yes, now kill *checkIt or *refIt
              (*checkIt).setPhenotypeX(-1);
              (*checkIt).setPhenotypeY(-1);
              /*if(KilledOP%2==0) {
              checkIt = removeIndivFromThePopulation(checkIt);
              offed = checkIt;
              }else {
              refIt = removeIndivFromThePopulation(refIt);
              refItgone = 1;
              offed = refIt;
              checkIt = endOfThePopulation();
              }
              while(offed<endOfThePopulation()) {
              adjustIdentity(1,offed);
              offed++;
              }*/
              KilledOP++;
              //removed++;
              //}else {
              //	//no, move on to the next indiv
              //	checkIt++;
            }
          }
        }/*else {
         checkIt++;
         }*/ //if refi!=checki 
        checkIt++;
        /*if(checkIt!=endOfThePopulation()) {
        adjustIdentity(removed,checkIt); 
        }*/
      } //while checkIt
    }
    //if(refItgone==0) {
    //	refIt++; //*refIt wasn't killed
    //}else {
    //	refItgone = 0; //*refIt was killed
    //}
    c = c++;
  } //while refIt
  if (intSizeOfThePopulation() >= getExtinctionLimit()) {
    //can rearrange offing indivs to optimize
    checkIt = beginOfThePopulation();
    while (checkIt < endOfThePopulation()) {
      checkx = (*checkIt).getPhenotypeX();
      if (checkx == -1) {
        checkIt = removeIndivFromThePopulation(checkIt);
        offed = checkIt;
        while (offed < endOfThePopulation()) {
          adjustIdentity(1, offed);
          offed++;
        }
              /*adjustIdentity(KilledOP, checkIt);
    } else if (KilledOP > 0) {
      adjustIdentity(KilledOP, checkIt);
      checkIt++;*/
      } else {
        checkIt++;
      }
    }
  }
}
//void population::CrowdControl(landscape* resources) {
//	double range, defRange;
//	double currX, currY, currDist, upperX, lowerX, upperY, lowerY;
//	vector<indiv>::iterator currIt, tempIt;
//	int curri, tempi, n1Iden, n2Iden;
//	double tempX, tempY, n1Dist, n2Dist;
//	bool remove;
//	int removed;
//	vector<indiv> findAgain, toKillList;
//
//	defRange = getDefaultRange(resources);
//	range = defRange;
//	//*currIt is the indiv whose Neighbors information we are setting
//	currIt = ThePopulation.begin();
//	n1Iden = (*currIt).getNeighbor1Identity();
//	n2Iden = (*currIt).getNeighbor2Identity();
//	while(currIt<endOfThePopulation()) {
//		//get currIt's information
//		curri = (*currIt).getIdentity();
//		currX = (*currIt).getPhenotypeX();
//		currY = (*currIt).getPhenotypeY();
//		//set neighbor search limits
//		upperX = currX+range;
//		lowerX = currX-range;
//		upperY = currY+range;
//		lowerY = currY-range;
//		//restart remove counter
//		removed = 0;
//		//*tempIt is the indiv who may become *currIt's neighbor
//		tempIt = ThePopulation.begin();
//		//cycle through the population to set neighbors
//		while(tempIt<(ThePopulation.end())) {
//			//need *tempIt's identity	
//			tempi = (*tempIt).getIdentity();
//			//if indiv's have been removed, adjust *tempIt's identity accordingly
//			adjustIdentity(removed,tempIt);
//			//reset remove state
//			remove = false;
//			//don't try checking if *currIt is *tempIt
//			if(curri!=tempi) {
//				//get *tempIt's location
//				tempX = (*tempIt).getPhenotypeX();
//				tempY = (*tempIt).getPhenotypeY();
//				//check if *tempIt is within the x range
//				if(lowerX<tempX && tempX<upperX) {
//					//check if *tempIt is within the y range
//					if(lowerY<tempY && tempY<upperY) {
//						//get the identities of *currIt's neighbors
//						n1Iden = (*currIt).getNeighbor1Identity();
//						n2Iden = (*currIt).getNeighbor2Identity();
//						//check if *tempIt *currIt's neighbor 1 or 2
//						if(tempi!=n1Iden && tempi!=n2Iden) {
//							//calculate the distance from *currIt to *tempIt
//							currDist = pow(pow((currX-tempX),2)+pow((currY-tempY),2),0.5);
//							//check if *tempIt is too close to *currIt
//							if(currDist>OverPopulationLimit) {
//								//get the distances from *currIt to it's current neighbors
//								n1Dist = (*currIt).getNeighbor1Distance();
//								n2Dist = (*currIt).getNeighbor2Distance();
//								//check if *tempIt is closer than *currIt's current neighbor 1
//								if(currDist<n1Dist) {
//		if(n1Iden>intSizeOfThePopulation() || n2Iden>intSizeOfThePopulation()){
//			cout << "n1Iden = " << n1Iden << " and n2Iden = " << n2Iden;
//			cout << ", but the population only has " << intSizeOfThePopulation();
//		}
//									//move *currIt's old neighbor 1 info to the neighbor 2 slots
//									(*currIt).setNeighbor2Identity(n1Iden);
//									(*currIt).setNeighbor2Distance(n1Dist);
//									//reset *currIt's neighbor 1 info with *tempIt's info
//									(*currIt).setNeighbor1Identity(tempi);
//									(*currIt).setNeighbor1Distance(currDist);
//								//check if *tempIt is closer than *currIt's current neighbor 1
//								}else if(currDist<n2Dist) {
//									//reset *currIt's neighbor 2 info with *tempIt's info
//									(*currIt).setNeighbor2Identity(tempi);
//									(*currIt).setNeighbor2Distance(currDist);
//								}//assignments
//							//*tempIt is too close to *currIt...it'll soon die
//							}else {
//		n1Iden = (*currIt).getNeighbor1Identity();
//		n2Iden = (*currIt).getNeighbor2Identity();
//		if(n1Iden>intSizeOfThePopulation() || n2Iden>intSizeOfThePopulation()){
//			cout << "n1Iden = " << n1Iden << " and n2Iden = " << n2Iden;
//			cout << ", but the population only has " << intSizeOfThePopulation();
//			cout << ".  Before OverPopulated!";
//		}
//								//send *tempIt to see who has it as their neighbor
//								findAgain = OverPopulated(tempi, findAgain, currIt);
//								//*tempIt meets the chopping block...this returns the next tempIt
//								tempIt = removeIndivFromThePopulation(tempIt);
//								//increment the number of removed
//								removed++;
//								KilledOP++;
//								//remove tells the incrementer to hold off
//								remove = true;
//		n1Iden = (*currIt).getNeighbor1Identity();
//		n2Iden = (*currIt).getNeighbor2Identity();
//		if(n1Iden>intSizeOfThePopulation() || n2Iden>intSizeOfThePopulation()){
//			cout << "n1Iden = " << n1Iden << " and n2Iden = " << n2Iden;
//			cout << ", but the population only has " << intSizeOfThePopulation();
//			cout << ".  After OverPopulated!";
//		}
//							}//check OverPopulationLimit
//						}//check if already assigned as one of currIndiv's neighbors
//					}//check Y
//				}//check X
//			}//curri, tempi
//			//check if tempIt was removed
//			if(remove==false) {	tempIt++; }
//		}//while tempIt
//		n1Iden = (*currIt).getNeighbor1Identity();
//		n2Iden = (*currIt).getNeighbor2Identity();
//		//double check if *currIt has found a non default neighbor 1 and 2
//		if(n1Iden==-1 || n2Iden==-1) {
//			//*currIt still hasn't set both of its neighbors from default
//			//both neighbors are not set, increase limit area of range
//			range = 2*range;
//			//this CAN include the whole map, so the while loop can exit
//		}else if(n1Iden>intSizeOfThePopulation() || n2Iden>intSizeOfThePopulation()){
//			cout << "n1Iden = " << n1Iden << " and n2Iden = " << n2Iden;
//			cout << ", but the population only has " << intSizeOfThePopulation();
//			break;
//		}else {
//			replaceIndiv(curri, &(*currIt));
//			//neighbors have been set, so increment to next indiv in ThePopulation
//			currIt++;
//			//reset range to default
//			range = defRange;
//		}
//	}//for currIt
//	//For those indiv's whose nearest neighbors were killed...
//	NeighborsRestored(findAgain, defRange);
//}
//double population::getDefaultRange(landscape* smallWorld) {
//	double maxDist, area, fracDist, defaultRange;
//
//	//get the maximum diagonal distance of the landscape
//	maxDist = smallWorld->getMaximumDistance();	
//	//calculate the area of the landscape
//	area = (smallWorld->getMaxXOfTheLandscape())*(smallWorld->getMaxYOfTheLandscape());
//	//use inverse population density on map for search area
//	defaultRange = area/intSizeOfThePopulation();
//	//no need for defaultRange to be larger than the maxDist
//	if(defaultRange > maxDist) { defaultRange = maxDist; }
//	//the minimum defaultRange is 5% of maxDist (subjectively chosen)
//	fracDist = 0.05*maxDist;
//	//too small of a search area may result in lots of full population searches
//	if(defaultRange < fracDist) { defaultRange = fracDist; }
//	//initialize range to default
//	return defaultRange;
//}
//vector<indiv> population::OverPopulated(int tempi, vector<indiv> retry, 
//														vector<indiv>::iterator currIt) {
//	bool checked;
//	int tempItn1id, tempItn2id, redoid, fAid;
//	vector<indiv>::iterator tryIt, trying;
//	//tempIt is dying.  Need to check the previously set
//	//indiv's to see if they're associated with tempIt.
//	//If they are, then we need to reset their nearest
//	//neighbor(s).
//	tryIt = beginOfThePopulation();
//	//cycle set indiv's
//	for(tryIt; tryIt<currIt; tryIt++) {
//		//tryIt's Neighbor1Identity
//		tempItn1id = (*tryIt).getNeighbor1Identity();
//		//tryIt's Neighbor2Identity
//		tempItn2id = (*tryIt).getNeighbor2Identity();
//		//Is either Neighbor the dying indiv?
//		if(tempItn1id==tempi || tempItn2id==tempi) {
//			if(int(retry.size())>0) {
//				trying = retry.begin();
//				redoid = (*tryIt).getIdentity();
//				checked = true;
//				//cycle through retry
//				while(checked) {
//					fAid = (*trying).getIdentity();
//					if(redoid==fAid){
//						//*tryIt is already in retry
//						checked = false;
//					}else {
//						//go to next in retry
//						trying++;
//					}
//					//if at the end of retry, then tryIt isn't 
//					//included yet
//					if(trying==(retry.end())) {
//						(*tryIt).setNeighbor1Distance(1000);
//						(*tryIt).setNeighbor2Distance(1000);
//						(*tryIt).setNeighbor1Identity(-1);
//						(*tryIt).setNeighbor2Identity(-1);
//						retry.push_back(*tryIt);
//						checked = false;
//					}
//				}
//			}else {//if retry has nothing
//				(*tryIt).setNeighbor1Distance(1000);
//				(*tryIt).setNeighbor2Distance(1000);
//				(*tryIt).setNeighbor1Identity(-1);
//				(*tryIt).setNeighbor2Identity(-1);
//				retry.push_back(*tryIt);
//			}
//		}
//		//is Neighbor1 after dying indiv?
//		//if(tempItn1id>tempi) {
//		//	//reset tryIt's Neighbor1Identity one less
//		//	(*tryIt).setNeighbor1Identity(tempItn1id-1);
//		//}
//		////is Neighbor2 after dying indiv?
//		//if(tempItn2id>tempi) {
//		//	//reset tryIt's Neighbor2Identity one less
//		//	(*tryIt).setNeighbor2Identity(tempItn2id-1);
//		//}
//	}//end tryIt
//	return retry;
//}

void population::NeighborsRestored(vector<indiv> redoThese, double dR) {
  vector<indiv>::iterator redo, tI;
  double r, cX, cY, uX, lX, uY, lY, tX, tY, cD, n1D, n2D;
  int ci, ti, n1i, n2i;
  r = dR;
  if (int(redoThese.size()) > 0) {
    redo = redoThese.begin();
    n1i = (*redo).getNeighbor1Identity();
    n2i = (*redo).getNeighbor2Identity();
    while (redo < redoThese.end()) {
      ci = (*redo).getIdentity();
      cX = (*redo).getPhenotypeX();
      cY = (*redo).getPhenotypeY();
      tI = ThePopulation.begin();
      uX = cX + r;
      lX = cX - r;
      uY = cY + r;
      lY = cY - r;
      while (tI < (ThePopulation.end())) {
        ti = (*tI).getIdentity();
        if (ci != ti) {
          n1D = (*redo).getNeighbor1Distance();
          n2D = (*redo).getNeighbor2Distance();
          tX = (*tI).getPhenotypeX();
          tY = (*tI).getPhenotypeY();
          if (lX < tX && tX < uX) {
            if (lY < tY && tY < uY) {
              n1i = (*redo).getNeighbor1Identity();
              n2i = (*redo).getNeighbor2Identity();
              if (ti != n1i && ti != n2i) {
                cD = pow(pow((cX - tX), 2) + pow((cY - tY), 2), 0.5);
                if (cD < n1D) {
                  (*redo).setNeighbor1Identity(ti);
                  (*redo).setNeighbor1Distance(cD);
                  (*redo).setNeighbor2Identity(n1i);
                  (*redo).setNeighbor2Distance(n1D);
                } else if (cD < n2D) {
                  (*redo).setNeighbor2Identity(ti);
                  (*redo).setNeighbor2Distance(cD);
                }//assignments
              }//tI is not a neighbor
            }//check Y
          }//check X
        }//ci!=ti
        tI++;
      }//while tI
      n1i = (*redo).getNeighbor1Identity();
      n2i = (*redo).getNeighbor2Identity();
      if (n1i == -1 || n2i == -1) {
        //both neighbors are not set, increase limit area of range
        r = 2 * r;
        //this CAN include the whole map, so the while loop can exit	
      } else {
        replaceIndiv(ci, &(*redo));
        redo++;
        r = dR;
      }
    }//for redo
  }//if redoThese
}

void population::adjustIdentity(int rmvd, vector<indiv>::iterator fixIt) {
  int id = (*fixIt).getIdentity();
  if (rmvd > 0) {
    id = id - rmvd;
    (*fixIt).setIdentity(id);
  }
}

int population::getOPKillCount() const {
  return KilledOP;
}

int population::getRRKillCount() const {
  return KilledRR;
}

int population::getCJKillCount() const {
  return KilledCJ;
}

int population::getKillCount() const {
  return Killed;
}

bool population::checkIdentity(int id) {
  if (id <= intSizeOfThePopulation()) {
    return true;
  } else {
    cout << id;
    throw " That guy doesn't exist!";
    return false;
  }
}