#include "pch.h"
#include "Action.h"

Action::Action(Character* owner) : owner(owner) {}
Action::~Action() = default;