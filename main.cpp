#include "Game.h"
#include <iostream>

using namespace std;

int main() {
	int noOfAgents;
	do {
		cout << "Enter the number of agents:" << endl;
		cin >> noOfAgents;
		if (noOfAgents < 1)
			cout << "The number of agents must be positive." << endl;
	} while (noOfAgents < 1);

	int mapSize;
	do {
		cout << "Enter the size of the map (at least 25):" << endl;
		cin >> mapSize;
		if (mapSize < 25)
			cout << "The size of the map must be at least 25." << endl;
	} while (mapSize < 25);

	cout << endl << endl;

	Game game(noOfAgents, mapSize);
	game.run();

	return 0;
}
