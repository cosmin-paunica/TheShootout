#include "Weapon.h"

Weapon::Weapon(int range, int damage, string type, string ammoType)
	: range(range), damage(damage), type(type), ammoType(ammoType) {
}

int Weapon::getRange() const {
	return range;
}

string Weapon::getType() {
	return type;
}

string Weapon::getAmmoType() const {
	return ammoType;
}
