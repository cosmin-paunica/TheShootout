#pragma once

// Agentii care au sniper pot trage doar cand au arma incarcata
// De fiecare data cand trag un glont, arma se descarca

#include "Weapon.h"

class Sniper : public Weapon {
	bool isLoaded;

public:
	Sniper();
	int getActualDamage() const;
	bool isUsable() const;

	// descarca sniper-ul
	void use();

	// incarca sniper-ul
	void repair();
};
