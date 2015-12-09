/*
ID: zpstudi1
PROG: ride
LANG: C++11
*/

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getPhrasePower(string phrase);
int getLetterIndex(char letter);

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int powerMod = 47;

int main()
{
	ofstream fout("ride.out");
	ifstream fin("ride.in");

	string line1 = "";
	getline(fin, line1);
	
	string line2 = "";
	getline(fin, line2);

	if (getPhrasePower(line1) % powerMod == getPhrasePower(line2) % powerMod)
	{
		fout << "GO\n";
	}
	else
	{
		fout << "STAY\n";
	}

    return 0;
}

int getPhrasePower(string phrase)
{
	int power = 1;
	for (unsigned int i = 0; i < phrase.length(); i++)
	{
		power *= (getLetterIndex(phrase[i]) + 1);
	}
	return power;
}

int getLetterIndex(char letter)
{
	for (unsigned int i = 0; i < letters.length(); i++)
	{
		if (letters[i] == toupper(letter))
		{
			return i;
		}
	}

	return 0;
}