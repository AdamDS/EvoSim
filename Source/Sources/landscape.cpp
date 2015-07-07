#include "landscape.h"

landscape::landscape() { 
	setX(45);
	setY(45);
	setMaximumDistance();
	setShift(0);
	setShifted(0);
	setRate(0);
	setMin(1);
	setMax(4);
	TheLandscape = new double[getX()*getY()];
	for(int m = 0; m<getX()*getY(); m++) {	TheLandscape[m] = 0; }
}

landscape::landscape(int M, int N) {
	setX(4*M-3);
	setY(4*N-3);
	setMaximumDistance();
	setShift(0);
	setShifted(0);
	setRate(0);
	setMin(1);
	setMax(4);
	TheLandscape = new double[getX()*getY()];
	for(int m = 0; m<getX(); m++) {	
		for(int n = 0; n<getY(); n++) {
			setTheLandscape(m,n,0); 
		}
	}
}

landscape::landscape(int M, int N, int num_gen, int speed, int min, int max) {
	setX(4*M-3);
	setY(4*N-3);
	setMaximumDistance();
	setShift(4*(int(num_gen/speed)));
	setShifted(0);
	setRate(speed);
	setMin(min);
	setMax(max);
	TheLandscape = new double[getX()*getY()];
	for(int m = 0; m<getX(); m++) {	
		for(int n = 0; n<getY(); n++) {
			setTheLandscape(m,n,0); 
		}
	}
	ShiftedScape = new double[getX()*getShift()];
	for(int m = 0; m<getX(); m++) {
		for(int n = 0; n<getShift(); n++) {
			setShiftedScape(m,n,0);
		}
	}
}

landscape::~landscape() {	
	delete [] TheLandscape; 
	delete [] ShiftedScape;
}

void landscape::setBasicMap(CRandomMersenne* bRand) {
	for(int n = 0; n<getY(); n++) {
		setRowForBasicMap(n,bRand);
		n = n+3; //add 3 since for adds another 1 each loop
	}
}

void landscape::interp2(int x0, int xf, int y0, int yf) {
	/* Interpolate twice by averaging
	Steps 1 and 2 interpolate between BasicMap grid points.
	Steps 3 and 4 interpolate a second time between the updated grid points
	from the BasicMap and steps 1 and 2.*/
	int a, b;
	double f1, f2;
	double f = 0;
	//step 1	
	//interpolate along y axis between BasicMap grid points
	for(a = x0+2; a<xf; a++) { // 2, 6, 10, 14, etc.
		for(b = y0; b<yf; b++) { // 0, 4, 8, 12, etc.
			f1 = getValueOfTheLandscape(a-2,b);
			f2 = getValueOfTheLandscape(a+2,b);
			f = (f1+f2)/2;
			setTheLandscape(a,b,f);
			b = b+3; //add 3 since for adds another 1 when doing loop
		}
		a = a+3; //add 3 since for adds another 1 when doing loop
	}
	//step 2
	//interpolate along x axis between BasicMap and step 1 points
	for(a = x0; a<xf; a++) { // 0, 2, 4, 6, etc.
		for(b = y0+2; b<yf; b++) { // 2, 6, 10, 14, etc.
			f1 = getValueOfTheLandscape(a,b-2);
			f2 = getValueOfTheLandscape(a,b+2);
			f = (f1+f2)/2;
			setTheLandscape(a,b,f);
			b = b+3; //add 3 since for adds another 1 when doing loop
		}
		a = a+1; //add 1 since for adds another 1 when doing loop
	}
	//step 3
	//interpolate along y axis to begin second interpolation
	for(a = x0+1; a<xf; a++) { // 1, 3, 5, 7, etc. 
		for(b = y0; b<yf; b++) { // 0, 2, 4, 6, etc.
			f = (getValueOfTheLandscape(a-1,b) + getValueOfTheLandscape(a+1,b))/2;
			setTheLandscape(a,b,f);
			b = b+1; //add 1 since for adds another 1 when doing loop
		}
		a = a+1; //add 3 since for adds another 1 when doing loop
	}
	//step 4
	//finish second interpolation along x axis
	for(a = x0; a<xf; a++) { // 0, 1, 2, etc.
		for(b = y0+1; b<yf; b++) { // 1, 3, 5, 7, etc.
			f = (getValueOfTheLandscape(a,b-1) + getValueOfTheLandscape(a,b+1))/2;
			setTheLandscape(a,b,f);
			b = b+1; //add 1 since for adds another 1 when doing loop
		}
	}
}

int landscape::getMaxXOfTheLandscape() const { return X; }

int landscape::getMaxYOfTheLandscape() const { return Y; }

int landscape::getMaxFitnessOfTheLandscape() const { return MAX; }

int landscape::getMinFitnessOfTheLandscape() const { return MIN; }

