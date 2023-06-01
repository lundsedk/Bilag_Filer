#include <stdint.h>
#include <cmath>
#include <mutex>
#include <boost/asio.hpp>

/*
	klassen antager at der findes en TCP server p� 192.168.0.2:8888, som returnerer uint8[8], n�r den f�r et enkelt 'R'
	iPotWifi er implementeret som singleton; istedet for en constructor kaldes getInstance, s�ledes:
		iPotWifi& my_iPotRef = iPotWifi::getInstance();
	getData() kan efterf�lgende bruges til at opdatere data, og f� en reference til denne, s�ledes:
		uint16_t const * returnVal = my_iPotRef.getData();
	retur-v�rdierne er alle i uint16, og er som f�lger:
		v�gt, givet i g
		vand niveau, givet i procent-intervaller (0, 20, 40, 60, 80, 100)
		lys-niveau, givet som procent af maksimalt m�lt lys og minimalt m�lt lys
		fugtighed, givet i fire mulige v�rdier (0,1,2,3), tilsvarende t�r, optimal, lidt for v�d, druknet
			(ved 0/t�r sker der vanding)
	hvis der ikke kan oprettes forbindelse til TCP-serveren, returneres istedet en null-pointer
*/

class iPotWifi
{
public:
	static iPotWifi& getInstance() {
		static iPotWifi instance;
		return instance;
	}
	uint16_t const* getData();
	iPotWifi(iPotWifi const&) = delete;
	void operator=(iPotWifi const&) = delete;
private:
	iPotWifi() {};
	~iPotWifi() {};
	uint16_t lastReadData[4];
	std::mutex busy;
};

