#include "ancestors.h"

ancestors::ancestors() {
    vector<population> TheAncestors;
    vector<genus> TheNations;
    vector<double> PhenotypeXs;
    vector<double> PhenotypeYs;
    vector<int> Parent1s;
    vector<int> Parent2s;
    vector<int> Neighbor1s;
    vector<int> Neighbor2s;
    vector<double> Mutabilities;
    int ExtinctionLimit = 3;
    /*Popc = '0';
    Phnc = '0';
    Parc = '0';
    Nghc = '0';
    Mutc = '0';
    Genc = '0';
    Sppc = '0';*/
}

ancestors::ancestors(int buffanc) {
    vector<population> TheAncestors;
    vector<genus> TheNations;
    vector<double> PhenotypeXs;
    vector<double> PhenotypeYs;
    vector<int> Parent1s;
    vector<int> Parent2s;
    vector<int> Neighbor1s;
    vector<int> Neighbor2s;
    vector<double> Mutabilities;
    TheAncestors.reserve(buffanc);
    TheNations.reserve(buffanc);
    int ExtinctionLimit = 3;
    /*Popc = '0';
    Phnc = '0';
    Parc = '0';
    Nghc = '0';
    Mutc = '0';
    Genc = '0';
    Sppc = '0';*/
}

ancestors::~ancestors() {
    TheAncestors.erase(TheAncestors.begin(), TheAncestors.end());
    TheNations.erase(TheNations.begin(), TheNations.end());
}

void ancestors::addToTheAncestors(population oldGen) {
    char* phnc = getPhenotypeCommand();
    char* parc = getParentCommand();
    char* nghc = getNeighborCommand();
    char* mutc = getMutabilityCommand();
    vector<indiv>::iterator It;
    int ipar;
    double dpar;
    //If commander says save all, just save to TheAncestors
    if (checkCommand(phnc) && checkCommand(parc) && checkCommand(nghc) &&
            checkCommand(mutc)) {
        TheAncestors.push_back(oldGen);
        //Otherwise, save only the essentials as given by the commander file
    } else {
        PopulationSize.push_back(oldGen.intSizeOfThePopulation());
        It = oldGen.beginOfThePopulation();
        for (It; It < oldGen.endOfThePopulation(); It++) {
            //save phenotype coordinates?
            if (checkCommand(phnc)) {
                dpar = (*It).getPhenotypeX();
                PhenotypeXs.push_back(dpar);
                dpar = (*It).getPhenotypeY();
                PhenotypeYs.push_back(dpar);
            }
            //save parent identities?
            if (checkCommand(parc)) {
                ipar = (*It).getParent1Identity();
                Parent1s.push_back(ipar);
                ipar = (*It).getParent2Identity();
                Parent2s.push_back(ipar);
            }
            //save neighbor identities?
            if (checkCommand(nghc)) {
                ipar = (*It).getNeighbor1Identity();
                Neighbor1s.push_back(ipar);
                ipar = (*It).getNeighbor2Identity();
                Neighbor2s.push_back(ipar);
            }
            //save mutabilities?
            if (checkCommand(mutc)) {
                dpar = (*It).getMutability();
                Mutabilities.push_back(dpar);
            }
        }//end for It
    }//end if/else
}

void ancestors::removePopulation(vector<population>::iterator byeGen) {
    TheAncestors.erase(byeGen);
}

void ancestors::resetTheAncestors() {
    if (checkCommand(Phnc) && checkCommand(Parc) && checkCommand(Nghc) &&
            checkCommand(Mutc)) {
        TheAncestors.erase(TheAncestors.begin(), TheAncestors.end());
    } else {
        PopulationSize.erase(PopulationSize.begin(), PopulationSize.end());
        if (checkCommand(Phnc)) {
            PhenotypeXs.erase(PhenotypeXs.begin(), PhenotypeXs.end());
            PhenotypeYs.erase(PhenotypeYs.begin(), PhenotypeYs.end());
        }
        if (checkCommand(Parc)) {
            Parent1s.erase(Parent1s.begin(), Parent1s.end());
            Parent2s.erase(Parent2s.begin(), Parent2s.end());
        }
        if (checkCommand(Nghc)) {
            Neighbor1s.erase(Neighbor1s.begin(), Neighbor1s.end());
            Neighbor2s.erase(Neighbor2s.begin(), Neighbor2s.end());
        }
        if (checkCommand(Mutc)) {
            Mutabilities.erase(Mutabilities.begin(), Mutabilities.end());
        }
    }
}

