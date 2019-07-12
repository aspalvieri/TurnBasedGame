#include "../header/RDevice.h"

int RDevice::randomInt(int min, int max)
{
	return uniform_int_distribution<int>{min, max}(rng);
}

double RDevice::randomDouble(double min, double max)
{
	return uniform_real_distribution<double>{min, max}(rng);
}
