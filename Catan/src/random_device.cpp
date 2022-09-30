
#include "random_device.h"

int RandomDevice::next()
{
	return std::uniform_int_distribution<>{2, 12}(ran);
}