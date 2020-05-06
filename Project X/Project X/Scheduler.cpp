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

vector<Employee> initEmployee(json jread) {
	std::vector<Employee> emp;
	Employee newemp;

	int jsize = jread.size();
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
			employees[i].setPrefAge("null");
	}
}


vector<string> scheduleDates(Calendar c)
{
	string dayname;
	int month, year, daynum;
	string date, monthname;

	int numOfDays = c.getnumOfDays();
	//std::cout << numOfDays << std::endl;
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


// Making edges of csv
vector<vector<string>> createCalendar(vector<string> dates, vector<Employee> emp) {
	vector<vector<string>> calendar;
	vector<string> row;
	string empName;
	string date;
	//std::cout << "date: " << dates.size() << std::endl;;
	for (int i = 0; i < dates.size(); i++) {
		row = {};
		for (int j = 0; j <= emp.size(); j++) {
			if (i == 0) {
				if (j == 0) {
					row.push_back("-X-");
				}
				else {
					// Make name row
					int empi = j - 1;
					empName = emp[empi].getName();
					row.push_back(empName);
				}
			}
			else {
				if (j == 0) {
					date = dates[i];
					row.push_back(date);
				}
				else {
					row.push_back(" ");
				}
			}
		}
		calendar.push_back(row);
	}
	return calendar;
}


// fill csv
vector<vector<string>> fillCalendar(vector<vector<string>> cal,vector<Employee> emp, vector<Clinic> cln, json jread) {
	string currDay, currDate, empName, currentEmpRole,clinicName = "";
	vector<string> minStaff;
	int empCount, empMax, empIdeal;
	int qindex;
	int currentEmpInd;
	vector<string>::iterator it;
	
	int nameIndex;
	int clinicIndex;
	int csize = cln.size();
	int empSize = emp.size();
	bool areMoreEmpAvailable = true;
	bool areMoreClinicsAvailable = true;

	for (int i = 1; i < cal.size(); i++) { // Rows
		currDate = cal[i][0];
		currDay = currDate.substr(0, 3);
		
			if (currDay != "Sun" && currDay != "Sat") { // checks if it's the weekend
				removeAvailable(emp,currDay);
				areMoreEmpAvailable = true;
				areMoreClinicsAvailable = true;
				while (areMoreEmpAvailable)
				{
					for (int j = 0; j < emp.size(); j++) // checks if more employees to schedule
					{
						currentEmpRole = emp[j].getPrefAge();
						empName = emp[j].getName();
						currentEmpInd = j;
						if (currentEmpRole != "null")
						{
							j = emp.size();
							areMoreEmpAvailable = true;
						}
						else if(j==emp.size())
						{
							areMoreEmpAvailable = false;
						}

					}
					if (areMoreEmpAvailable && !areMoreClinicsAvailable)
					{
						int numOfFullClinics = 0;
						it = find(cal[0].begin(), cal[0].end(), empName);
						nameIndex = it - cal[0].begin();

						for (int c = 0; c < csize; c++) {
							empCount = cln[c].getCurrentEmps();
							empMax = cln[c].getMax();
							if (empCount < empMax)
							{
								emp[currentEmpInd].setPrefAge("null");

								clinicName = cln[c].getName();
								cal[i][nameIndex] = clinicName;
								empCount = cln[c].getCurrentEmps() + 1;
								cln[c].setCurrentEmps(empCount);
								
								c = csize;
							}
							else
							{
								numOfFullClinics++;
							}
							if (numOfFullClinics == csize)
							{
								emp[currentEmpInd].setPrefAge("null");
								areMoreEmpAvailable = false;
							}
						}
					}
					else
					{
						while (areMoreClinicsAvailable)
						{
							for (int p = 0; p < csize; p++)
							{
								vector<string> availableClinic = cln[p].getMinStaff();
								if (!availableClinic.empty())
								{
									p = csize;
									areMoreClinicsAvailable = true;
								}
								else
								{
									areMoreClinicsAvailable = false;
								}
							}
							for (int k = 0; k < csize; k++) { //Fill all clinics min requirements
								minStaff = cln[k].getMinStaff();
								while (!minStaff.empty())
								{
									clinicName = cln[k].getName();

									int minStaffSize = minStaff.size() - 1;
									string neededRole = minStaff[minStaffSize];
									qindex = findQualifiedEmpIndex(emp, neededRole, empSize);
									empName = emp[qindex].getName();
									it = find(cal[0].begin(), cal[0].end(), empName);
									nameIndex = it - cal[0].begin();
									cal[i][nameIndex] = clinicName;
									minStaff.pop_back();
									empCount = cln[k].getCurrentEmps() + 1;
									cln[k].setCurrentEmps(empCount);
									emp[qindex].setPrefAge("null");
								}
								cln[k].setMinStaff({});

							}
						}
					}
				}
			}
			emp = initEmployee(jread);
			cln = initClinics();		
	}
	return cal;
}


void printCSV(vector<vector<string>> calendar) {
	
	int rowsize = calendar.size();
	int colsize = calendar[0].size();

	std::ofstream myfile;
	myfile.open("CSV_test.csv");

	for (int i = 0; i < rowsize; i++) {
		for (int j = 0; j < colsize; j++) {
			myfile << calendar[i][j];
			myfile << ",";
		}
		myfile << "\n";
	}
	myfile.close();
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
	//jsize = jread.size();
	
	// Read into Employee vector of size jsize
	enew = initEmployee(jread);
	clinic = initClinics();


// 1. Testing schedule Dates
	//std::cout << "Schedule test: " << std::endl;
	vector<string> dates;
	dates = scheduleDates(cal);
	/*
	std::cout << dates.size() << std::endl;
	string currentDay;
	for (int k = 0; k < dates.size(); k++) {
		currentDay = dates[k];
		std::cout << currentDay << std::endl;
	}
	*/
// End of Tesing

// 2. Testing Calendar make:
	//std::cout << "Calendar row test: " << std::endl;
	vector<vector<string>> calendar;
	//vector<string> getvect;
	//string getcal;
	calendar = createCalendar(dates, enew);
	/*
	for (i = 0; i < calendar.size(); i++) {
		for (int j = 0; j < calendar[i].size(); j++) {
			std::cout << calendar[i][j] << "  ";
		}
		std::cout << "\n";
	}
	*/
// End of Tesing

// 3. Fill calendar
	vector<vector<string>> fullCalendar;
	fullCalendar = fillCalendar(calendar,enew,clinic,jread);
	/*
	for (i = 0; i < fullCalendar.size(); i++) {
		for (int j = 0; j < fullCalendar[i].size(); j++) {
			std::cout << fullCalendar[i][j] << "  ";
		}
		std::cout << "\n";
	}
	*/
// End fill

// 4. create csv
	printCSV(fullCalendar);


// Testing revmoveAvailable
	/*
	removeAvailable(enew, "Tue");
	std::cout << "Removeable age test: " << std::endl;
	std::cout << enew[0].getPrefAge() << std::endl;
	std::cout << enew[1].getPrefAge() << std::endl;
	std::cout << enew[2].getPrefAge() << std::endl;
	std::cout << enew[3].getPrefAge() << std::endl;
	*/
// End of Tesing
/*
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
*/
	//delete[] emp;
	return 0;
}