void ancestors::replacePopulation(int deesone, population* populogy) {
    TheAncestors[deesone] = *populogy;
}

population ancestors::getThisPopulationOfTheAncestors(int thisPopulation) {
    return TheAncestors[thisPopulation];
}

//ITERATOR ACCESS

vector<population>::iterator ancestors::beginOfTheAncestors() {
    return TheAncestors.begin();
}

vector<population>::iterator ancestors::endOfTheAncestors() {
    return TheAncestors.end();
}
//THE ANCESTORS ACCESS

vector<population> ancestors::getTheAncestors() {
    return TheAncestors;
}

int ancestors::intSizeOfTheAncestors() const {
    return int(TheAncestors.size());
}

void ancestors::setTempPopulation(population tp) {
    TheAncestors.push_back(tp);
}
///////////////////////////////////////////////////////////////
//REPRODUCTION RITUALS
///////////////////////////////////////////////////////////////

population ancestors::assortativeMating(landscape* babylaw, population* oldPop,
        CRandomMersenne* raNuGe) {
    //CRandomMersenne raNuGe(int(time(NULL)));//for real runs
    //CRandomMersenne raNuGe(0);//for test runs
    int refId, mateId, refFit, pSize;
    double refX, refY, refM;
    double mateX, mateY;
    double lowX, lowY, highX, highY;
    double babyX, babyY;
    indiv Ref, Mate, Baby;
    population newPop;
    int newpopsize = 0;
    vector<indiv>::iterator refIt, endCurr;

    refIt = oldPop->beginOfThePopulation();
    /*for(ref; ref<oldPop->endOfThePopulation(); ref++) {
            oldPop->goodNeighbors(ref);
    }*/
    //cycle through the old (parents) population
    for (refIt; refIt < (oldPop->endOfThePopulation()); refIt++) {
        //get *refIt's information
        refId = (*refIt).getIdentity();
        refX = (*refIt).getPhenotypeX();
        refY = (*refIt).getPhenotypeY();
        refM = (*refIt).getMutability();
        //get *refIt's Neighbor1 (Mate) information
        mateId = (*refIt).getNeighbor1Identity();
        pSize = oldPop->intSizeOfThePopulation();
        if (mateId > pSize || mateId < 0) {
            cout << mateId << " cannot be " << refId;
            cout << "'s mate!  The population is of size " << pSize << endl;
        }
        Mate = oldPop->getNeighbor1OfThisIndiv(&(*refIt));
        mateId = Mate.getIdentity();
        mateX = Mate.getPhenotypeX();
        mateY = Mate.getPhenotypeY();
        //determine minimum x value
        if (refX <= mateX) {
            lowX = refX - refM;
        } else {
            lowX = mateX - refM;
        }
        //determine minimum y value
        if (refY <= mateY) {
            lowY = refY - refM;
        } else {
            lowY = mateY - refM;
        }
        //determine maximum x value
        if (refX <= mateX) {
            highX = mateX + refM;
        } else {
            highX = refX + refM;
        }
        //determine maximum y value
        if (refY <= mateY) {
            highY = mateY + refM;
        } else {
            highY = refY + refM;
        }
        //get *refIt's fitness (number of babies it can have)
        refFit = babylaw->getNearestFitnessOfTheLandscape(refX, refY);
        //birth each baby
        for (int baby = 0; baby < refFit; baby++) {
            //determine the baby's location
            babyX = lowX + (highX - lowX)*(raNuGe->Random());
            babyY = lowY + (highY - lowY)*(raNuGe->Random());
            //make sure baby is within the landscape
            //NOTE:  Matlab takes care of cliff jumpers AFTER overpopulation and
            //			random death.  The order of overpopulation and random death
            //			(for whatever reason) matters, so despite possibly being more
            //			efficient, I'm not sure we should take care of cliff jumpers here.
            //if(babyX<(babylaw->getMaxXOfTheLandscape()) && babyX>=0) {
            //if baby is not within the landscape, then don't add it to newPop
            //if(babyY<(babylaw->getMaxYOfTheLandscape()) && babyY>=0) {
            //set baby's identity, parent identities, location and mutation rate
            Baby.setBaby(newpopsize, refId, mateId, babyX, babyY, refM);
            newPop.addToPopulation(Baby);
            newpopsize++;
            //}//within Y range
            //}//within X range
        }//babies
    }//parents
    //pass on oldPop's data members
    double opl = oldPop->getOverPopulationLimit();
    double death_max = oldPop->getDeathChance();
    newPop.setOverPopulationLimit(opl);
    newPop.setDeathChance(death_max);
    //rush babies to the simulated world
    return newPop;
}

