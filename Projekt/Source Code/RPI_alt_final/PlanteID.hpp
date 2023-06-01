#ifndef PLANTEID_
#define PLANTEID_

#include <string>

#define TYPE_FLOWER 1
#define TYPE_LEAF 2
#define TYPE_CACTUS 3

class PlanteID {
public:
	PlanteID(std::string name = "", char type = 0);
	std::string getPlanteName();
	char getPlanteType();
	void setPlanteName(std::string name);
	void setPlanteType(char type);
	bool isEmpty();
	void erasePlanteID();
private:
	std::string name_;
	char type_;
};
#endif
