#pragma once
#include <Windows.h>
#include <DirectXMath.h>

class MathHelper {
public:
	// Returns random float in [0, 1].
	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b].
	static float RandF(float a, float b)
	{
		return a + RandF()*(b - a);
	}

	static DirectX::XMFLOAT4X4 Identity4x4()
	{
		static DirectX::XMFLOAT4X4 I(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return I;
	}

	static const float Pi;
};