#include "helper.h"


helper::helper()
{
}


helper::~helper()
{
}

int helper::sign(int in)
{
	if (in >= 0)
		return 1;
	return -1;
}

int helper::sign(double in)
{
	if (in >= 0)
		return 1;
	return -1;
}
