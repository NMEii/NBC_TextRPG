#include "pch.h"
#include "UseItem.h"
#include "Character.h"

void UseItem::Play(const ActionContext& context)
{
	if (!context.owner || !context.useItem)
		return;

	if (context.useItem->getCount() <= 0)
		return;

	if (context.useItem->getName() == "HP Potion")
	{
		context.owner->stats.currentHealth += 50;
		if (context.owner->stats.currentHealth > context.owner->stats.maxHealth)
			context.owner->stats.currentHealth = context.owner->stats.currentHealth;

	}
	
}
