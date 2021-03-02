#include "Game.h"
#include <iostream>

using namespace std;

int main() {
	cout << "-----THE SHOOTOUT-----\n\n";

	int noOfAgents;
	do {
		cout << "Enter the number of agents:\n";
		cin >> noOfAgents;
		if (noOfAgents < 1)
			cout << "The number of agents must be positive.\n";
	} while (noOfAgents < 1);

	int mapSize;
	do {
		cout << "Enter the size of the map (at least 25):\n";
		cin >> mapSize;
		if (mapSize < 25)
			cout << "The size of the map must be at least 25.\n";
		else if (mapSize * mapSize < noOfAgents)
			cout << "The size of the map is not big enough for the number of agents chosen.\n";
	} while (mapSize < 25 || mapSize * mapSize < noOfAgents);

	cout << "\n\n";

	Game* game = Game::getInstance();
	game->run(noOfAgents, mapSize);

	return 0;
}
