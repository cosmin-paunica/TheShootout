#include "Map.h"

Map::Map(int size) : size(size) {
	for (int i = 0; i < size; i++) {
		vector<Agent*> row;
		for (int j = 0; j < size; j++)
			row.push_back(NULL);
		agentsMatrix.push_back(row);
	}
}

Map::~Map() {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (agentsMatrix[i][j] != NULL)
				delete agentsMatrix[i][j];
}

int Map::middle() const {
	return size / 2;
}

string Map::area(int row, int col, int middleSquareRadius) const {
	if (middle() - middleSquareRadius <= row && row <= middle() + middleSquareRadius
		&& middle() - middleSquareRadius <= col && col <= middle() + middleSquareRadius)
		return "middle";
	if (row < col && row + col < size)
		return "north";
	if (row + col >= size && row <= col)
		return "east";
	if (row > col && row + col >= size - 1)
		return "south";
	return "west";
}

string Map::relativeArea(int rowAg1, int colAg1, int rowAg2, int colAg2) const {
	int row = (int)rowAg1 - ((int)(rowAg2) - (int)middle());
	int col = (int)colAg1 - ((int)(colAg2)-(int)middle());

	return area(row, col, 0);
}

void Map::moveAgent(int row, int col, int newRow, int newCol) {
	if (newRow < 0 || newRow >= size || newCol < 0 || newCol >= size)
		throw "Index out of range";
	if (agentsMatrix[row][col] == NULL)
		throw "Agent doesn't exist";
	if (agentsMatrix[newRow][newCol] != NULL)
		throw "Position is occupied";

	agentsMatrix[newRow][newCol] = agentsMatrix[row][col];
	agentsMatrix[row][col] = NULL;
	agentsMatrix[newRow][newCol]->setRow(newRow);
	agentsMatrix[newRow][newCol]->setCol(newCol);
}

void Map::moveAgent(int row, int col, string direction, int distance) {
	int newRow = row, newCol = col;
	if (direction == "north")
		newRow -= distance;
	else if (direction == "east")
		newCol += distance;
	else if (direction == "south")
		newRow += distance;
	else if (direction == "west")
		newCol -= distance;

	moveAgent(row, col, newRow, newCol);
}

vector<Agent*>& Map::operator[](int row) {
	return agentsMatrix[row];
}

ostream& operator<<(ostream& out, const Map& map) {
	out << " -";
	for (int j = 0; j < 3 * map.size; j++)
		out << "-";
	out << " " << endl;

	for (int i = 0; i < map.size; i++) {
		out << "| ";
		for (int j = 0; j < map.size; j++)
			if (map.agentsMatrix[i][j] == NULL)
				out << "   ";
			else
				if (map.agentsMatrix[i][j]->getId() < 10)
					out << " " << map.agentsMatrix[i][j]->getId() << " ";
				else if (map.agentsMatrix[i][j]->getId() < 100)
					out << map.agentsMatrix[i][j]->getId() << " ";
				else
					out << map.agentsMatrix[i][j]->getId();
		out << "|" << endl;
	}

	out << " -";
	for (int j = 0; j < 3 * map.size; j++)
		out << "-";
	out << " ";
	return out;
}
