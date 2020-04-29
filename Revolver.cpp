#include "Revolver.h"

Revolver::Revolver() : Weapon(3, 4, "revolver", "none"), currentNoOfBulltes(5), maxNoOfBullets(5) {
}

int Revolver::getActualDamage() const {
	if (currentNoOfBulltes > 0)
		return damage;
	return 0;
}

bool Revolver::isUsable() const {
	if (currentNoOfBulltes > 0)
		return true;
	return false;
}

void Revolver::use() {
	if (currentNoOfBulltes <= 0)
		throw "Revolver is unusable";
	currentNoOfBulltes -= 1;
}

void Revolver::repair() {
	currentNoOfBulltes = maxNoOfBullets;
}
