

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <ConstructorHelpers.h>
#include "PlayerInfoWidget.generated.h"

class UVerticalBox;


UCLASS()
class BATTLEMANIA_API UPlayerInfoWidget : public UUserWidget 
{

	GENERATED_BODY()
	
public:
	UPlayerInfoWidget(const FObjectInitializer& ObjectInitializer);

	void SetPlayerInfo(const TArray<FString>& InfoStrings);

	void AddPlayerInfo(const TArray<FString>& InfoStrings);

	void SetColor(FColor Color);

	void SetFontSize(int32 FontSize);

protected:
	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerInfo;
	
	int32 FontSize = 14;
	
	FColor Color = FColor::White;
};
