#include "Wave.h"
#include <iostream>

namespace wave {
	
	_declspec(dllexport) void Print() {
		std::cout << "Welcome to Wave engine, future of gaming!" << std::endl;
	}

}
