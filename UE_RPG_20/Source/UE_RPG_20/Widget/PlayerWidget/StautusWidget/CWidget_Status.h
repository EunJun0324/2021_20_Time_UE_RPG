#pragma once

#include "CoreMinimal.h"
#include "Widget/CUserWidget_Closable.h"
#include "CWidget_Status.generated.h"

UCLASS()
class UE_RPG_20_API UCWidget_Status : public UCUserWidget_Closable
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UCWidget_StatusRow> StatusRow_Class;

private :
	UPROPERTY(meat = (BindWidget))
		class UScrollBox* ScrollBox;

public :
	UCWidget_Status(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	class UDataTable* DT_StatusRowData;

};
