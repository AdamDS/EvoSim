/* 
 * File:   mainEvoSim.cpp
 * Author: Amviot
 *
 * Created on August 8, 2011, 2:11 PM
 */

#include "ancestors.h"
//#include "landscape.h"
//need to take out temporary input from:
//indiv(int,double,doubl,int,landscape) landscape & second int
//setIndiv(int,double,double,int,landscape) landscape & second int
//setPhenotypeCoordinate(landscape,int,int) both ints

//int main(int args, char**arg)
int main() {
	
	//used to tell simulation run time
	double t, t0; 
	clock_t start_clock;

	//read in simulation options
	ifstream commander;
	commander.open("EvoSim_Commander.txt");
	char popcom[2];  //record population
	commander.get(popcom,2);
	char phncom[2];  //record phenotype locations
	commander.get(phncom,2);
	char parcom[2];  //record parent(s)
	commander.get(parcom,2);
	char nghcom[2];  //record neighbor(s)
	commander.get(nghcom,2);
	char mutcom[2];  //record mutabilities
	commander.get(mutcom,2);
	char gencom[2];  //record genus' information
	commander.get(gencom,2);
	char spscom[2];  //record species' details
	commander.get(spscom,2);
	char spCcom[2];  //record species' details
	commander.get(spCcom,2);
	char spdcom[2];  //record species' details
	commander.get(spdcom,2);
	char spicom[2];  //record species' indivs
	commander.get(spicom,2);
	char fitcom[2];  //record fitness landscape
	commander.get(fitcom,2);
	char slscom[2];  //record shifted landscape
	commander.get(slscom,2);
	char ngncom[2];  //option for NGEN
	commander.get(ngncom,2);
	char ipscom[2];  //option for initial population size
	commander.get(ipscom,2);
	char expcom[2];  //option to compete
	commander.get(expcom,2);
	char sptcom[2];  //option to Nate or Adam speciate
	commander.get(sptcom,2);
	char hrdcom[2];  //option to assortative mate or cleave
	commander.get(hrdcom,2);
	char mlscom[2];  //option to move landscape
	commander.get(mlscom,2);
	char vlscom[2];  //option to vary landscape height range
	commander.get(vlscom,2);
	commander.close();
	//print options chosen
	cout << "Options from EvoSim_Commander.txt:  ";
	cout << popcom << phncom << parcom << nghcom << mutcom;
	cout << gencom << spscom << spCcom << spdcom << spicom;
	cout << fitcom << slscom << ngncom << ipscom << expcom;
	cout << sptcom << hrdcom << mlscom << vlscom << endl;
	
	//basic options
	int sim, run_sim, num_sim, same;
	cout << "How many simulations should be run?  ";
	cin >> run_sim;
	if(run_sim>0) {
		cout << "What should the first file label be?  ";
		cin >> sim;
	}else {	sim = -1; }
	if(run_sim>1) {
		cout << "Should all simulations be the same (0 = no, 1 = yes)?  ";
		cin >> same;
	}else {	same = 1; }

	//initialize the primary random variable
  CRandomMersenne rm(int(time(NULL)));//for realz runz
	//CRandomMersenne rm(10);//test runs
	
	int ditto = 0;  //used to check if options should be the same
	int NGEN;  //maximum number of generations to run each simulation
	int lastGeneration;  //generation when competition ends
	int IPOP; //initial size of the population
	int unique;  //number of unique mutation parameters if opted for
	int lsX;  //seed landscape x length size
	int lsY;  //seed landscape y lengthh size
	int maxH;  //maximum fitness
	int minH;  //minimum fitness
	int moverate = 0;  //number of generations between shifting the landscape
	int moved = 0;  //counts number of times the landscape moves
	int maxX;  //largest x length of the landscape
	int maxY;  //largest y length of the landscape
	int create;  //number of indivs to generate
	double RNG1, RNG2, RNG3;  //random value for phenotypes and mutability
	double allmut;  //single mutation parameter
	vector<double> muts;  //list of mutation parameters
	indiv TEMP;  //indiv used for populating the population
	population POP;  //primary population
	population POPnew;  //place holding population after reproduction
	species SPP;  //species used for populating the genus
	genus G;	//primary genus
	ancestors ELDERS;  //master data collecting variable
	ofstream logout, timout;
	ostringstream fname;
	string lfile, tfile;

	//RUN PROGRAM RUN_SIM TIMES
	num_sim = sim+run_sim;
	for(sim; sim<num_sim; sim++) {  //SIMULATIONS LOOP
fname.str("");
fname<<tfile<<sim<<".txt";
tfile = "times_EvoSim_";
tfile=tfile+fname.str();
timout.open(tfile.c_str());
		cout << "Simulation:  " << sim-num_sim+run_sim+1 << " of " << run_sim << endl;

		if(ditto!=1) {
			//prompt for maximum generations if opted for
			if(ngncom[0]=='0') {
				NGEN = 1000;  //default
			}else if(ngncom[0]=='1') {
				cout << "Enter number of generations to run:  ";
				cin >> NGEN;
				cout << endl;
			}else {	NGEN = 1; }
			lastGeneration = NGEN;

			//prompt for initial population size if opted for
			if(ipscom[0]=='0') {
				IPOP = 300;  //default
			}else if(ipscom[0]=='1') {
				cout << "Enter initial population size:  ";
				cin >> IPOP;
				cout << endl;
			}else {	IPOP = 3; }
			unique = IPOP;

			//prompt for single mutation parameter if opted for
			if(expcom[0]=='0') {	
				cout << "Enter mutability:  ";
				cin >> allmut;
        cout << endl;
			}

			//initialize the landscape variables
			lsX = 12;
			lsY = 12;
			maxH = 4;
			minH = 1;
			//set landscape shift rate
			if(mlscom[0]=='0') {
				moverate = 2;  //this is default from original model
			}else if(mlscom[0]=='1') {
				cout << "Enter rate of shifting landscape:  ";
				cin >> moverate;
        cout << endl;
			}else { moverate = 10101010; }
			//set landscape height variation
			if(vlscom[0]=='0') {
				minH = 1;
				maxH = 4;
			}else if(vlscom[0]=='1') {
				minH = 1;
				maxH = 0;
				while(maxH<minH) {
					cout << "Enter worst fitness value:  ";
					cin >> minH;
					cout << endl << "Enter best fitness value:  ";
					cin >> maxH;
          cout << endl;
					if(minH>maxH) {	cout << "Redo fitness entries, ";
						cout << "best must be >= worst." << endl; 
					}
				}
			}else { 
				minH = 1; 
				maxH = 1; 
			}
			if(same==1) {	ditto = 1; }
		}//ditto
		landscape FitLand(lsX,lsY,NGEN,moverate,maxH,minH);

		//write out options to file for reference later
		fname.str("");
		fname<<lfile<<sim<<".txt";
		lfile = "options_EvoSim_";
		lfile=lfile+fname.str();
		logout.open(lfile.c_str());
		logout << "Saved:  " << endl;
		if(popcom[0]=='0') {	logout << "Yes "; 
		}else {	logout << " No "; }
		logout << "Population size" << endl;
		if(phncom[0]=='0') {	logout << "Yes ";
		}else { logout << " No "; }
		logout << "Phenotype coordinates" << endl;
		if(parcom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Parent(s)" << endl; 
		if(nghcom[0]=='0') {	logout << "Yes ";
		}else { logout << " No "; }
		logout << "Neighbor(s)" << endl; 
		if(mutcom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Mutabilities" << endl; 
		if(gencom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Number of species" << endl;
		if(spscom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Species size" << endl;
		if(spCcom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Species centroids" << endl;
		if(spdcom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Species details" << endl;
		if(spicom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Indivs in each species" << endl;
		if(fitcom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Fitness landscape" << endl;
		if(slscom[0]=='0') {	logout << "Yes ";
		}else {	logout << " No "; }
		logout << "Shifted landscape" << endl;
		logout << endl;
		logout << "Experiment options are:  " << endl;
		logout << "NGEN = " << NGEN << endl;
		logout << "IPOP = " << IPOP << endl;
		if(expcom[0]=='0') {	logout << "Single mutability = " << allmut << endl; 
		}else if(expcom[0]=='1') {	logout << "Competition" << endl; }
		if(sptcom[0]=='0') {	logout << "Two nearest neighbors included in species seeds";
			logout << endl;
		}else if(sptcom[0]=='1') {	logout << "Nearest neighbor included in species seeds";
			logout << endl; }
		if(hrdcom[0]=='0') {	logout << "Reproduce by assortative mating";
			logout << endl;
		}else if(sptcom[0]=='1') {	logout << "Reproduce by bacterial cleaving";
			logout << endl; }
		if(mlscom[0]=='0') {	logout << "Move the landscape every 2 generations";
			logout << endl; 
		}else if(mlscom[0]=='1' && FitLand.getRate()<NGEN) {	logout << "Move the landscape every " << moverate;
			logout << " generations" << endl;
    }else if(mlscom[0]=='1' && FitLand.getRate()>=NGEN) { logout << "Landscape is stationary" << endl; }
		if(vlscom[0]=='0') {	logout << "Fitness varies between 1 and 4" << endl;
    }else if(vlscom[0]=='1' && FitLand.getMinFitnessOfTheLandscape()!=FitLand.getMaxFitnessOfTheLandscape()) {	
      logout << "Fitness varies between " << minH;
			logout << " and " << maxH << endl; 
    }else if(vlscom[0]=='1' && FitLand.getMinFitnessOfTheLandscape()==FitLand.getMaxFitnessOfTheLandscape()) { 
      logout << "Fitness is neutral at " << FitLand.getMinFitnessOfTheLandscape() << " fitness" << endl;  }
		logout.close();
		lfile.clear();

		start_clock = clock();  //start timing;

		//prepare variables with default values
		moved = 0;
		maxX = (((lsX*2)-1)*2)-1;
		maxY = (((lsY*2)-1)*2)-1;
		create = IPOP;
				
		//initialize the ancestors 
		ELDERS.setSaveCommands(popcom,phncom,parcom,nghcom,mutcom,
														gencom,spscom,spCcom,spdcom,spicom,sptcom,expcom);
		
		//initialize the fitness landscape
		FitLand.setSaveLandCommands(fitcom,slscom,vlscom,mlscom);
		FitLand.setBasicMap(&rm);
		maxX = FitLand.getMaxXOfTheLandscape();
		maxY = FitLand.getMaxYOfTheLandscape();
		FitLand.interp2(0,maxX,0,maxY);

		//initialize population
		POP.setDeathChance(0.7);
		POP.setOverPopulationLimit(0.25);
    POP.setExtinctionLimit(3);
    if (sptcom[0] == 1) { POP.setExtinctionLimit(2); }

		while(POP.intSizeOfThePopulation()!=IPOP) {	//ensure initial POP has 300
		
			for(int d = 0; d<create; d++) {  //LOOP POPULATION
				
				//initialize random variables
				RNG1 = rm.Random();
				RNG2 = rm.Random();
				if(expcom[0]=='1') {	RNG3 = rm.Random(); 
				}else if(expcom[0]=='0') {	RNG3 = allmut; 
				}else {	RNG3 = 0; }
				
				//initiate and include new indiv
				TEMP.setIndiv(d,&FitLand,RNG1,RNG2,RNG3);
				POP.addToPopulation(TEMP);
			}

			//POP.CrowdControl(&FitLand); //Does not happen in the Matlab version
			//if indiv's were killed by CrowdControl, go back and create them again
			create = POP.getKillCount();
		}
	
		//POP.setNeighbors(&FitLand); //Where the Matlab version sets neighbors
		
		//initiate clock timer
		t0 = double(clock());
    bool KEEP_GOING = true;

		//LOOP GENERATIONS
		for(int gen = 0; gen<NGEN; gen++) {

      if(POP.intSizeOfThePopulation()>=POP.getExtinctionLimit()) {
			  //determine neighbor(s) for every indiv  
    	  POP.setNeighbors(&FitLand);

			  //print updates every so many generations
			  //if(gen%10==0) {
				  t = (clock()-start_clock)/(double) CLOCKS_PER_SEC;
				  cout << "Simulation:  " << sim << "; ";
				  cout << "Generation:  " << gen << "; ";
				  cout << "Population size:  " << POP.intSizeOfThePopulation() << "; ";
				  cout << "CPU time:  " << t << "sec " << endl;
			  //}
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
      }
			//make sure enough indivs for speciation if opted to save
			if(sptcom[0]=='0') {
        if(POP.intSizeOfThePopulation()<=POP.getExtinctionLimit()) {	
          cout << "There are less than " << POP.getExtinctionLimit() << " indivs in the population";
          cout << " in generation " << gen << endl;
					KEEP_GOING = false;
          lastGeneration = gen;
          cout << "The last recorded generation will be " << lastGeneration-1 << endl;
          gen = NGEN;
        }else if (POP.getExtinctionLimit() == 3) {
					G.NateSpeciation(&POP);
        }else if (POP.getExtinctionLimit() == 2) {
					G.AdamSpeciation(&POP); 
				}
			} else {	
				cout << "No speciation!" << endl;
        if(POP.intSizeOfThePopulation()<=POP.getExtinctionLimit()) {
          KEEP_GOING = false;
          gen = NGEN;
        }
			}
      if (KEEP_GOING == true) {
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
			  //calculate species' centroid coordinate and density if opted to save
			  if(ELDERS.checkCommand(spCcom)) {	
				  G.Centroids(&POP);	
			  }
			  if(ELDERS.checkCommand(spdcom)) {
				  G.Densities(&POP);
			  }
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
			  //collect population and genus to write later
			  ELDERS.addToTheAncestors(POP); 
			  ELDERS.addToTheNations(G);
			
			  //unique mutability tells when competition completes
			  if(expcom[0]=='1') {
				  unique = POP.uniqueMutability(); 
				  if(unique==1) {
					  lastGeneration = gen;
					  gen = NGEN;
				  }
			  }
			
			  //circle of life...except for NGENth population
			  if(gen<(NGEN)) {
				  //birth
				  if(hrdcom[0]=='0') {	POPnew = ELDERS.assortativeMating(&FitLand,&POP,&rm);
				  }else if(hrdcom[0]=='1') {	POPnew = ELDERS.cleaving(&FitLand,&POP,&rm);
				  }else {	POPnew = POP; }
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
				  //death
				  POPnew.CrowdControl(&rm);
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
          if (POPnew.intSizeOfThePopulation() >= POPnew.getExtinctionLimit())
            POPnew.RussianRoulette(&rm);
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
				  if (POPnew.intSizeOfThePopulation() >= POPnew.getExtinctionLimit())
            POPnew.CliffJumpers(&FitLand);
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
			}
			
			  //reset population and genus
			  G.resetGenus();
			  POP.resetThePopulation();
			  POP = POPnew;
			  POPnew.resetThePopulation();
			
			  //shift landscape if opted for
			  FitLand.shiftTheLandscape(&rm,gen); 
timout << (clock()-start_clock)/(double) CLOCKS_PER_SEC << ",";
timout << POP.intSizeOfThePopulation() << ",";
timout << POP.getCJKillCount() << ",";
timout << POP.getOPKillCount() << ",";
timout << POP.getRRKillCount() << endl;
      }
		}//END GENERATION LOOP
timout.close();
tfile.clear();
		//save data to files
    if(FitLand.getMinFitnessOfTheLandscape()!=FitLand.getMaxFitnessOfTheLandscape())
  		FitLand.writeTheLandscape(sim);
		if(NGEN<FitLand.getRate()) {
			FitLand.writeShiftedScape(sim);
		}
		ELDERS.writeAncestors(sim,lastGeneration);

		//reset for next run
		POP.resetThePopulation();
		ELDERS.resetTheAncestors();

		//print total simulation time
		t=(clock()-start_clock)/(double) CLOCKS_PER_SEC;
		cout<<"\nCPU time:"<<t<<"sec "<<endl;

	}//END SIMULATIONS LOOP
	
	cout << "ALL done!" << endl;
	char u;
	cout << "Press any alphanumeric key, then [Enter] to exit.  ";
	cin >> u;
	return 0;

}//end main