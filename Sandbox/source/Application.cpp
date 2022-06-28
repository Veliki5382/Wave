#include <iostream>

namespace wave {

	_declspec(dllimport) void Print() {
		std::cout << "Welcome to Wave engine, future of gaming!" << std::endl;
	}

}

int main() {

	wave::Print();

	return 0;
}