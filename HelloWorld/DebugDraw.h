/*
* Copyright (c) 2006-2013 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "Box2D/Box2D.h"
#include "Engine\Camera.h"


struct b2AABB;
struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;



// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class DebugDraw 
{
public:
	DebugDraw();
	~DebugDraw();

	void Create(Camera* camera);
	void Destroy();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, const b2Transform& transform = b2Transform());

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, const b2Transform& transform = b2Transform());

	void DrawBox(const b2Vec2& size, const b2Vec2& center, const b2Color& color, const b2Transform& transform = b2Transform());

	void DrawSolidBox(const b2Vec2& size, const b2Vec2& center, const b2Color& color, const b2Transform& transform = b2Transform());

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color, const b2Transform& transform = b2Transform());

	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

	void DrawString(int x, int y, const char* string, ...); 

	void DrawString(const b2Vec2& p, const char* string, ...);

	void Flush();

private:
	GLRenderPoints* m_points;
	GLRenderLines* m_lines;
	GLRenderTriangles* m_triangles;

	Camera* camera = nullptr;
};


#endif
