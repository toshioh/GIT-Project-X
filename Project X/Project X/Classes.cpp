#include "Classes.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <fstream>

/* CLINIC CLASS */

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


/* * * * *  CALENDAR CLASS * * * * */

void Calendar::setMonthYearNum(int month, int year) {
	if (month < 1 || month > 12) {
		cout << "Invalid month. Set to Jan by default." << endl;
		monthNum_ = 1;
	}
	else {
		monthNum_ = month;
	}

	if (year < 2020) {
		cout << "Past years are invalid. Current year set by default." << endl;
		yearNum_ = 2020;
		checkYear(2020);
	}
	else {
		yearNum_ = year;
		checkYear(year);
	}

	setnumOfDays(monthNum_);
}

void Calendar::checkYear(int year) {
	if (year % 400 == 0 || year % 4 == 0) {
		nDays_[1] = 29;
	}
	else if (year % 100 == 0) {
		nDays_[1] = 28;
	}
	else {
		nDays_[1] = 28;
	}
}

int Calendar::getYearNum() {
	return yearNum_;
}

int Calendar::getMonthNum() {
	return monthNum_;
}

string Calendar::getMonthName(int monthNum) {
	string months[] = { "Jan","Feb","Mar","Apr",
						"May","Jun","Jul","Aug",
						"Sep","Oct","Nov","Dec"};
	return (months[monthNum-1]);
}

void Calendar::setDayName(int day) {
	// index 0
	dayName_ = dNames_[day];
}

string Calendar::getDayName() {
	return dayName_;
}

int Calendar::dayNumber(int day, int month, int year) {
	static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

void Calendar::setnumOfDays(int monthnum) {
	numOfDays_ = nDays_[monthnum - 1];
}

int Calendar::getnumOfDays() {
	return numOfDays_;
}


/* * * * *  EMPLOYEE CLASS * * * * */

void Employee::setAvailability(string av) {
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

string Employee::getAvailability() {
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


/* * * * *  CSV CLASS * * * * */
/*
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
	fstream myFileout;
	myFileout.open(filename, ios::out | ios::app);
	
	int i;
	for (i = 0; i < size; i++) {
		if (i == 0) {
			myFileout << "Scheduler" << "," << names[i].getName() << ",";
		}
		else {
			myFileout << names[i].getName() << ",";
		}
	}
	myFileout.close();
}

void CSV::sendDates(string filename, Calendar c, int numofdays) {
	string dayname;
	int month, year, daynum;
	string date, monthname;
	fstream myFileout;

	myFileout.open(filename,ios::out | ios::app);
	
	int i;
	for (i = 0; i <= numofdays; i++) {
		if (i == 0) {
			myFileout << "\n";
		}
		else {
			month = c.getMonthNum();
			year = c.getYearNum();
			c.setDayName(c.dayNumber(i,month,year));
			monthname = c.getMonthName(month);

			date = c.getDayName() + " " + to_string(i) + "-" + monthname + "-" + to_string(year);
			myFileout << date << "\n";
		}
	}	
	myFileout.close();
}
*/