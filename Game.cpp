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
		int row = agent->row;
		int col = agent->col;

		// Caz 1: daca arma nu e folosibila, agentul intotdeauna o repara
		if (!agent->weapon->isUsable()) {
			agent->weapon->repair();
			cout << "Agent " << agent->id << " repaired their weapon" << endl;
		}
		else {
			//bool attacked = false;
			//for (unsigned row = max(0, (int)(agents[i]->getRow() - VIS_RANGE)); !attacked && row <= min(mapSize - 1, agents[i]->getRow() + VIS_RANGE); row++)
			//	for (unsigned col = max(0, (int)(agents[i]->getCol() - VIS_RANGE)); !attacked && col <= min(mapSize - 1, agents[i]->getCol() + VIS_RANGE); col++)
			//		if (agents[i] != map[row][col] && map[row][col] != NULL) {
			//			attacked = true;
			//			cout << "Agent " << agents[i]->getId() << " attacked agent " << map[row][col]->getId() << endl;
			//			agents[i]->attack(*map[row][col]);

			//			if (map[row][col]->getHealth() == 0) {
			//				cout << "Agent " << map[row][col]->getId() << " died" << endl;
			//				for (unsigned j = 0; j < agents.size(); j++)
			//					if (agents[j] == map[row][col]) {
			//						agents.erase(agents.begin() + j);
			//						if (j < i)
			//							i--;	// daca agentul care a murit era pozitionat in vector inaintea celui care a atacat
			//					}
			//				delete map[row][col];
			//				map[row][col] = NULL;
			//			}
			//		}

			// leastDangerous = cel mai nepericulos din raza de vedere
			// mostDangerous = cel mai periculos din raza armei
			Agent* leastDangerous = NULL, * mostDangerous = NULL;
			float smallestPowerFactor = 10, greatestPowerFactor = 0;
			
			for (int i = max(0, row - VIS_RANGE); i <= min(mapSize - 1, row + VIS_RANGE); i++)
				for (int j = max(0, col - VIS_RANGE); j <= min(mapSize - 1, col + VIS_RANGE); j++)
					if (map[i][j] != agent && map[i][j] != NULL) {
						if (leastDangerous == NULL || smallestPowerFactor > map[i][j]->relativePowerFactor(*agent)) {
							leastDangerous = map[i][j];
							smallestPowerFactor = map[i][j]->relativePowerFactor(*agent);
						}
						if (map[i][j]->isInRange(*agent, agent->weapon->getRange()))
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
				string relativeArea = map.relativeArea(leastDangerous->row, leastDangerous->col, row, col);

				int distToMove = 0;
				if (relativeArea == "north")
					for (int k = row - 1; k >= 0 && map[k][col] == NULL
						&& distToMove < MOVE_DIST && !leastDangerous->isInRange(*agent, agent->weapon->getRange()); k--)
						distToMove++;
				else if (relativeArea == "east")
					for (int k = col + 1; k < mapSize && map[row][k] == NULL
						&& distToMove < MOVE_DIST && !leastDangerous->isInRange(*agent, agent->weapon->getRange()); k++)
						distToMove++;
				else if (relativeArea == "south")
					for (int k = row + 1; k < mapSize && map[k][col] == NULL
						&& distToMove < MOVE_DIST && !leastDangerous->isInRange(*agent, agent->weapon->getRange()); k++)
						distToMove++;
				else if (relativeArea == "west")
					for (int k = col - 1; k >= 0 && map[row][k] == NULL
						&& distToMove < MOVE_DIST && !leastDangerous->isInRange(*agent, agent->weapon->getRange()); k--)
						distToMove++;

				map.moveAgent(row, col, relativeArea, distToMove);
				cout << "Agent " << agent->id << " moved " << distToMove << " units "
					<< relativeArea << endl;
			}

			// Caz 4: daca nu au fost gasiti agenti de atacat
			else {
				string area = map.area(row, col, MOVE_DIST);
				if (area == "middle")
					cout << "Agent " << agent->id << " stayed in the middle";
				else {
					cout << "Agent " << agent->id << " moved " << MOVE_DIST << " units ";
					if (area == "north") {
						map.moveAgent(row, col, row + MOVE_DIST, col);
						cout << "south";
					}
					else if (area == "east") {
						map.moveAgent(row, col, row, col - MOVE_DIST);
						cout << "west";
					}
					else if (area == "south") {
						map.moveAgent(row, col, row - MOVE_DIST, col);
						cout << "north";
					}
					else if (area == "west") {
						map.moveAgent(row, agent->col, row, col + MOVE_DIST);
						cout << "east";
					}
				}
				cout << endl;
			}
		}
	}

	cout << endl << map << endl << endl;
}

void Game::start() {
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
		cout << "Do you wish to run another round? [1 for yes, 0 for no]: ";
		cin >> cont;
		cout << endl << endl;
	} while (cont == 1);
}
