#include "Classes.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <fstream>

/* CLINIC CLASS */

using namespace std;
/*
Clinic::Clinic(const string& clinicName, array<bool, 31> clinicDays, int numStaff){
	setName(clinicName);
	staff_ = numStaff;
	setDays(clinicDays);
}

// Set Clinic's Name, Days open/closed, Number of staff for each clinic
void Clinic::setName(const string& clinicName) {
	name_ = clinicName;
}

void Clinic::setStaff(int& numStaff) {
	staff_ = numStaff;
}

void Clinic::setDays(const array<bool, 31>& clinicDays) {
	days = clinicDays;
}

// Get Clinic's Name, Days open/closed, Number of staff for each clinic
string Clinic::getName() const {
	return name_;
}

array<bool, 31> Clinic::getDays() const {
	return days;
}

int Clinic::getStaff() const {
	return staff_;
}
*/


/* * * * *  CALENDAR CLASS * * * * */

void Calendar::setMonth(int month) {
	if (month < 1 || month > 12) {
		cout << "Invalid month. Set to Jan by default." << endl;
		month_ = 1;
	}
	else {
		month_ = month;
	}
}

void Calendar::setYear(int year) {
	if (year < 2020) {
		cout << "Past years are invalid. Current year set by default." << endl;
		year_ = 2020;
		leapYear_ = checkYear(2020);
	}
	else {
		year_ = year;
		leapYear_ = checkYear(year);
	}
}

void Calendar::setDate(int month, int year) {
	
}

bool Calendar::checkYear(int year) {
	if (year % 400 == 0 || year % 4 == 0) {
		numDays_[1] = 29;
		return true;
	}
	else if (year % 100 == 0) {
		return false;
	}
	else {
		return false;
	}
}

int Calendar::getMonth() {
	return month_;
}

string Calendar::getStartDay() {
	if (month_ == 1 && year_ == 2020) {
		return mo_startDay_[3];
	}
	else {

	}

}




/* * * * *  EMPLOYEE CLASS * * * * */

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


/* * * * *  CSV CLASS * * * * */

void CSV::setRows(int rows) {
	rows_ = rows;
}

void CSV::setCols(int cols) {
	cols_ = cols;
}

int CSV::getRows() {
	return rows_;
}

int CSV::getCols() {
	return cols_;
}

void CSV::sendNames(string filename, Employee* names, int size) {
	ofstream myFile(filename);
	int i;
	for (i = 0; i < size; i++) {
		if (i == 0) {
			myFile << "Scheduler" << ",";
		}
		myFile << names[i].getName() << ",";
	}
	myFile << "\n";
}


/* * * * *  MONTH CLASS * * * * */
/*
Month::Month(int month, int yr, int start) {
	setMonthName(month);
	setMonthNum(month);
	setYear(yr);
}

void Month::setMonthName(int month) {
	if (month < 1 || month > 12) {
		cout << "Invalid month. Set to Jan (1) by default." << endl;
		monthName_ = months_[0]; // default: January
	}
	else {
		monthName_ = months_[month - 1];
	}
}

void Month::setMonthNum(int month) {
	if (month < 1 || month > 12) {
		cout << "Invalid month. Set to 1 (Jan) by default." << endl;
		monthNum_ = 1; // default
		setMonthName(1);
		setDays(1);
	}
	else {
		monthNum_ = month;
		setMonthName(month);
		setDays(month);
	}
}

void Month::setYear(int yr) {
	if (yr < 2020) {
		cout << "Pick current or future year. Set to 2020 by default." << endl;
		year_ = 2020;
	}
	else {
		year_ = yr;
	}
}

void Month::setDays(int month) {
	if (month < 1 || month > 12) {
		cout << "Invalid month. Set to 1 (Jan) by default." << endl;
		numDays_ = daysnMonth_[0];
	}
	else {
		numDays_ = daysnMonth_[month - 1];
	}
}

void Month::setStartDay(int start) {
	if (start < 1 || start > getStartDay()) {

	}
	startDay_ = start;
}

string Month::getMonthName() {
	return monthName_;
}

int Month::getMonthNum() {
	return monthNum_;
}

int Month::getYear() {
	return year_;
}

int Month::getDays() {
	return numDays_;
}

int Month::getStartDay() {
	return startDay_;
}
*/