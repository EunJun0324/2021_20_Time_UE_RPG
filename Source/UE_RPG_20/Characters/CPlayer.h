#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_RPG_20_API ACPlayer  : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float HorizontalLook = 45;

	UPROPERTY(EditDefaultsOnly, Category = "CameraSpeed")
		float VerticalLook = 45;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;
public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

	void OnOneHand();

	void OnAction();


private :
	UPROPERTY(EditDefaultsOnly, Category = "Sword")
		TSubclassOf<class ACSword> SwordClass;

	class ACSword* Sword;

public :
	FORCEINLINE class ACSword* GetSword() { return Sword; }
};
