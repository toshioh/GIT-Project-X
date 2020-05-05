#include "Clinic.h"
#include "Calendar.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <fstream>

using namespace std;

Clinic::Clinic(string clinicName, vector<string> min, int ideal, int max) {
	setName(clinicName);
	setMinStaff(min);
	setIdeal(ideal);
	setMax(max);
}

// Set Clinic's Name, Days open/closed, Number of staff for each clinic
void Clinic::setName(string clinicName) {
	name = clinicName;
}

void Clinic::setMinStaff(vector<string> min) {
	min_staff = min;
}
void Clinic::setIdeal(int ideal) {
	ideal_clinicians = ideal;
}

void Clinic::setMax(int max) {
	max_clinicians = max;
}


// Get Clinic's Name, Days open/closed, Number of staff for each clinic
string Clinic::getName() {
	return name;
}

vector<string> Clinic::getMinStaff() {
	return min_staff;
}
int Clinic::getIdeal() {
	return ideal_clinicians;
}
int Clinic::getMax() {
	return max_clinicians;
}
