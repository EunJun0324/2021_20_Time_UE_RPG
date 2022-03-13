#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Health.generated.h"

UCLASS()
class UE_RPG_20_API UCUserWidget_Health : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHealth(float InHealth, float InMAxHealth);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateCharacterName(const FString& InName);
};
