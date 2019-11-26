#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "MapWidget.generated.h"

class UImage;
class UOverlay;
class UPointOfInterest;


UCLASS( ClassGroup = (MiniMap) )
class MINIMAPMODULE_API UMapWidget : public UUserWidget 
{

	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	virtual bool Initialize() override;

public:
	UPROPERTY(EditAnywhere, Category = "Map Display")
	UTexture* MapImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Display")
	float Dimensions = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Display")
	float HalfSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Display")
	float Zoom = 0.5;

	/** Convert world position to map coordinates */
	UFUNCTION(BlueprintCallable)
	bool GetMapLocation(const FVector& WorldLocation, FVector2D& MapLocation);

	UFUNCTION(BlueprintCallable)
	void AddPointOfInterest(UPointOfInterest* POI);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Display")
	bool IsRound = false;

	UPROPERTY(meta = (BindWidget))
	UOverlay* MapOverlay = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* SquareMap = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* SquareMapMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player Display")
	FColor PlayerIconTint = FColor::White;

	UPROPERTY(EditAnywhere, Category = "Player Display")
	UTexture2D* PlayerIcon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Map Display")
	TSubclassOf<UUserWidget> MapIconClass;

	UPROPERTY()
	UMaterialParameterCollectionInstance* MapData = nullptr;


	UFUNCTION()
	void AddPlayerIcon();


	UFUNCTION()
	void AddMapIcon(const FColor& IconTint, UTexture2D* IconImage, AActor* Actor, bool bAlwaysShow);
};