population ancestors::cleaving(landscape* babylaw, population* oldPop,
        CRandomMersenne* raNuGe) {
    //CRandomMersenne raNuGe(int(time(NULL)));//for real runs
    //CRandomMersenne raNuGe(0);//for test runs
    int refId, refFit, pSize;
    double refX, refY, refM;
    double lowX, lowY, highX, highY;
    double babyX, babyY;
    indiv Ref, Baby;
    population newPop;
    int newpopsize = 0;
    vector<indiv>::iterator refIt, endCurr;

    refIt = oldPop->beginOfThePopulation();
    /*for(ref; ref<oldPop->endOfThePopulation(); ref++) {
            oldPop->goodNeighbors(ref);
    }*/
    //cycle through the old (parents) population
    for (refIt; refIt < (oldPop->endOfThePopulation()); refIt++) {
        //get *refIt's information
        refId = (*refIt).getIdentity();
        refX = (*refIt).getPhenotypeX();
        refY = (*refIt).getPhenotypeY();
        refM = (*refIt).getMutability();
        pSize = oldPop->intSizeOfThePopulation();
        //if(mateId>pSize || mateId<0) {	
        //	cout << mateId << " cannot be " << refId;
        //	cout << "'s mate!  The population is only " << pSize << " large!";
        //}
        //determine minimum x value
        lowX = refX - refM;
        //determine minimum y value
        lowY = refY - refM;
        //determine maximum x value
        highX = refX + refM;
        //determine maximum y value
        highY = refY + refM;
        //get *refIt's fitness (number of babies it can have)
        refFit = babylaw->getNearestFitnessOfTheLandscape(refX, refY);
        //birth each baby
        for (int baby = 0; baby < refFit; baby++) {
            //determine the baby's location
            babyX = lowX + (highX - lowX)*(raNuGe->Random());
            babyY = lowY + (highY - lowY)*(raNuGe->Random());
            Baby.setBaby(newpopsize, refId, babyX, babyY, refM);
            newPop.addToPopulation(Baby);
            newpopsize++;
        }//babies
    }//parents
    //pass on oldPop's data members
    double opl = oldPop->getOverPopulationLimit();
    double death_max = oldPop->getDeathChance();
    newPop.setOverPopulationLimit(opl);
    newPop.setDeathChance(death_max);
    //rush babies to the simulated world
    return newPop;
}
///////////////////////////////////////////////////////////////
//THENATIONS FUNCTIONS
///////////////////////////////////////////////////////////////

void ancestors::addToTheNations(genus oldGenus) {
    if (checkCommand(Genc) || checkCommand(Spdc) || checkCommand(Spic)) {
        TheNations.push_back(oldGenus);
    }
}

void ancestors::removeGenus(vector<genus>::iterator byeGenus) {
    TheNations.erase(byeGenus);
}

void ancestors::resetTheNations() {
    TheNations.erase(TheNations.begin(), TheNations.end());
}

void ancestors::replaceGenus(int disone, genus* genulogy) {
    TheNations[disone] = *genulogy;
}

genus ancestors::getThisGenusOfTheNations(int thisGenus) {
    return TheNations[thisGenus];
}
//ITERATOR ACCESS

vector<genus>::iterator ancestors::beginOfTheNations() {
    return TheNations.begin();
}

vector<genus>::iterator ancestors::endOfTheNations() {
    return TheNations.end();
}
//THE NATIONS ACCESS

vector<genus> ancestors::getTheNations() {
    return TheNations;
}

