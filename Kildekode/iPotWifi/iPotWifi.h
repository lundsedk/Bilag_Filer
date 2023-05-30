#include <stdint.h>
#include <cmath>
#include <mutex>
#include <boost/asio.hpp>

/*
	klassen antager at der findes en TCP server på 192.168.0.2:8888, som returnerer uint8[8], når den får et enkelt 'R'
	iPotWifi er implementeret som singleton; istedet for en constructor kaldes getInstance, således:
		iPotWifi& my_iPotRef = iPotWifi::getInstance();
	getData() kan efterfølgende bruges til at opdatere data, og få en reference til denne, således:
		uint16_t const * returnVal = my_iPotRef.getData();
	retur-værdierne er alle i uint16, og er som følger:
		vandtank niveau, givet i 6 procent-intervaller (0, 20, 40, 60, 80, 100)
		fugtighed, givet i 4 procent-intervaller (0, 33, 66, 99)
		lys niveau, givet som procent af maksimalt målt lys og minimalt målt lys
		vægt, givet i g
	hvis der ikke kan oprettes forbindelse til TCP-serveren, returneres istedet en null-pointer
*/

class iPotWifi
{
public:
    static iPotWifi& getInstance() {
		static iPotWifi instance;
		return instance;
	}
	uint16_t const * getData();
	iPotWifi(iPotWifi const&) = delete;
	void operator=(iPotWifi const&) = delete;
private:
	iPotWifi() {};
	~iPotWifi() {};
	uint16_t lastReadData[4];
	std::mutex busy;
};

