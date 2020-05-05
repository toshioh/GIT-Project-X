#include "Employee.h"

using namespace std;

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

