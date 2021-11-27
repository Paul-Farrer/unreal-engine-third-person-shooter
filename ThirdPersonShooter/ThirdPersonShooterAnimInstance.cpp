// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonShooterAnimInstance.h"
#include "ThirdPersonShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UThirdPersonShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ThirdPersonShooterCharacter == nullptr)
	{
		ThirdPersonShooterCharacter = Cast<AThirdPersonShooterCharacter>(TryGetPawnOwner());
	}
	if (ThirdPersonShooterCharacter)
	{
		// Get the lateral speed of the character from the velocity
		FVector Velocity{ ThirdPersonShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = ThirdPersonShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if (ThirdPersonShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = ThirdPersonShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ThirdPersonShooterCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (ThirdPersonShooterCharacter->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}
		
		bAiming = ThirdPersonShooterCharacter->GetAiming();
	}
}

void UThirdPersonShooterAnimInstance::NativeInitializeAnimation()
{
	ThirdPersonShooterCharacter = Cast<AThirdPersonShooterCharacter>(TryGetPawnOwner());
}