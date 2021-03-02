#include "Agent.h"

int Agent::count = 0;

Agent::Agent(int row, int col) : row(row), col(col), health(10), id(++count) {
	WeaponFactory wpFact;
	int weaponType = rand() % 3;
	weapon = wpFact.makeWeapon(weaponType);

	ArmorFactory armFact;
	int armorType = rand() % 3;
	armor = armFact.makeArmor(armorType);
}

Agent::~Agent() {
	delete weapon;
	if (armor != NULL)
		delete armor;
}

int Agent::getId() {
	return id;
}

void Agent::setRow(int row) {
	this->row = row;
}

void Agent::setCol(int col) {
	this->col = col;
}

float Agent::relativePowerFactor(const Agent& agent) const {
	float powerFactor = (float)weapon->getActualDamage();
	if (agent.armor != NULL)
		if (agent.armor->getWeakenedAmmoType() == weapon->getType())
			powerFactor *= (1 - 2 * agent.armor->getProtection());
		else
			powerFactor *= (1 - agent.armor->getProtection());
	return powerFactor;
}

void Agent::attack(Agent& agent) const {
	if (!weapon->isUsable())
		throw "Agent's weapon is unusable";

	// calculam damage-ul pe care agent il primeste de la *this
	float healthLost = relativePowerFactor(agent);
	agent.health = max(0.0f, agent.health - healthLost);

	weapon->use();
}