int landscape::getNearestFitnessOfTheLandscape(double indivsX, 
																							 double indivsY) const { 
	int disX, disY;
	double fitness;
	double indivsXint, indivsYint, indivsXfract, indivsYfract;
	indivsXfract = std::modf(indivsX, &indivsXint);
	if(indivsXfract<0.5) {
		disX = int(floor(indivsX));
		if(disX<0) {	disX = 0; }
	}else {
		disX = int(ceil(indivsX));
		if(disX>=getX()) {	disX = getX()-1; }
	}
	indivsYfract = std::modf(indivsY, &indivsYint);
	if(indivsYfract<0.5) {
		disY = int(floor(indivsY));
		if(disY<0) {	disY = 0; }
	}else {
		disY = int(ceil(indivsY));
		if(disY>=getY()) {	disY = getY()-1; }
	}
	fitness = getValueOfTheLandscape(disX,disY);
	return int(ceil(fitness)); 
}

double landscape::getValueOfTheLandscape(int ecks, int wai) const {
	if(ecks>=getX() || wai>=getY() || ecks<0 || wai<0) { 
		throw "Cannot acces that landscape location (does not exist).";
	}
	return TheLandscape[(wai*getX())+ecks];
}

double landscape::getMaximumDistance() const { return MaximumDistance; }

void landscape::setX(int x) {	X = x; }

void landscape::setY(int y) {	Y = y; }

void landscape::setMaximumDistance() {
	MaximumDistance = pow(double(getX()),2);
	MaximumDistance = MaximumDistance+pow(double(getY()),2);
	MaximumDistance = pow(MaximumDistance,0.5);
}

void landscape::setMax(int max) {	MAX = max; }

void landscape::setMin(int min) {	MIN = min; }

void landscape::setRowForBasicMap(int n, CRandomMersenne* baseRand) {
	int max = getMax();
	int min = getMin();
	double fitness;
	for(int m = 0; m<getX(); m++) {
		fitness = (max-min)*(baseRand->Random())+min;
		setTheLandscape(m,n,fitness); 
		m = m+3; //add 3 since for adds another 1 each loop
	}
}

void landscape::setTheLandscape(int x, int y, double fit) {
	if(x>=getX() || y>=getY() || x<0 || y<0) 
		throw "Cannot set to that landscape location (does not exist)";
	TheLandscape[(y*getX())+x] = fit;
}

int landscape::getX() const {	return X; }

int landscape::getY() const {	return Y; }

int landscape::getMin() const {	return MIN; }

int landscape::getMax() const {	return MAX; }

//////////////////////////////////////////////////
//LANDSCAPE CHANGES
//////////////////////////////////////////////////
void landscape::shiftTheLandscape(CRandomMersenne* r, int g) {
	//Shift TheLandscape by four rows at a time.  The last four rows of TheLandscape
	//are recorded in the open four rows of ShiftedScape starting from the Y end.
	//Shifting is done in the Y direction, so rows in the X direction are shifted
	//from "left" to "right" (lower index to higher index).
	if(((g+1)%getRate())==0) {
		// Interpolate twice by averaging
		//assign random numbers; fill elements 0, 3, 7, etc.
		int a, b, c, bi, bf, shftd;
		double f = 0;
		shftd = getShifted();
		if(getShift()!=0) {
			// get the last four rows of TheLandscape and set them to ShiftedScape
			c = getY()-1; // track rows of TheLandscape
			// track rows of ShiftedScape (setting rows from last to first)
			bi = getShift()-(4*getShifted())-1;  //set starting row to record
			bf = getShift()-(4*(getShifted()+1));  //set end row (not recorded now)
			for(b = bi; b>=bf; b--) {  //start recording to end of ShiftedScape
				for(a = 0; a<getX(); a++) {  //cycle through each row
					f = getValueOfTheLandscape(a,c);
					setShiftedScape(a,b,f);  //record old landscape
				}
				c--;
			}
			setShifted(shftd+1);  //update shifted
			// move all but the last four rows of TheLandscape down four rows
			for(b = getY()-5; b>=0; b--) {
				for(a = 0; a<getX(); a++) {
					f = getValueOfTheLandscape(a,b);
					setTheLandscape(a,b+4,f);
					//// reset TheLandscape grid that has moved away
					//if(b<4) {	setTheLandscape(a,b,0); }
				}
			}
			// reset the first row of TheLandscape
			setRowForBasicMap(0,r);
			// interpolate within newly set region
			interp2(0,getX(),0,4);
		}
	}
}

double landscape::getValueOfShiftedScape(int ex, int why) const {
	if(ex>=getX() || why>=getShift() || ex<0 || why<0) { 
		throw "Cannot acces that shifted landscape location (does not exist).";
	}
	return ShiftedScape[(why*getX())+ex];
}

void landscape::setShiftedScape(int oldx, int oldy, double oldFit) {
	if(oldx>=getX() || oldy>=getShift() || oldx<0 || oldy<0) 
		throw "Cannot set to that shifted landscape location (does not exist)";
	ShiftedScape[(oldy*getX())+oldx] = oldFit;
}

void landscape::setShift(int shift) {	SHIFT = shift; }

void landscape::setShifted(int shifted) {	SHIFTED = shifted; }

void landscape::setRate(int rate) {	RATE = rate; }

int landscape::getShift() const {	return SHIFT; }

int landscape::getShifted() const {	return SHIFTED; }

int landscape::getRate() const {	return RATE; }

