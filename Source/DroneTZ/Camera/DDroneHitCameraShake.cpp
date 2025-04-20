#include "DDroneHitCameraShake.h"

UDDroneHitCameraShake::UDDroneHitCameraShake()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = 4.f;
	RotOscillation.Pitch.Frequency = 15.f;

	RotOscillation.Yaw.Amplitude = 4.f;
	RotOscillation.Yaw.Frequency = 15.f;

	LocOscillation.Z.Amplitude = 3.f;
	LocOscillation.Z.Frequency = 15.f;
}
