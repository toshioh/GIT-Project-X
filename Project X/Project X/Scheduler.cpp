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
using std::vector;
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

int findQualifiedEmpIndex(std::vector<Employee> &employees, string neededAgeGroup, int osize)
{
	int index = -1;
	//int check = 0;
	for (int i = 0; i < osize; i++)
	{
		string empPrefAge = employees[i].getPrefAge();
		if (neededAgeGroup == empPrefAge || empPrefAge == "family") {
			index = i;
			i = osize;
		}
	}
	if (index == -1)
	{
		throw std::invalid_argument("No employees left to fill this position!");
	}
	else {
		employees[index].setPrefAge("null");
	}
	return index;
}

vector<Employee> initEmployee(json jread, int jsize) {
	std::vector<Employee> emp;
	Employee newemp;
	json::iterator it;
	int i;

	// Read JSON attributes
	for (i = 0; i < jsize; i++) {
		// Set Name and Preferred Age
		emp.push_back(newemp);
		emp[i].setName(jread[i]["Name"].get<string>());
		emp[i].setPrefAge(jread[i]["Preferred Age"].get<string>());
		// Set Available Days
		it = jread[i]["Available Days"].begin();
		for (it = jread[i]["Available Days"].begin(); it != jread[i]["Available Days"].end(); it++) {
			emp[i].setAvailability(*it);
		}
	}
	return emp;
}

void removeAvailable(vector<Employee>& employees, string day)
{
	int size = employees.size();
	for (int i = 0; i < size; i++)
	{
		vector<string> availableDays = employees[i].getAvailability();
		vector<string>::iterator it;

		it = find(availableDays.begin(), availableDays.end(), day);
		if (it == availableDays.end())
			employees[i].setPrefAge("NULL");
	}
}


/* Main function */

int main() {
	int jsize, i, m, y;
	json jread;
	Calendar cal;
	vector<string> vect;
	vector<Employee> enew;

	// User input for month and year
	/*
	std::cout << "Enter month #: ";
	std::cin >> m;
	std::cout << "Enter Year #: ";
	std::cin >> y;

	cal.setMonthYearNum(m,y);
	*/
	
	// Reading JSON
	std::ifstream jfile("User.json");
	jfile >> jread;
	jsize = jread.size();
	
	// Read into Employee vector of size jsize
	enew = initEmployee(jread, jsize);



// Testing revmoveAvailable
	removeAvailable(enew, "Tue");
	std::cout << "Removeable age test: " << std::endl;
	std::cout << enew[0].getPrefAge() << std::endl;
	std::cout << enew[1].getPrefAge() << std::endl;
	std::cout << enew[2].getPrefAge() << std::endl;
	std::cout << enew[3].getPrefAge() << std::endl;
// End of Tesing
	
// Testing Availability
	std::cout << "Get Availability test: " << std::endl;
	vect = enew[3].getAvailability();
	for (auto itt = vect.begin(); itt != vect.end(); itt++) {
		std::cout << *itt << " ";
	}
	std::cout << "\n";
// End of Tesing

//Testing findQualifiedEmpIndex Function:
	std::cout << "Find qualified index test: " << std::endl;
	int indx;
	indx = findQualifiedEmpIndex(enew, "adult", jsize);
	std::cout << indx << std::endl;
	std::cout << enew[indx].getName() << std::endl;
	std::cout << enew[indx].getPrefAge() << std::endl;
	
	indx = findQualifiedEmpIndex(enew, "adult", jsize);
	std::cout << indx << std::endl;
	std::cout << enew[indx].getName() << std::endl;
	std::cout << enew[indx].getPrefAge() << std::endl;

// End of Testing

	//delete[] emp;
	return 0;
}