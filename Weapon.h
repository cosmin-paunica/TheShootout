#pragma once

#include <string>

using namespace std;

class Weapon {
protected:
	int range, damage;
	string type, ammoType;

public:
	Weapon(int, int, string, string);
	virtual ~Weapon() {};
	int getRange() const;
	string getType();
	string getAmmoType() const;

	// returneaza damage-ul dat de arma, luand in considerare uzura
	virtual int getActualDamage() const = 0;
	virtual bool isUsable() const = 0;

	// aplica uzura armei
	virtual void use() = 0;
	
	// make weapon great again
	virtual void repair() = 0;
};