//////////////////////////////////////////////////
//LANDSCAPE WRITING
//////////////////////////////////////////////////
void landscape::setSaveLandCommands(char* fitc, char* slsc, 
																		char* vlsc, char* mlsc) {
	Fitc = fitc;
	Slsc = slsc;
	Vlsc = vlsc;
	Mlsc = mlsc;
}

char* landscape::getFitnessCommand() const {	return Fitc; }

char* landscape::getShiftedCommand() const {	return Slsc; }

char* landscape::getVaryingCommand() const {	return Vlsc; }

bool landscape::checkLandCommand(char* command) const {
	if(command[0]=='0') {	return true; }else {	return false; }
}

void landscape::writeTheLandscape(int simu) {
	ofstream fitout;
	ostringstream fname;
	string fitfile; 

	if(checkLandCommand(Fitc)) {
		fname.str("");
		fname<<fitfile<<simu<<".txt";
		fitfile = "fitness_EvoSim_";
		fitfile=fitfile+fname.str();
		fitout.open(fitfile.c_str());
		for(int i = getMaxXOfTheLandscape()-1; i==0; i--) {
			for(int j = getMaxYOfTheLandscape()-1; j==0; j--) {
				fitout << getValueOfTheLandscape(i,j) << ",";
			}
			fitout << endl;
		}
	}
}

void landscape::writeShiftedScape(int simu) {
	ofstream slsout;
	ostringstream fname;
	string slsfile; 

	if(checkLandCommand(Slsc)) {
		fname.str("");
		fname<<slsfile<<simu<<".txt";
		slsfile = "shifted_EvoSim_";
		slsfile=slsfile+fname.str();
		slsout.open(slsfile.c_str());
		for(int i = getX()-1; i==0; i--) {
			for(int j = getShift()-1; j==0; j--) {
				slsout << getValueOfShiftedScape(i,j) << ",";
				}
			slsout << endl;
		}
		slsout.close();
		slsfile.clear();
	}
}
//CRandomMersenne landscape::getRandom() { return SequenceKeeper; };	

//void landscape::finalizeTheLandscape(double templand[]) {
//	int intf;
//	double f;
//	for(int a = 0; a<X; a++) { 
//		for(int b = 0; b<Y; b++) {
//			if(a>=X || b>=Y) 
//			throw "Cannot set to that landscape location (does not exist)";
//			f = templand[a * X+b];
//			intf = int(ceil(f));
//			setTheLandscape(a,b,intf);
//		}
//	}
//}
//void landscape::initializeRandom(int seed) { 
//	CRandomMersenne jo(seed);
//	setRandom(jo);
//}
//void landscape::setRandom(CRandomMersenne sk) { SequenceKeeper = sk; }

//double** TheLandscape = new double*[X];
	//for(int m = 0; m<X; m++) { 
	//	TheLandscape[m] = new double[Y];
	//	for(int n = 0; n<Y; n++) {
	//		TheLandscape[m][n] = 0;
	//	}
	//}

	//for(a = 0; a<X; a++) {
	//	for(b = 0; b<Y; b++) {	
	//		f = 10*(mtrand1.Random());
	//		setTheLandscape(a,b,f);//assign random numbers
	//		b = b+4;
	//	}
	//	a = a+4;
	//}
		//}	
		//if(a==0 || (a-X<5 && a-X>=0)) {
		//	for(b = 2; b<Y; b++) {
		//		f = (TheLandscape[a * X+b-2] + TheLandscape[a+2 * X+b+2])/2;
		//		setTheLandscape(a,b,f);//
		//		b = b+4;
		//	}
		//}
		//for(b = 1; b<Y; b++) {
		//	f = (TheLandscape[a * X+b-1] + TheLandscape[a+1 * X+b+1])/2;
		//	setTheLandscape(a,b,f);
		//	b = b+2;
		//}
		//a = a+4;
	//}
	//first interpolation; fill elements 2, 5, 9, etc.
	//for(a = 2; a<X; a++) {
	//	for(b = 2; b<Y; b++) {
	//		setTheLandscape(a,b,((TheLandscape[a-2 * X+b-2] + TheLandscape[a+2 * X+b+2])/2));
	//		b = b+2;
	//	}
	//	a = a+4;
	//}
	////second interpolation; fill elements 1, 4, 6, 8, etc.
	//for(a = 1; a<X; a++) {
	//	for(b = 1; b<Y; b++) {
	//		setTheLandscape(a,b,((TheLandscape[a-1 * X+b-1] + TheLandscape[a+1 * X+b+1])/2));
	//		b = b+1;
	//	}
	//	a = a+1;
	//}
//from getNearestFitnessOfTheLandscape
/*if((indivsX%1)<0.5) {
		disX = int(floor(indivsX));
		if(disX<0) {	disX = 0; }
	}else {
		disX = int(ceil(indivsX));
		if(disX>=X) {	disX = X-1; }
	}
	if((indivsY%1)<0.5) {
		disY = int(floor(indivsY));
		if(disY<0) {	disY = 0; }
	}else {
		disY = int(ceil(indivsY));
		if(disY>=Y) {	disY = Y-1; }
	}*/