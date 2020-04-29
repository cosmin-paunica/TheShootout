#pragma once

#include <string>
#include <vector>

using namespace std;

class Armor {
	float protection;
	string type;

	// tipul de munitie pe care e specializata armura
	string weakenedAmmoType;

public:
	Armor(float, string, string);
	float getProtection() const;
	string getType() const;
	string getWeakenedAmmoType() const;
};
