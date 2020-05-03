#include "Game.h"

Game::Game(int noOfAgents, int mapSize = 25)
	: map(mapSize), mapSize(mapSize) {
	if (mapSize < 25)
		throw "Map should be at least 25x25";
	if (noOfAgents > mapSize * mapSize)
		throw "Too many agents for this map size";

	srand((int)time(NULL));

	for (int i = 0; i < noOfAgents; i++) {
		int row, col;
		do {
			row = rand() % mapSize;
			col = rand() % mapSize;
		} while (map[row][col] != NULL);
		createAgent(row, col);
	}
}

void Game::createAgent(int row, int col) {
	Agent* agent = new Agent(row, col);
	agents.push_back(agent);
	map[row][col] = agent;
}

void Game::runRound() {

	cout << "Agents in game: ";
	for (Agent* agent : agents)
		cout << agent->id << " ";
	cout << endl << endl;
	
	for (int k = 0; k < (int)agents.size(); k++) {
		// fiecare agent din joc face cate o actiune
		Agent* agent = agents[k];
		int row = agent->row;	// row-ul agentului curent
		int col = agent->col;	// col-ul agentului curent

		// Caz 1: daca arma nu e folosibila, agentul intotdeauna o repara
		if (!agent->weapon->isUsable()) {
			agent->weapon->repair();
			cout << "Agent " << agent->id << " repaired their weapon" << endl;
		}
		else {
			Agent* leastDangerous = NULL;	// cel mai nepericulos din raza de vizibilitate
			Agent* mostDangerous = NULL;	// cel mai periculos din raza armei
			float smallestPowerFactor = 10, greatestPowerFactor = 0;
			
			for (int i = max(0, row - VIS_RANGE); i <= min(mapSize - 1, row + VIS_RANGE); i++)
				for (int j = max(0, col - VIS_RANGE); j <= min(mapSize - 1, col + VIS_RANGE); j++)
					if (map[i][j] != agent && map[i][j] != NULL) {
						if (leastDangerous == NULL || smallestPowerFactor > map[i][j]->relativePowerFactor(*agent)) {
							leastDangerous = map[i][j];
							smallestPowerFactor = map[i][j]->relativePowerFactor(*agent);
						}
						
						if (map.areInRange(row, col, map[i][j]->row, map[i][j]->col, agent->weapon->getRange()))
							if (mostDangerous == NULL || greatestPowerFactor < map[i][j]->relativePowerFactor(*agent)) {
								mostDangerous = map[i][j];
								greatestPowerFactor = map[i][j]->relativePowerFactor(*agent);
							}
					}

			// Caz 2: daca exista un agent in raza de atac a armei
			if (mostDangerous != NULL) {
				cout << "Agent " << agent->id << " attacked agent " << mostDangerous->id << endl;
				agent->attack(*mostDangerous);
				if (mostDangerous->health == 0) {
					// daca mostDangerous a murit, il stergem din joc
					cout << "Agent " << mostDangerous->id << " died" << endl;
					for (int l = 0; l < (int)agents.size(); l++)
						if (agents[l] == mostDangerous) {
							agents.erase(agents.begin() + l);
							if (l < k)
								k--;
						}
					Agent* auxToBeDeleted = mostDangerous;
					map[mostDangerous->row][mostDangerous->col] = NULL;
					delete auxToBeDeleted;
				}
			}

			// Caz 3: daca exista agenti in raza de vizibilitate, dar nu in raza de atac a armei
			else if (leastDangerous != NULL) {
				string areaToMove = map.relativeArea(leastDangerous->row, leastDangerous->col, row, col);

				int distToMove = 0;
				if (areaToMove == "north")
					for (int k = row - 1; k >= 0 && map[k][col] == NULL && distToMove < MOVE_DIST
						&& !map.areInRange(row, col, leastDangerous->row, leastDangerous->col, agent->weapon->getRange()); k--)
						distToMove++;
				else if (areaToMove == "east")
					for (int k = col + 1; k < mapSize && map[row][k] == NULL && distToMove < MOVE_DIST
						&& !map.areInRange(row, col, leastDangerous->row, leastDangerous->col, agent->weapon->getRange()); k++)
						distToMove++;
				else if (areaToMove == "south")
					for (int k = row + 1; k < mapSize && map[k][col] == NULL && distToMove < MOVE_DIST
						&& !map.areInRange(row, col, leastDangerous->row, leastDangerous->col, agent->weapon->getRange()); k++)
						distToMove++;
				else if (areaToMove == "west")
					for (int k = col - 1; k >= 0 && map[row][k] == NULL && distToMove < MOVE_DIST
						&& !map.areInRange(row, col, leastDangerous->row, leastDangerous->col, agent->weapon->getRange()); k--)
						distToMove++;

				map.moveAgent(row, col, areaToMove, distToMove);
				cout << "Agent " << agent->id << " moved " << distToMove << " units "
					<< areaToMove << endl;
			}

			// Caz 4: daca nu au fost gasiti agenti de atacat
			else {
				string area = map.area(row, col, MOVE_DIST);
				if (area == "middle")
					cout << "Agent " << agent->id << " stayed in the middle";
				else {
					cout << "Agent " << agent->id << " moved " << MOVE_DIST << " units ";
					if (area == "north") {
						map.moveAgent(row, col, "south", MOVE_DIST);
						cout << "south";
					}
					else if (area == "east") {
						map.moveAgent(row, col, "west", MOVE_DIST);
						cout << "west";
					}
					else if (area == "south") {
						map.moveAgent(row, col, "north", MOVE_DIST);
						cout << "north";
					}
					else if (area == "west") {
						map.moveAgent(row, col, "east", col + MOVE_DIST);
						cout << "east";
					}
				}
				cout << endl;
			}
		}
	}

	cout << endl << map << endl << endl;
}

void Game::run() {
	cout << "Initial configuration of the game:" << endl << endl;
	for (Agent* agent : agents) {
		cout << "Agent " << agent->id << ": " << agent->weapon->getType() << ", "
			<< (agent->armor != NULL ? agent->armor->getType() : "no armor") << endl;
	}
	cout << endl << map << endl << endl;

	system("pause");
	cout << endl << endl;
	int cont, round = 0;
	do {
		cout << "Round " << ++round << endl << endl;
		runRound();
		do {
			cout << "Do you wish to run another round? [1 for yes, 0 for no]: ";
			cin >> cont;
			if (cont != 0 && cont != 1)
				cout << "Invalid command" << endl;
		} while (cont != 0 && cont != 1);
		cout << endl << endl;
	} while (cont == 1);

	cout << "End of game!" << endl << endl << "Stats:" << endl << endl;
	for (Agent* agent : agents) {
		cout << "Agent " << agent->id << ": " << agent->health << " health" << endl;
	}
}
