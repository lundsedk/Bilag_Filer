#include "iPotWifi.h"
#include <iostream>
#include <string>

int main(){
	//std::cout << "getDataTest starting" << std::endl;
	iPotWifi& my_iPotRef = iPotWifi::getInstance();
	iPotWifi& my_iPotRef2 = iPotWifi::getInstance();
	iPotWifi& my_iPotRef3 = iPotWifi::getInstance();

	//std::cout << std::endl << &my_iPotRef << std::endl << &my_iPotRef2 << std::endl << &my_iPotRef3 << std::endl;

	uint16_t const * returnVal = my_iPotRef.getData();

	if (returnVal == nullptr) {
		std::cout << std::endl << "No connection to TCP server" << std::endl;
		return 0;
	}

	std::cout << std::endl << "main - returnVal from getData is: ";
	for (uint i = 0 ; i < 4 ; i++){
		std::cout << " " << returnVal[i];
	}
	std::cout << std::endl;

	// std::cout << "Light: " << (uint16_t)returnVal[0] << "Humidity: " << (uint16_t)returnVal[1] << "Weight: " << (uint16_t)returnVal[2] << "Water level: " << (uint16_t)returnVal[3] << std::endl;

	return 0;
}