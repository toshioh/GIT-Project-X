#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <string>
#include <set>
#include <ctime>
#include <vector>

#ifndef CLINIC_H
#define CLINIC_H

#include <string>
#include <array>

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

#endif