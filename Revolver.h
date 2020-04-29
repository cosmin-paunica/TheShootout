#pragma once

// Agentii care au revolver pot trage 5 gloante, dupa care trebuie sa il reincarce

#include "Weapon.h"

class Revolver : public Weapon {
	int currentNoOfBulltes, maxNoOfBullets;

public:
	Revolver();
	int getActualDamage() const;
	bool isUsable() const;

	// scade numarul de gloante din revolver
	void use();

	// incarca revolverul
	void repair();
};
