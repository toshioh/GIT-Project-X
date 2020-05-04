#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <string>
#include <set>
#include <ctime>

#ifndef CLASSES_H
#define CLASSES_H


class Clinic {
private:
	int max_clinicians_ = 5;
	int ideal_clinicians_ = 5;

public:
	

};


class Calendar {
private:
	// defaults
	int defaultMonth = 1;
	int defaultStart = 3; // enter into mo_startDay_

	std::string date_;
	int month_;
	int year_;
	int num_startDay_;
	bool leapYear_;
	std::string mo_startDay_[7] = { "Sun","Mon","Tues","Wed","Thu","Fri","Sat"};
	std::string months_[12] = { "Jan","Feb","Mar","Apr",
								"May","Jun","Jul","Aug",
								"Sep","Oct","Nov","Dec" };
	int numDays_[12] = { 31,29,31,30,
					     31,30,31,31,
					     30,31,30,31 }; // leap year (2020)
	

public:
	void setMonth(int);
	void setYear(int);
	void setDate(int, int);
	bool checkYear(int);
	int getMonth();
	std::string getStartDay();
};

class Employee {

private:
	std::string name_ = "employee";
	std::string license_ = "license";
	int hours_ = 80;
	std::string scheduleType_ = "fixed";

public:
	//Employee(const std::string&, const std::string&, int);

	void setName(std::string);
	void setLicense(std::string);
	void setHours(int);
	void setScheduleType(std::string);
	std::string getName();
	std::string getLicense();
	int getHours();
	std::string getScheduleType();
};

class CSV {
private:
	int rows_;
	int cols_;

public:
	void setRows(int);
	void setCols(int);
	int getRows();
	int getCols();
	void sendNames(std::string, Employee*, int);
};

#endif