int ancestors::intSizeOfTheNations() const {
    return int(TheNations.size());
}

void ancestors::setSaveCommands(char* popc, char* phnc, char* parc,
        char* nghc, char* mutc, char* genc, char* spsc, char* spCc, char* spdc,
        char* spic, char* sptc, char* expc) {
    Popc = popc;
    Phnc = phnc;
    Parc = parc;
    Nghc = nghc;
    Mutc = mutc;
    Genc = genc;
    Spsc = spsc;
    SpCc = spCc;
    Spdc = spdc;
    Spic = spic;
    Sptc = sptc;
    Expc = expc;
}

char* ancestors::getPopulationCommand() const {
    return Popc;
}

char* ancestors::getPhenotypeCommand() const {
    return Phnc;
}

char* ancestors::getParentCommand() const {
    return Parc;
}

char* ancestors::getNeighborCommand() const {
    return Nghc;
}

char* ancestors::getMutabilityCommand() const {
    return Mutc;
}

char* ancestors::getGenusCommand() const {
    return Genc;
}

char* ancestors::getSpeciesDetailCommand() const {
    return Spdc;
}

char* ancestors::getSpeciesIndivsCommand() const {
    return Spic;
}

bool ancestors::checkCommand(char* command) const {
    if (command[0] == '0') {
        return true;
    } else {
        return false;
    }
}

int ancestors::checkCommand() const {
    int tni = 0;
    if (Popc[0] == '0') {
        tni = 10000 + tni;
    }
    if (Phnc[0] == '0') {
        tni = 1000 + tni;
    }
    if (Parc[0] == '0') {
        tni = 100 + tni;
    }
    if (Nghc[0] == '0') {
        tni = 10 + tni;
    }
    if (Mutc[0] == '0') {
        tni = 1 + tni;
    }
    return tni;
}

