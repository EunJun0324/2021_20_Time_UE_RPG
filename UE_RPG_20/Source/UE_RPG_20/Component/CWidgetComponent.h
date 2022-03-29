#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWidgetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_RPG_20_API UCWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	TSubclassOf<class UCWidgetController> WidgetControllerClass;
	
	TSubclassOf<class UCPlayerWidget> PlayerWidgetClass;

	TSubclassOf<class UCWidget_Status> StatusWidgetClass;


private :
	UPROPERTY(VisibleDefaultsOnly)
		class UCWidgetController* WidgetController;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCPlayerWidget* PlayerWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWidget_Status* StatusWidget;

public:	
	UCWidgetComponent();

protected:
	virtual void BeginPlay() override;

private :
	void OpenStatus();

	void CloseStatus();

public :
	void ToggleStatus();
};
