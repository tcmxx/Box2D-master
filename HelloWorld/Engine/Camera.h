#pragma once
#include "Box2D/Box2D.h"

//
struct Camera
{
	Camera()
	{
		m_center.Set(0.0f, 15.0f);
		m_zoom = 1.0f;
		m_width = 1280;
		m_height = 800;
	}

	b2Vec2 ConvertScreenToWorld(const b2Vec2& screenPoint);
	b2Vec2 ConvertWorldToScreen(const b2Vec2& worldPoint);
	void BuildProjectionMatrix(float32* m, float32 zBias);

	b2Vec2 m_center;
	float32 m_zoom;
	int32 m_width;
	int32 m_height;
};