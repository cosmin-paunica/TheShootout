#pragma once

// Agentii care au sword o pot folosi oricand,
// doar ca damage-ul ei scade pe masura ce o folosesc
// Damage-ul poate scadea pana la 50, cand arma nu mai e folosibila

#include "Weapon.h"

class Sword : public Weapon {
	int sharpnessPercentage;

public:
	Sword();
	int getActualDamage() const;
	bool isUsable() const;

	// scade sharpnessPercentage-ul cu 10
	void use();

	// ascute arma, iar sharpnessPercentage revine la 100
	void repair();
};
