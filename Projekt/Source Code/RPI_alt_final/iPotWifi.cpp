#include "iPotWifi.h"

#define REPLY_LENGTH 8		// Er i uint8, bemærk at sensorerne bruger en uint16 hver - ie. dette skal være 2 * antal sensorer.

using boost::asio::ip::tcp;

uint16_t const* iPotWifi::getData() {
	busy.lock();

	try {
		boost::asio::io_context io_context;
		tcp::socket s(io_context);
		tcp::resolver resolver(io_context);
		boost::asio::connect(s, resolver.resolve("192.168.0.2", "8888"));
		char request[1] = { 'R' };
		size_t request_length = 1;

		// Skriver R til ESP
		boost::asio::write(s, boost::asio::buffer(request, request_length));

		// Modtager REPLY_LENGTH bytes
		uint8_t reply[REPLY_LENGTH];
		size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, (size_t)REPLY_LENGTH));

		// Omsætter uint8[8] til uint16[4]
		uint16_t replyIn16b[4];
		for (uint8_t valueIt = 0; valueIt != 4; valueIt++) {
			uint16_t tempValue = 0;
			tempValue += reply[2 * valueIt] << 8;
			tempValue += reply[2 * valueIt + 1];
			replyIn16b[valueIt] = tempValue;
		}

		// Omregn de fire værdier og gem i lastReadData
		lastReadData[0] = floor(0.25990 * replyIn16b[0] - 465.08);

		const uint16_t waterLevelCutoffs[6] = { 20200, 18700, 18030, 17740, 17230, 0 };
		for (uint8_t i = 0; i < 6; i++) {
			if (replyIn16b[1] > waterLevelCutoffs[i]) {
				lastReadData[1] = i * 20;
				break;
			};
		}

		lastReadData[2] = floor((replyIn16b[2] - 596) / 278.58);

		const uint16_t humidityLevelCutoffs[4] = { 17925, 17165, 16800, 0 };
		for (uint8_t i = 0; i < 4; i++) {
			if (replyIn16b[3] > humidityLevelCutoffs[i]) {
				lastReadData[1] = i;
				break;
			};
		}
	}
	catch (std::exception& e) {
		busy.unlock();
		return nullptr;
	}

	busy.unlock();
	return lastReadData;
}

