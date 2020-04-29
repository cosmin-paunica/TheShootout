#include "Sword.h"

Sword::Sword() : Weapon(1, 2, "sword", "blade"), sharpnessPercentage(100) {
}

int Sword::getActualDamage() const {
	return (int)(damage * sharpnessPercentage / 100);
}

bool Sword::isUsable() const {
	if (sharpnessPercentage > 50)
		return true;
	return false;
}

void Sword::use() {
	if (sharpnessPercentage <= 50)
		throw "Sword is unusable";
	sharpnessPercentage -= 10;
}

void Sword::repair() {
	sharpnessPercentage = 100;
}
