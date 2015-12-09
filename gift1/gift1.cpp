/*
ID: zpstudi1
PROG: gift1
LANG: C++11
*/

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG

using namespace std;

struct gift {
	string sender;
	int giftBalance;
	vector<string> recipitents;
};

struct member {
	string name;
	int currentBalance = 0;
};

typedef vector<string> slist;
typedef vector<member> group;

void log(string message);
void wait(void);
slist getFileLines(ifstream fin);
group getPeople(slist lines, int np);
int getPersonIndex(group people, string person);
vector<gift> getGifts(slist lines, int np);
vector<string> split(string &s, char delim);

int main()
{
	slist fileLines = getFileLines(ifstream("gift1.in"));
	ofstream fout("gift1.out");

	int np = atoi(fileLines[0].c_str()); // Line 1 = NP

	log("NP: " + to_string(np));
	log("Getting people...");
	wait();

	group people = getPeople(fileLines, np); // gets the NP people listed from lines 2 through NP + 1 in gift1.in

	log("Got people...");
	log("Getting gifts...");
	wait();

	vector<gift> gifts = getGifts(fileLines, np);

	log("Got gifts...");
	log("Calculating balances...");
	wait();

	for (int i = 0; i < gifts.size(); i++)
	{
		gift g = gifts[i];
		int recipentCount = g.recipitents.size();
		int receivedAmount = (g.giftBalance - (g.giftBalance % recipentCount)) / recipentCount;

		log("Calculating balance events caused by gift from: " + g.sender);
		wait();

		people[getPersonIndex(people, g.sender)].currentBalance -= receivedAmount * recipentCount;
		for (int i = 0; i < recipentCount; i++)
		{
			people[getPersonIndex(people, g.recipitents[i])].currentBalance += receivedAmount;
		}
	}

	log("Calculated balances...");
	log("Logging balances to gift1.out");
	wait();

	for (int i = 0; i < people.size(); i++)
	{
		member p = people[i];
		fout << p.name << " " << p.currentBalance << "\n";
	}

	log("Logged balances to gift1.out");
	wait();

    return 0;
}

int getPersonIndex(group people, string person)
{
	for (int i = 0; i < people.size(); i++)
	{
		if (people[i].name == person)
		{
			return i;
		}
	}
	return 0;
}

slist getFileLines(ifstream fin)
{
	slist lines;

	for (string line = ""; getline(fin, line);)
	{
		lines.push_back(line);
	}

	return lines;
}

group getPeople(slist lines, int np)
{
	group p;

	for (int i = 1; i < np + 1; i++) // Lines 2 .. NP + 1
	{
		member nperson;

		nperson.name = lines[i];

		p.push_back(nperson);
	}

	return p;
}

vector<gift> getGifts(slist lines, int np)
{
	vector<gift> gifts;

	for (int i = np + 1; i < lines.size();) // Lines NP + 2 .. end
	{
		gift g;
		
		g.sender = lines[i];

		vector<string> senderValues = split(lines[i + 1], ' ');

		if (senderValues[1] != "0")
		{
			g.giftBalance = atoi(senderValues[0].c_str());

			int recipitentCount = atoi(senderValues[1].c_str());

			for (int j = 0; j < recipitentCount; j++)
			{
				g.recipitents.push_back(lines[i + j + 2]);
			}

			gifts.push_back(g);

			i += recipitentCount;
		}

		i += 2;
	}

	return gifts;
}

vector<string> &split(string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


vector<string> split(string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
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
	cout << "Press enter to continue";
	cin.get();
#endif
}