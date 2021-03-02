#pragma once

#include "Revolver.h"
#include "Sniper.h"
#include "Sword.h"
#include "Weapon.h"

class WeaponFactory {
public:
	Weapon* makeWeapon(int weaponType) {
		Weapon* weapon = NULL;
		if (weaponType == 0)
			weapon = new Sword();
		else if (weaponType == 1)
			weapon = new Revolver();
		else
			weapon = new Sniper();
		return weapon;
	}
};
