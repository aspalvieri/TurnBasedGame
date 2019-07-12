#ifndef RDEVICE_H
#define RDEVICE_H

#include "Includes.h"

class RDevice {
public:
	//Random device
	random_device rd;
	mt19937 rng{ rd() };

	//Randomize
	int randomInt(int min, int max);
	double randomDouble(double min, double max);

private:

};

#endif//RDEVICE_H