

#pragma once

#include "CoreMinimal.h"


#define PrintScreen(x, t, c) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, t, c, x, false)

/** Enumeration to string */
template<typename TEnum>
static FORCEINLINE FString Enum2Str(const FString& Name, TEnum Value) {
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!enumPtr) { 
		return FString("Invalid"); 
	}
	FString NameString = enumPtr->GetNameStringByValue((int64)Value);
	NameString.RemoveFromStart("e");
	return NameString;
}

UENUM(BlueprintType)
enum class EBattleManiaAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 3 LMB
	Ability1		UMETA(DisplayName = "Ability1"),
	// 4 RMB
	Ability2		UMETA(DisplayName = "Ability2"),
	// 5 Q
	Ability3		UMETA(DisplayName = "Ability3"),
	// 6 E
	Ability4		UMETA(DisplayName = "Ability4"),
	// 7 R
	Ability5		UMETA(DisplayName = "Ability5"),
	// 8 Sprint
	Sprint			UMETA(DisplayName = "Sprint"),
	// 9 Jump
	Jump			UMETA(DisplayName = "Jump")
};