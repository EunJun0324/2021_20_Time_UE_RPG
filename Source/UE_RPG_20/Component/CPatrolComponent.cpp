#include "Component/CPatrolComponent.h"
#include "Global.h"
#include "BehaviorTree/CPatrolPath.h"
#include "Components/SplineComponent.h"

UCPatrolComponent::UCPatrolComponent()
{
}


void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceDistanse)
{
	OutLocation = FVector::ZeroVector;
	OutAcceptanceDistanse = 0.0f;
	CheckFalseResult(IsValidPath(), false);

	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(NextIndex, ESplineCoordinateSpace::World);
	OutAcceptanceDistanse = AcceptanceDistanse;

	return false;
}

void UCPatrolComponent::UpdateNextIndex()
{
	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();
	if (bReverse)
	{
		if (NextIndex > 0)
		{
			NextIndex--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())
		{
			NextIndex = count - 1;

			return;
		}

		NextIndex = 1;
		bReverse = false;

		return;
	}

	if (NextIndex < count - 1)
	{
		NextIndex++;

		return;
	}

	if (Path->GetSpline()->IsClosedLoop())
	{
		NextIndex = 0;

		return;
	}

	NextIndex = count - 2;
	bReverse = true;
}