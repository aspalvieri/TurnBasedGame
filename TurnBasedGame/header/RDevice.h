#ifndef RDEVICE_H
#define RDEVICE_H

#include "Includes.h"

class RDevice {
public:
	//Randomize functions
	int randomInt(int min, int max);
	double randomDouble(double min, double max);

private:
	//Random device
	random_device rd;
	mt19937 rng{ rd() };
};

#endif//RDEVICE_H