#pragma once
#include "pch.h"
#include "hooks/patterns.h"
#include "rage/classes/NetObject.h"
#include "util/fiber.h"
#include "rage/invoker/natives.h"
#include "rage/classes/vector.h"

namespace menu::raycast {
	
	inline float DegreeToRadian(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	inline Vector3 RotationToDirection(Vector3 rotation)
	{
		float x = DegreeToRadian(rotation.x);
		float z = DegreeToRadian(rotation.z);

		float num = abs(cos(x));

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}

	inline Vector3 Multiply(Vector3 vector, float incline)
	{
		vector.x *= incline;
		vector.y *= incline;
		vector.z *= incline;
		return vector;
	}

	inline Vector3 Add(Vector3 vector, Vector3 vector2)
	{
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		return vector;
	}


	inline Vector3 CoordsInFrontOfCam(std::float_t distance)
	{
		Vector3 pos = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(NULL);
		Vector3 dir = RotationToDirection(rot);
		Vector3 dist = Multiply(dir, distance);
		return Add(pos, dist);
	}

	inline BOOL m_ShapeTestHit = FALSE;
	inline std::int32_t m_ShapeTestEntity = FALSE;
	inline Vector3 m_ShapeTestDestination;
	inline Vector3 m_ShapeTestSurface;
	inline std::int32_t m_ShapeTestRay = FALSE;

	inline void raycastUpdate() {
		if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID())) {
			auto Weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), NULL);
			auto Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Weapon, { 1.5f, 0.f, 0.f } );
			auto AimCoords = CoordsInFrontOfCam(1000.f);
			m_ShapeTestHit = FALSE;
			m_ShapeTestEntity = NULL;
			m_ShapeTestDestination.x = 0.f;
			m_ShapeTestDestination.y = 0.f;
			m_ShapeTestDestination.z = 0.f;
			m_ShapeTestSurface.x = 0.f;
			m_ShapeTestSurface.y = 0.f;
			m_ShapeTestSurface.z = 0.f;
			m_ShapeTestRay = NULL;
			m_ShapeTestRay = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(Coords, AimCoords, -1, PLAYER::PLAYER_PED_ID(), 7);
			SHAPETEST::GET_SHAPE_TEST_RESULT(m_ShapeTestRay, &m_ShapeTestHit, &m_ShapeTestDestination, &m_ShapeTestSurface, &m_ShapeTestEntity);
		}
	}

	inline bool raycast(Entity* ent)
	{
		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = RotationToDirection(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords, farCoords, -1, 0, 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

		return (bool)hit;
	}

	inline bool IsEmpty(Vector3 vector)
	{
		if (vector.x == 0.f && vector.y == 0.f && vector.z == 0.f)
			return true;
		return false;
	}

}