void ancestors::writeAncestors(int simu, int gens) {
    ofstream populationout, killout, genusout, speciessizeout, speciescxout, speciescyout;
    ofstream speciesdout, speciesiout, phenoxout, phenoyout, par1out, par2out, neigh1out;
    ofstream neigh2out, mutout;
    ostringstream fname;
    string pfile, kfile, gfile, ssfile, scxfile, scyfile, sdfile, sifile, dcfile, phxfile;
    string phyfile, mutfile, par1file, par2file, neigh1file, neigh2file;
    population POP;
    genus G;
    species SPP;
    indiv TEMP;

    cout << endl << "Recording requested info." << endl;
    if (checkCommand(Popc)) {
        cout << "populations" << endl;
        fname.str("");
        fname << pfile << simu << ".txt";
        pfile = "population_EvoSim_";
        pfile = pfile + fname.str();
        populationout.open(pfile.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                populationout << POP.intSizeOfThePopulation() << endl;
            } else {
                populationout << getPopulationSize(i) << endl;
            }
        }
        populationout.close();
        pfile.clear();
    }
    if (checkCommand(Popc)) {
        cout << "kill counts" << endl;
        fname.str("");
        fname << kfile << simu << ".txt";
        kfile = "kill_EvoSim_";
        kfile = kfile + fname.str();
        killout.open(kfile.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                killout << POP.getOPKillCount() << "," << POP.getRRKillCount() << ",";
                killout << POP.getCJKillCount() << endl;
            }
        }
        killout.close();
        kfile.clear();
    }
    if (checkCommand(Phnc)) {
        cout << "x phenotypes";
        fname.str("");
        fname << phxfile << simu << ".txt";
        phxfile = "phenotypeX_EvoSim_";
        phxfile = phxfile + fname.str();
        phenoxout.open(phxfile.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    phenoxout << TEMP.getPhenotypeX() << endl;
                }
            } else {
                for (int j = 0; j < PopulationSize[i]; j++) {
                    phenoxout << getPhenotypeXs(j) << endl;
                }
            }
        }
        phenoxout.close();
        phxfile.clear();
    }
    if (checkCommand(Phnc)) {
        cout << " & y phenotypes" << endl;
        fname.str("");
        fname << phyfile << simu << ".txt";
        phyfile = "phenotypeY_EvoSim_";
        phyfile = phyfile + fname.str();
        phenoyout.open(phyfile.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    phenoyout << TEMP.getPhenotypeY() << endl;
                }
            } else {
                for (int j = 0; j < PopulationSize[i]; j++) {
                    phenoyout << getPhenotypeYs(j) << endl;
                }
            }
        }
        phenoyout.close();
        phyfile.clear();
    }
    if (checkCommand(Parc)) {
        cout << "parents 1";
        fname.str("");
        fname << par1file << simu << ".txt";
        par1file = "parent1_EvoSim_";
        par1file = par1file + fname.str();
        par1out.open(par1file.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    par1out << TEMP.getParent1Identity() << endl;
                }
            } else {
                for (int j = 0; j < getPopulationSize(i); j++) {
                    par1out << getParent1s(j) << endl;
                }
            }
        }
        par1out.close();
        par1file.clear();
    }
    if (checkCommand(Parc) && checkCommand(Sptc)) {
        cout << " & parents 2";
        fname.str("");
        fname << par2file << simu << ".txt";
        par2file = "parent2_EvoSim_";
        par2file = par2file + fname.str();
        par2out.open(par2file.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    par2out << TEMP.getParent2Identity() << endl;
                }
            } else {
                for (int j = 0; j < getPopulationSize(i); j++) {
                    par2out << getParent2s(j) << endl;
                }
            }
        }
        par2out.close();
        par2file.clear();
    }
    if (checkCommand(Nghc)) {
        cout << endl << "neighbors 1";
        fname.str("");
        fname << neigh1file << simu << ".txt";
        neigh1file = "neighbor1_EvoSim_";
        neigh1file = neigh1file + fname.str();
        neigh1out.open(neigh1file.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    neigh1out << TEMP.getNeighbor1Identity() << endl;
                }
            } else {
                for (int j = 0; j < getPopulationSize(i); j++) {
                    neigh1out << getNeighbor1s(j) << endl;
                }
            }
        }
        neigh1out.close();
        neigh1file.clear();
    }
    if (checkCommand(Nghc) && checkCommand(Sptc)) {
        cout << " & neighbors 2";
        fname.str("");
        fname << neigh2file << simu << ".txt";
        neigh2file = "neighbor2_EvoSim_";
        neigh2file = neigh2file + fname.str();
        neigh2out.open(neigh2file.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    neigh2out << TEMP.getNeighbor2Identity() << endl;
                }
            } else {
                for (int j = 0; j < getPopulationSize(i); j++) {
                    neigh2out << getNeighbor2s(j) << endl;
                }
            }
        }
        neigh2out.close();
        neigh2file.clear();
    }
    if (checkCommand(Mutc) && !checkCommand(Expc)) {
        cout << endl << "mutabilities";
        fname.str("");
        fname << mutfile << simu << ".txt";
        mutfile = "mutability_EvoSim_";
        mutfile = mutfile + fname.str();
        mutout.open(mutfile.c_str());
        for (int i = 0; i < gens; i++) {
            if (checkCommand() == 11111) {
                POP = getThisPopulationOfTheAncestors(i);
                for (int j = 0; j < (POP.intSizeOfThePopulation()); j++) {
                    TEMP = POP.getThisIndivOfThePopulation(j);
                    mutout << TEMP.getMutability() << endl;
                }
            } else {
                for (int j = 0; j < getPopulationSize(i); j++) {
                    mutout << getMutabilities(j) << endl;
                }
            }
        }
        mutout.close();
        mutfile.clear();
    }
    if (checkCommand(Genc)) {
        cout << endl << "genera" << endl;
        fname.str("");
        fname << gfile << simu << ".txt";
        gfile = "genus_EvoSim_";
        gfile = gfile + fname.str();
        genusout.open(gfile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            genusout << G.intSizeOfTheGenus() << endl;
        }
        genusout.close();
        gfile.clear();
    }
    if (checkCommand(Spsc)) {
        cout << "species abundances" << endl;
        fname.str("");
        fname << ssfile << simu << ".txt";
        ssfile = "species_size_EvoSim_";
        ssfile = ssfile + fname.str();
        speciessizeout.open(ssfile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            for (int j = 0; j < (G.intSizeOfTheGenus()); j++) {
                SPP = G.getThisSpeciesOfTheGenus(j);
                speciessizeout << SPP.intSizeOfTheSpecies() << endl;
            }
        }
        speciessizeout.close();
        ssfile.clear();
    }
    if (checkCommand(SpCc)) {
        cout << "centroids x";
        fname.str("");
        fname << scxfile << simu << ".txt";
        scxfile = "species_centroidX_EvoSim_";
        scxfile = scxfile + fname.str();
        speciescxout.open(scxfile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            for (int j = 0; j < (G.intSizeOfTheGenus()); j++) {
                SPP = G.getThisSpeciesOfTheGenus(j);
                speciescxout << SPP.getCentroidX() << endl;
            }
        }
        speciescxout.close();
        scxfile.clear();
    }
    if (checkCommand(SpCc)) {
        cout << " & centroids y" << endl;
        fname.str("");
        fname << scyfile << simu << ".txt";
        scyfile = "species_centroidY_EvoSim_";
        scyfile = scyfile + fname.str();
        speciescyout.open(scyfile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            for (int j = 0; j < (G.intSizeOfTheGenus()); j++) {
                SPP = G.getThisSpeciesOfTheGenus(j);
                speciescyout << SPP.getCentroidY() << endl;
            }
        }
        speciescyout.close();
        scyfile.clear();
    }
    if (checkCommand(Spdc)) {
        cout << "species diversity" << endl;
        fname.str("");
        fname << sdfile << simu << ".txt";
        sdfile = "species_diversity_EvoSim_";
        sdfile = sdfile + fname.str();
        speciesdout.open(sdfile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            for (int j = 0; j < (G.intSizeOfTheGenus()); j++) {
                SPP = G.getThisSpeciesOfTheGenus(j);
                speciesdout << SPP.getDensity() << endl;
            }
        }
        speciesdout.close();
        sdfile.clear();
    }
    if (checkCommand(Spic)) {
        cout << "indivs of species" << endl;
        fname.str("");
        fname << sifile << simu << ".txt";
        sifile = "species_indivs_EvoSim_";
        sifile = sifile + fname.str();
        speciesiout.open(sifile.c_str());
        for (int i = 0; i < gens; i++) {
            G = getThisGenusOfTheNations(i);
            for (int j = 0; j < (G.intSizeOfTheGenus()); j++) {
                SPP = G.getThisSpeciesOfTheGenus(j);
                for (int k = 0; k < (SPP.intSizeOfTheSpecies()); k++) {
                    speciesiout << SPP.getThisIndivOfTheSpecies(k);
                }
            }
        }
        speciesiout.close();
        sifile.clear();
    }
}

