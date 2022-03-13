#pragma once

#include "CoreMinimal.h"
#include "Weapon/CSkill.h"
#include "NiagaraDataInterfaceExport.h"
#include "CSkill_Thron.generated.h"

UCLASS()
class UE_RPG_20_API ACSkill_Thron : public ACSkill
	, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
		class UStaticMesh* CollisionMesh;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class UNiagaraComponent* Niagara;

public :
	ACSkill_Thron();

	void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem) override;

protected :
	virtual void BeginPlay() override;

};
