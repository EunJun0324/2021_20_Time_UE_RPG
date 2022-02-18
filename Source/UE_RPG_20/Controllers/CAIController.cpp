#include "Controllers/CAIController.h"
#include "Global.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(L"Perception"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(L"Sight");

	SightSense->SightRadius = 90;

}