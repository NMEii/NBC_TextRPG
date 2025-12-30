#include "pch.h"
#include "Status.h"


Status::Status(string name, int level, int currenthealth, int maxhealth, int attack)
: Name(name), level(level), currentHealth(currenthealth), maxHealth(maxhealth), attack(attack)
{}