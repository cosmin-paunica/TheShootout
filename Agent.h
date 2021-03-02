#pragma once

#include "Armor.h"
#include "ArmorFactory.h"
#include "BulletProofVest.h"
#include "Revolver.h"
#include "Sniper.h"
#include "Sword.h"
#include "TinChestplate.h"
#include "Weapon.h"
#include "WeaponFactory.h"
#include <algorithm>

using namespace std;

class Agent {
	float health;
	Weapon* weapon;
	Armor* armor;
	int id;
	int row, col;		// pozitia agentului
	static int count;	// pentru a genera id-uri unice

public:
	Agent(int, int);
	~Agent();
	int getId();
	void setRow(int);
	void setCol(int);

	// returneaza damage-ul pe care *this i l-ar da unui agent intr-un atac
	float relativePowerFactor(const Agent&) const;
	
	void attack(Agent&) const;

	friend class Game;
};
