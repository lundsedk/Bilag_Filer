#include "PlanteID.hpp"


PlanteID::PlanteID(std::string name, char type) {
    setPlanteName(name);
    setPlanteType(type);
}

std::string PlanteID::getPlanteName() {
    return name_;
}

char PlanteID::getPlanteType() {
    return type_;
}

void PlanteID::setPlanteName(std::string name) {
    name_ = name;
}

void PlanteID::setPlanteType(char type) {
    type_ = type;
}

bool PlanteID::isEmpty() {
    if (name_.compare("") == 0 && type_ == 0)
        return true;
    else
        return false;
}

void PlanteID::erasePlanteID() {
    name_ = "";
    type_ = 0;
}
