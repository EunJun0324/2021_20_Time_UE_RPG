#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CLevelScript_Title.generated.h"

UCLASS()
class UE_RPG_20_API ACLevelScript_Title : public ALevelScriptActor
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UCWidget_Title> BP_CWidget_Title;

public :
	ACLevelScript_Title();

protected :
	virtual void BeginPlay() override;

};
