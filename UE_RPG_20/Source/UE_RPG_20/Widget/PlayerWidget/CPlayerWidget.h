#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

UCLASS()
class UE_RPG_20_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UCWidget_PlayerState* PlayerState;

protected :
	virtual void NativeConstruct() override;

public :
	FORCEINLINE UCWidget_PlayerState* GetPlayerState()
	{ return PlayerState; }
};
