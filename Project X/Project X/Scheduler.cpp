#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <nlohmann/json.hpp>
#include "Classes.h"

using std::string;
using json = nlohmann::json;

int main() {
	int jsize, i;
	json j, jread;
	string* jobj;

	// Reading JSON
	std::ifstream jfile("User.json");
	jfile >> jread;
	

	jsize = jread.size();

	Employee* emp;
	Calendar* cal;
	emp = new Employee[jsize];

	// set employee attributes
	for (i = 0; i < jsize; i++) {
		emp[i].setName(jread[i]["Name"].get<string>());
		emp[i].setLicense(jread[i]["License"].get<string>());
		emp[i].setHours(jread[i]["Hours"].get<int>());
		emp[i].setScheduleType(jread[i]["Schedule Type"].get<string>());
	}

	// enter into csv
	CSV mycsv;
	mycsv.sendNames("CSV_test.csv", emp, jsize);

	
	for (i = 0; i < jsize; i++) {
		std::cout << emp[i].getName() << std::endl;
		std::cout << emp[i].getLicense() << std::endl;
		std::cout << emp[i].getHours() << std::endl;
		std::cout << emp[i].getScheduleType() << std::endl;
	}

	//std::cout << emp << std::endl;



	


	// allocate memory for jobj
	//jobj = new string[jsize];
    /*
	//string jobj;
	std::cout << jsize << std::endl;
	// get names
	for (int j = 0; j < jsize; j++) {
		// create an array of objects from JSON
		jobj[j] = jread[j].dump(4); // employee 1 name
	}
	// for loop for print
	std::cout << jobj[0] << std::endl; // function
	/*
	1. JSON objects to Class objects
	2. start scheduling
	
	
    */
	//delete[] emp;
	return 0;
}