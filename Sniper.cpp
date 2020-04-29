#include "Sniper.h"

Sniper::Sniper() : Weapon(5, 7, "sniper", "bullet"), isLoaded(true) {
}

int Sniper::getActualDamage() const {
	if (isLoaded)
		return damage;
	return 0;
}

bool Sniper::isUsable() const {
	return isLoaded;
}

void Sniper::use() {
	isLoaded = false;
}

void Sniper::repair() {
	isLoaded = true;
}
