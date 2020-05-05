#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <string>
#include <set>
#include <ctime>
#include <vector>

#ifndef CLASSES_H
#define CLASSES_H


class Clinic {
private:
	std::string name;
	int max_clinicians;
	int ideal_clinicians;
	std::vector<std::string> min_staff; //A list of the bare minimum staff listed by Pediatric or Adult

public:
	Clinic(std::string, std::vector<std::string>, int, int);
	void setName(std::string);
	void setMinStaff(std::vector<std::string>);
	void setMax(int);
	void setIdeal(int);

	std::string getName();
	std::vector<std::string> getMinStaff();
	int getMax();
	int getIdeal();
};


class Calendar {
private:
	int         monthNum_;
	int         yearNum_;
	int			numOfDays_;
	std::string dayName_;
	bool        leapYear_;
	std::string dNames_[7] = { "Sun","Mon","Tues","Wed","Thu","Fri","Sat"};
	int			nDays_[12] = { 31,28,31,30,
							   31,30,31,31,
							   30,31,30,31 }; // not leap year;

public:
	void        setMonthYearNum(int,int);
	int         getMonthNum();
	std::string getMonthName(int);
	int         getYearNum();
	void        setDayName(int);
	std::string getDayName();
	int         dayNumber(int, int, int);
	void		setnumOfDays(int);
	int         getnumOfDays();

	void        checkYear(int);
};


class Employee {

private:
	std::string name_;
	std::string license_;
	int hours_ = 80;
	std::string scheduleType_;

public:
	//Employee(const std::string&, const std::string&, int);

	void		setName(std::string);
	void		setLicense(std::string);
	void		setHours(int);
	void		setScheduleType(std::string);
	std::string getName();
	std::string getLicense();
	int			getHours();
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
	void sendDates(std::string, Calendar, int);
};

#endif
