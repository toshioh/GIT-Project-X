#include "Employee.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <fstream>

using namespace std;


void Employee::setAvailability(vector<string> av) {
	availability_ = av;
}

void Employee::setPrefAge(string prefage) {
	prefAge_ = prefage;
}

void Employee::setName(string empName) {
	name_ = empName;
}

void Employee::setLicense(string license) {
	license_ = license;
}

void Employee::setHours(int hours) {
	hours_ = hours;
}

void Employee::setScheduleType(string type) {
	scheduleType_ = type;
}

vector<string> Employee::getAvailability() {
	return availability_;
}

string Employee::getPrefAge() {
	return prefAge_;
}

string Employee::getName() {
	return name_;
}

string Employee::getLicense() {
	return license_;
}

int Employee::getHours() {
	return hours_;
}

string Employee::getScheduleType() {
	return scheduleType_;
}
