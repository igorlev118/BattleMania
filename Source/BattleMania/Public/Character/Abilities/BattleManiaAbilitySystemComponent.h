// Copyright 2020 Igor Levdansky.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BattleManiaAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UBattleManiaAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);


UCLASS()
class BATTLEMANIA_API UBattleManiaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(UBattleManiaAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
