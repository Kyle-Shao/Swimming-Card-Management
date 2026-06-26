#include "timeutil.h"

std::time_t getTime() {
	return std::time(nullptr);
}