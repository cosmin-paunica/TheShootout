#include "Armor.h"

Armor::Armor(float protection, string type, string weakenedAmmoType)
	: protection(protection), type(type), weakenedAmmoType(weakenedAmmoType) {
}

float Armor::getProtection() const {
	return protection;
}

string Armor::getType() const {
	return type;
}

string Armor::getWeakenedAmmoType() const {
	return weakenedAmmoType;
}
