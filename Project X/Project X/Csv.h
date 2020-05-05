#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <string>
#include <set>
#include <ctime>
#include <vector>

#ifndef CSV_H
#define CSV_H

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