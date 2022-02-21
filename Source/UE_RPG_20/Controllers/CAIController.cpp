#include "Controllers/CAIController.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Component/CBehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(L"Sight");

	SightSense->SightRadius = 600;
	SightSense->LoseSightRadius = 800;
	SightSense->PeripheralVisionAngleDegrees = 45;
	SightSense->SetMaxAge(2);
	
	SightSense->DetectionByAffiliation.bDetectEnemies    = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals   = false;
	SightSense->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*SightSense);
	Perception->SetDominantSense(*SightSense->GetSenseImplementation());
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACEnemy_AI>(InPawn);
	SetGenericTeamId(OwnerCharacter->GetTeamID());

	UseBlackboard(OwnerCharacter->GetBehaviorTree()->BlackboardAsset, Blackboard);

	Behavior = CHelpers::GetComponent<UCBehaviorTreeComponent>(OwnerCharacter);
	Behavior->SetBlackBoard(Blackboard);

	RunBehaviorTree(OwnerCharacter->GetBehaviorTree());
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(NULL, actors);

	ACPlayer* player = nullptr;

	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);

		if (player) break;
	}

	Blackboard->SetValueAsObject("Player", player);
}
