

#pragma once

#include "BattleMania.h"
#include "BattleManiaEnum.h"
#include "UObject/Interface.h"
#include "BattleManiaInterfaceABPIK.generated.h"


UINTERFACE(MinimalAPI)
class UBattleManiaInterfaceABPIK : public UInterface 
{

	GENERATED_BODY()
};


class BATTLEMANIA_API IBattleManiaInterfaceABPIK 
{

	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABPIK_Interface")
	void OnSetShowTraces(bool bShow);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABPIK_Interface")
	void OnSetIsRagdoll(bool bRagdoll);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABPIK_Interface")
	void OnSetStance(EStance NewStance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABPIK_Interface")
	void OnSetLocomotionMode(ELocomotionMode NewMode);
};