int ancestors::getPopulationSize(int k) const {
    return PopulationSize[k];
}

int ancestors::getParent1s(int k) const {
    return Parent1s[k];
}

int ancestors::getParent2s(int k) const {
    return Parent2s[k];
}

int ancestors::getNeighbor1s(int k) const {
    return Neighbor1s[k];
}

int ancestors::getNeighbor2s(int k) const {
    return Neighbor2s[k];
}

double ancestors::getMutabilities(int k) const {
    return Mutabilities[k];
}

double ancestors::getPhenotypeXs(int k) const {
    return PhenotypeXs[k];
}

double ancestors::getPhenotypeYs(int k) const {
    return PhenotypeYs[k];
}

void ancestors::doubleCheck(population* P) const {
    vector<indiv>::iterator It;
    int id, n1id, n2id, psize;
    psize = P->intSizeOfThePopulation();
    bool dc = true;
    It = P->beginOfThePopulation();
    cout << psize << endl;
    while (It < (P->endOfThePopulation())) {
        id = (*It).getIdentity();
        n1id = (*It).getNeighbor1Identity();
        n2id = (*It).getNeighbor2Identity();
        if (id < 0 || id > psize) {
            cout << id << " is false id!" << endl;
            dc = false;
        } else if (n1id < 0 || n1id > psize) {
            cout << n1id << " is false n1id!" << endl;
            dc = false;
        } else if (n2id < 0 || n2id > psize) {
            cout << n2id << " is false n2id!" << endl;
            dc = false;
        }
        It++;
    }
    //if(dc) {	return true; }else {	return false; }
}