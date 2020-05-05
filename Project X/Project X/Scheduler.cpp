#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <nlohmann/json.hpp>
#include <vector>
#include "Support/Employee.h"
#include "Support/Clinic.h"
#include "Support/Calendar.h"

using std::string;
using json = nlohmann::json;

/* initialize classes */
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


/* Main function */

int main() {
	int jsize, i;
	json jread;
	int m, y;

	Calendar cal;

	// User input for month and year
	std::cout << "Enter month #: ";
	std::cin >> m;
	std::cout << "Enter Year #: ";
	std::cin >> y;

	cal.setMonthYearNum(m,y);

	
	// Reading JSON
	std::ifstream jfile("User.json");
	jfile >> jread;
	
	
	std::cout << jread[0]["Available Days"].size() << std::endl;
	jsize = jread.size();

	Employee* emp;
	emp = new Employee[jsize];

	
	// set employee attributes
	int avsize, j;
	json::iterator it;

	std::vector<string> vect;
	for (i = 0; i < jsize; i++) {
		emp[i].setName(jread[i]["Name"].get<string>());
		
		avsize = jread[i]["Available Days"].size();
		std::cout << jread[i]["Available Days"].type_name() << std::endl;
		
		it = jread[i]["Available Days"].begin();

		// Set Available Days
		for (it = jread[i]["Available Days"].begin(); it != jread[i]["Available Days"].end(); it++) {
			std::cout << *it << std::endl;
		}
	}

	
	
	
	// enter into csv
	//mycsv.sendNames("CSV_test.csv", emp, jsize);
	//mycsv.sendDates("CSV_test.csv", cal, cal.getnumOfDays());


	/*
	1. JSON objects to Class objects
	2. start scheduling
    */

	delete[] emp;
	return 0;
}