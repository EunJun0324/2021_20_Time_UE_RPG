#pragma once

#include "CoreMinimal.h"
#include "Widget/CUserWidget_Closable.h"
#include "Component/CStatusComponent.h"
#include "CWidget_Status.generated.h"

UCLASS()
class UE_RPG_20_API UCWidget_Status : public UCUserWidget_Closable
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UCWidget_StatusRow> StatusRow_Class;

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		class UDataTable* DT_StatusRowData;

private :
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ScrollBox_List;

public :
	UCWidget_Status(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	TArray<class UCWidget_StatusRow*> Rows;


};
