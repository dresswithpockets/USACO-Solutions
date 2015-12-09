/*
ID: zpstudi1
PROG: friday
LANG: C++11
*/

//#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define DEBUG

using namespace std;

struct date
{
	int day, month, year;
};

void log(string message);
void wait(void);
vector<string> getFileLines(ifstream fin);
int getMonthLength(int month, int year);
int getDayOfWeek(int daysSinceDayZero);
bool isLeapYear(int year);

int main()
{
	int daysSinceDayZero = 1;

	date d;
	d.day = 1;
	d.month = 1;
	d.year = 1900;

	int startingYear = d.year;

	int n = atoi(getFileLines(ifstream("friday.in"))[0].c_str());
	ofstream fout("friday.out");

	vector<int> thirteenths;
	for (int i = 0; i < 7; i++)
	{
		thirteenths.push_back(0);
	}

	for (int i = d.year; d.year < (startingYear + n); d.year++) // Start the year cycle at d.year (1900 by default)
	{
		log("year: " + to_string(d.year) + "\n");
		wait();
		for (int j = d.month; d.month < 13; d.month++) // 12 months
		{
			log("month: " + to_string(d.month) + "\n");
			wait();
			int monthLength = getMonthLength(d.month, d.year);
			for (int k = d.day; d.day < monthLength + 1; d.day++)
			{
				if (d.day == 13)
				{
					log("DAY IS A 13TH, day of week: " + to_string(getDayOfWeek(daysSinceDayZero)));
					wait();
					thirteenths[getDayOfWeek(daysSinceDayZero)]++;
				}
				else
				{
					//log("day: " + to_string(d.day));
				}
				
				daysSinceDayZero++;
			}

			d.day = 1;
		}

		d.month = 1;
	}

	for (int i = 0; i < thirteenths.size(); i++)
	{
		fout << thirteenths[i];
		if (i < (thirteenths.size() - 1))
		{
			fout << " ";
		}
	}
	fout << "\n";

    return 0;
}

vector<string> getFileLines(ifstream fin)
{
	vector<string> lines;

	for (string line = ""; getline(fin, line);)
	{
		lines.push_back(line);
	}

	return lines;
}

int getMonthLength(int month, int year)
{
	switch (month)
	{
	case 2:
		if (isLeapYear(year))
		{
			return 29;
		}
		return 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}

int getDayOfWeek(int daysSinceDayZero) // Sunday is 1 as day zero is a saturday.
{
	return (daysSinceDayZero + 1) % 7;
}

/*
Every year evenly divisible by 4 is a leap year (1992 = 4*498 so 1992 will be a leap year, but the year 1990 is not a leap year)
The rule above does not hold for century years. Century years divisible by 400 are leap years, all other are not.
Thus, the century years 1700, 1800, 1900 and 2100 are not leap years, but 2000 is a leap year.
*/
bool isLeapYear(int year)
{
	return ((year % 100 == 0) && (year % 400 == 0)) ||
		((year % 100 != 0) && (year % 4 == 0));
}

void log(string message)
{
#ifdef DEBUG
	cout << message << endl;
#endif
}

void wait(void)
{
#ifdef DEBUG
	cout << "Press enter to continue\n";
	cin.get();
#endif
}