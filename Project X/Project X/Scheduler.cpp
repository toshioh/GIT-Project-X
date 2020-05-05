#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <nlohmann/json.hpp>
#include "Classes.h"

using std::string;
using json = nlohmann::json;

void initClinics()
{
	Clinic chf("CHF", { "pediatric","adult" }, 5, 5);
	Clinic ths("THS", { "pediatric","adult" }, 2, 3);
	Clinic ppch("PPCH", { "pediatric","adult" }, 2, 3);
	/*
	std::cout << chf.getName() << std::endl;
	std::vector<string> list = chf.getMinStaff();
	for (int i = 0; i < 2; i++)
		std::cout << list[i] << "  ";
	std::cout << std::endl << chf.getIdeal() << std::endl;
	std::cout << chf.getMax() << std::endl;
	*/
}




int main() {
	int jsize, i;
	json jread;
	int m, y;

	Calendar cal;
	CSV mycsv;

	// User input for month and year
	std::cout << "Enter month #: ";
	std::cin >> m;
	std::cout << "Enter Year #: ";
	std::cin >> y;

	cal.setMonthYearNum(m,y);

	
	// Reading JSON
	std::ifstream jfile("User.json");
	jfile >> jread;
	

	jsize = jread.size();

	Employee* emp;
	emp = new Employee[jsize];

	// set employee attributes
	for (i = 0; i < jsize; i++) {
		emp[i].setName(jread[i]["Name"].get<string>());
		emp[i].setLicense(jread[i]["License"].get<string>());
		emp[i].setHours(jread[i]["Hours"].get<int>());
		emp[i].setScheduleType(jread[i]["Schedule Type"].get<string>());
	}

	// enter into csv
	mycsv.sendNames("CSV_test.csv", emp, jsize);
	mycsv.sendDates("CSV_test.csv", cal, cal.getnumOfDays());


	/*
	for (i = 0; i < jsize; i++) {
		std::cout << emp[i].getName() << std::endl;
		std::cout << emp[i].getLicense() << std::endl;
		std::cout << emp[i].getHours() << std::endl;
		std::cout << emp[i].getScheduleType() << std::endl;
	}
	*/

	/*
	1. JSON objects to Class objects
	2. start scheduling
	
	
    */
	delete[] emp;
	return 0;
}