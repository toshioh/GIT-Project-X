

void CSV::setRows(int rows) {
	rows_ = rows;
}

void CSV::setCols(int cols) {
	cols_ = cols;
}

int CSV::getRows() {
	return rows_;
}

int CSV::getCols() {
	return cols_;
}

void CSV::sendNames(string filename, Employee* names, int size) {
	fstream myFileout;
	myFileout.open(filename, ios::out | ios::app);
	
	int i;
	for (i = 0; i < size; i++) {
		if (i == 0) {
			myFileout << "Scheduler" << "," << names[i].getName() << ",";
		}
		else {
			myFileout << names[i].getName() << ",";
		}
	}
	myFileout.close();
}

void CSV::sendDates(string filename, Calendar c, int numofdays) {
	string dayname;
	int month, year, daynum;
	string date, monthname;
	fstream myFileout;

	myFileout.open(filename,ios::out | ios::app);
	
	int i;
	for (i = 0; i <= numofdays; i++) {
		if (i == 0) {
			myFileout << "\n";
		}
		else {
			month = c.getMonthNum();
			year = c.getYearNum();
			c.setDayName(c.dayNumber(i,month,year));
			monthname = c.getMonthName(month);

			date = c.getDayName() + " " + to_string(i) + "-" + monthname + "-" + to_string(year);
			myFileout << date << "\n";
		}
	}	
	myFileout.close();
}