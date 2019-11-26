#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "MapIconWidget.generated.h"

class UImage;
class UThrobber;
class UMapWidget;


/**
 * Implements widget for icon display on map  
 */
UCLASS(Category = "MiniMap")
class MINIMAPMODULE_API UMapIconWidget : public UUserWidget 
{

	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void Setup(const FColor& IconTint, UTexture2D* IconImage, UMapWidget* InMap, AActor* InActor, bool bAlwaysShow);

protected:
	virtual bool Initialize() override;

private:
	/** Determines if icon disappears when off map */
	UPROPERTY()
	bool bAlwaysRelevant = true;

	UPROPERTY()
	UWidget* CurrentIcon;

	UPROPERTY(meta = (BindWidget))
	UThrobber* DefaultIcon = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* CustomIcon = nullptr;

	UPROPERTY()
	AActor* MyActor = nullptr;

	UPROPERTY()
	UMapWidget* MyMap = nullptr;
};

