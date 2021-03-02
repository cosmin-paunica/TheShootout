#pragma once

#include "Armor.h"
#include "BulletProofVest.h"
#include "TinChestplate.h"

class ArmorFactory {
public:
	Armor* makeArmor(int armorType) {
		Armor* armor = NULL;
		if (armorType == 0)
			armor = new BulletProofVest();
		else if (armorType  == 1)
			armor = new TinChestplate();
		return armor;
	}
};
