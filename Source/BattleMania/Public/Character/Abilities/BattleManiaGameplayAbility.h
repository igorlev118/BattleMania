#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BattleMania.h"
#include "BattleManiaGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEMANIA_API UBattleManiaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UBattleManiaGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BattleMania Ability")
	EBattleManiaAbilityInputID AbilityInputID = EBattleManiaAbilityInputID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BattleMania Ability")
	EBattleManiaAbilityInputID AbilityID = EBattleManiaAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilites forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BattleMania Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
