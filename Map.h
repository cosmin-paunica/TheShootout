#pragma once

#include "Agent.h"
#include <iostream>
#include <vector>

using namespace std;

// harta de dimensiune size*size
class Map {
	int size;
	vector<vector<Agent*>> agentsMatrix;

public:
	Map(int);
	~Map();

	// returneaza coordonata aflata la mijlocul hartii
	int middle() const;
	
	// returneaza zona in care se afla o pereche de coordonate
	// al treilea parametru este folosit pentru a determina marimea zonei de mijloc
	string area(int, int, int) const;

	// returneaza zona in care se afla prima pereche de coordonate fata de a doua
	string relativeArea(int, int, int, int) const;

	// muta un agent de pe o pozitie pe alta
	void moveAgent(int, int, int, int);

	// muta un agent de pe o pozitie, intr-o directie, cu un anumit numar de pozitii
	void moveAgent(int, int, string, int);

	vector<Agent*>& operator[](int);
	friend ostream& operator<<(ostream&, const Map&);
};
