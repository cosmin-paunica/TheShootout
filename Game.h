// In cadrul fiecarei runde, fiecare agent poate face 4 lucruri:
// Cazul 1: daca arma sa nu este utilizabila, agentul o repara.
// Cazul 2: altfel, daca acesta are cel putin un agent in raza armei sale,
// il ataca pe cel mai periculos dintre ei.
// Cazul 3: altfel, daca are cel putin un agent in raza sa de vizibilitate,
// dar in afara razei armei sale, el se se apropie de cel mai nepericulos
// dintre ei pana cand acesta ii intra in raza.
// Cazul 4: altfel, el se deplaseaza spre centrul arenei (sau ramane pe loc
// daca deja se afla in zona de centru).

#pragma once

#include "Agent.h"
#include "Map.h"
#include <algorithm>
#include <ctime>
#include <exception>
#include <iostream>

using namespace std;

class Game {
	static Game* instance;
	Game();

	Map* map;
	int mapSize;
	vector<Agent*> agents;

	void createAgent(int, int);
	void init(int, int);

	const int VIS_RANGE = 4;	// raza de vizibilitate a agentilor
	const int MOVE_DIST = 2;	// distanta la care se pot misca agentii

public:
	static Game* getInstance();

	// gestioneaza rularea unei singure runde
	void runRound();

	// afiseaza starea initiala si gestioneaza rularea mai multor runde,
	// in functie de inputul utilizatorului
	void run(int, int);
};
