#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <string>
#include <set>
#include <ctime>
#include <vector>

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

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

#endif