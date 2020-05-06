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
vector<Clinic> initClinics()
{
	vector<Clinic> clinic;
	Clinic chf("CHF", { "pediatric","adult" }, 5, 5);
	clinic.push_back(chf);
	Clinic ths("THS", { "pediatric","adult" }, 2, 3);
	clinic.push_back(ths);
	Clinic ppch("PPCH", { "pediatric","adult" }, 2, 3);
	clinic.push_back(ppch);

	/*
	std::cout << chf.getName() << std::endl;
	std::vector<string> list = chf.getMinStaff();
	for (int i = 0; i < 2; i++)
		std::cout << list[i] << "  ";
	std::cout << std::endl << chf.getIdeal() << std::endl;
	std::cout << chf.getMax() << std::endl;
	*/
	return clinic;
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
	if (index == -1) {
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


vector<string> scheduleDates(Calendar c)
{
	string dayname;
	int month, year, daynum;
	string date, monthname;

	int numOfDays = c.getnumOfDays();
	std::cout << numOfDays << std::endl;
	vector<string> allDates;
	for (int i = 0; i <= numOfDays; i++) {
		if (i == 0) {
			allDates.push_back(" ");
		}
		else {
			month = c.getMonthNum();
			year = c.getYearNum();
			c.setDayName(c.dayNumber(i, month, year));
			monthname = c.getMonthName(month);

			date = c.getDayName() + " " + std::to_string(i) + "-" + monthname + "-" + std::to_string(year);
			allDates.push_back(date);
		}
	}
	return allDates;
}


vector<vector<string>> createCalendar(vector<string> dates, vector<Employee> emp, vector<Clinic> cln) {
	vector<vector<string>> calendar;
	vector<string> row;
	vector<string> avdays;
	string empName;
	string currdate, currday;
	string prefage, ageNeed;

	int qindex;

	for (int i = 0; i <= dates.size(); i++) {
		for (int j = 0; j < emp.size(); j++) {
			if (i == 0) {
				// Make name row
				empName = emp[j].getName();
				row.push_back(empName);
			}
			else {
				/*
				prefage = emp[i].getPrefAge();
				avdays  = emp[i].getAvailability();

				currdate = dates[i];
				currday = currdate.substr(0, 3);
				std::cout << currday << std::endl;
				// make function
				if (currday == "Sun" || currday == "Sat") {
					row.push_back(" "); // no weekends
				}
				else {
					
					int csize = cln.size();
					int ecount = 0;
					removeAvailable(emp,currday);
					for (int k = 0; k < csize; k++) {
						if (ecount == cln[k].getMax()) {
							// max clinicians met
						}else if(ecount >= cln[k].getIdeal()) {
							string staff = cln[k].getMinStaff;
							qindex = findQualifiedEmpIndex(emp,cln[k].getMinStaff());
						}
						//qindex = findQualifiedEmpIndex(emp, );
					}
					
					//row.push_back(clinic.getName());
					
				}
				*/
			}
		}
	}
	calendar.push_back(row);
	return calendar;
}


/* Main function */

int main() {
	int jsize, i, m, y;
	json jread;
	Calendar cal;
	vector<Clinic> clinic;
	vector<string> vect;
	vector<Employee> enew;

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
	
	// Read into Employee vector of size jsize
	enew = initEmployee(jread, jsize);
	clinic = initClinics();


// Testing schedule Dates
	std::cout << "Schedule test: " << std::endl;
	vector<string> dates;
	dates = scheduleDates(cal);
	std::cout << dates.size() << std::endl;
	string currentDay;
	for (int k = 0; k < dates.size(); k++) {
		currentDay = dates[k];
		std::cout << currentDay << std::endl;
	}
// End of Tesing

// Testing Calendar make:
	std::cout << "Calendar row test: " << std::endl;
	vector<vector<string>> calendar;
	vector<string> getvect;
	string getcal;
	calendar = createCalendar(dates, enew, clinic);
	std::cout << calendar.size() << std::endl;
	for (i = 0; i < calendar.size(); i++) {
		getvect = calendar[i];
		for (int j = 0; j < getvect.size(); j++) {
			getcal = getvect[j];
			std::cout << getcal << ",";
		}
		std::cout << "\n";
	}
// End of Tesing


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