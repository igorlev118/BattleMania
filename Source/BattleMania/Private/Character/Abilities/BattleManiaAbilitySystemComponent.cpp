#include "Character/Abilities/BattleManiaAbilitySystemComponent.h"

void UBattleManiaAbilitySystemComponent::ReceiveDamage(UBattleManiaAbilitySystemComponent * SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
