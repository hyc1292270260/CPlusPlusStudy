#pragma once
struct Vec3 {
	Vec3()
	{
	};

	Vec3(float x, float y, float z) :x(x), y(y), z(z)
	{

	};

	Vec3 operator+ (const Vec3& vec)
	{
		return Vec3(vec.x + x, vec.y + y, vec.z + z);
	}

	Vec3 operator- (const Vec3& vec)
	{
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vec3 operator* (float value)
	{
		return Vec3(x * value, y * value, z * value);
	}

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};