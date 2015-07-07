#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "randomc.h"
#include "general.h"

class landscape {
    //LANDSCAPE BUILD AND ACCESS
public:
    landscape();
    landscape(int M, int N);
    landscape(int M, int N, int num_gen, int speed, int min, int max);
    ~landscape();
    void setBasicMap(CRandomMersenne* bRand);
    void interp2(int x0, int xf, int y0, int yf);
    int getMaxXOfTheLandscape() const;
    int getMaxYOfTheLandscape() const;
    int getNearestFitnessOfTheLandscape(double indivsX,
            double indivsY) const;
    int getMaxFitnessOfTheLandscape() const;
    int getMinFitnessOfTheLandscape() const;
    double getValueOfTheLandscape(int ecks, int wai) const;
    double getMaximumDistance() const;
private:
    int X;
    int Y;
    int MIN;
    int MAX;
    double MaximumDistance;
    double* TheLandscape;
    void setX(int x);
    void setY(int y);
    void setMaximumDistance();
    void setMax(int max);
    void setMin(int min);
    void setRowForBasicMap(int m, CRandomMersenne* baserand);
    void setTheLandscape(int x, int y, double fit);
    int getX() const;
    int getY() const;
    int getMin() const;
    int getMax() const;
    //LANDSCAPE SHIFTING
public:
    void shiftTheLandscape(CRandomMersenne* r, int g);
    double getValueOfShiftedScape(int ex, int why) const;
    int getShift() const;
    int getShifted() const;
    int getRate() const;
private:
    int SHIFT;
    int SHIFTED;
    int RATE;
    double* ShiftedScape;
    void setShiftedScape(int oldx, int oldy, double oldFit);
    void setShift(int shift);
    void setShifted(int shifted);
    void setRate(int rate);
    //STORE A CRANDOMMERSENNE FOR THE PROGRAM?
    //public:
    //void initializeRandom(int seed);
    //void setRandom(CRandomMersenne sk);
    //CRandomMersenne getRandom();
    //private:
    //CRandomMersenne SequenceKeeper;

public:
    void setSaveLandCommands(char* fitc, char* slsc, char* vlsc, char* mlsc);
    char* getFitnessCommand() const;
    char* getShiftedCommand() const;
    char* getVaryingCommand() const;
    bool checkLandCommand(char* command) const;
    void writeTheLandscape(int simu);
    void writeShiftedScape(int simu);
private:
    char* Fitc;
    char* Slsc;
    char* Vlsc;
    char* Mlsc;
};
#endif