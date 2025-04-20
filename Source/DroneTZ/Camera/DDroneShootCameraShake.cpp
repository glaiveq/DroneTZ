#include "DDroneShootCameraShake.h"

UDDroneShootCameraShake::UDDroneShootCameraShake()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = 0.8f;
	RotOscillation.Pitch.Frequency = 15.f;

	RotOscillation.Yaw.Amplitude = 0.8f;
	RotOscillation.Yaw.Frequency = 15.f;

	LocOscillation.Z.Amplitude = 0.8f;
	LocOscillation.Z.Frequency = 15.f;
}