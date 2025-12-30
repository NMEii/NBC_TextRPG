#include "pch.h"
#include "Status.h"


Status::Status(string name, int currenthealth, int maxhealth, int attack)
: Name(name), currentHealth(currenthealth), maxHealth(maxhealth), attack(attack)
{}