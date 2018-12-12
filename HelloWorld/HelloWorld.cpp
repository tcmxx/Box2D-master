/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
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
#include "DebugDraw.h"
#include "Box2D/Box2D.h"
#include "Engine\Engine.h"
#include <stdio.h>


#include "Game\TargetBall.h"








// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
// There are no graphics for this example. Box2D is meant to be used
// with your rendering engine in your game engine.
int main(int argc, char** argv)
{
	Engine::Initialize();

	Scene* scene = Engine::GetScene();

	//create the ball object
	GameObject* testObject = scene->InstantiateGameObject<GameObject>();
	auto collider = testObject->AddComponent<CircleCollider2D>();
	collider->SetCircle(1, b2Vec2_zero);
	testObject->AddComponent<Rigidbody2D>();
	Rigidbody2D* comp = testObject->GetComponent<Rigidbody2D>();
	comp->SetType(b2_dynamicBody);
	comp->SetTransform(b2Vec2(0, 10), 0);

	//create the ground object
	GameObject* groundObject = scene->InstantiateGameObject<GameObject>();
	auto boxcollider = groundObject->AddComponent<BoxCollider2D>();
	boxcollider->SetBox(b2Vec2(10, 1), b2Vec2_zero, 0);
	auto groundBody = groundObject->AddComponent<Rigidbody2D>();
	groundBody->SetType(b2_staticBody);

	scene->InstantiateGameObject<TargetBall>(b2Vec2(0, 20),0);

	Engine::Run();

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}
