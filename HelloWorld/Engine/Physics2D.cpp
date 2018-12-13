#include "Physics2D.h"
#include "GameObject.h"

Physics2D::Physics2D():world2D(DEFAULT_GRAVITY) {
	world2D.SetContactListener(this);
}



void Physics2D::BeginContact(b2Contact* contact) {
	while (contact != nullptr) {

		auto fixtureA = contact->GetFixtureA();
		auto fixtureB = contact->GetFixtureB();

		auto colliderA = (Collider2D*)fixtureA->GetUserData();
		auto colliderB = (Collider2D*)fixtureB->GetUserData();

		CollisionInfo2D collisionA;
		collisionA.manifold = *contact->GetManifold();
		collisionA.other = colliderB;

		CollisionInfo2D collisionB;
		collisionB.manifold = collisionA.manifold;
		collisionB.other = colliderA;
		collisionB.manifold.localNormal = -collisionB.manifold.localNormal;

		colliderA->GetGameObject()->OnCollisionEnter(collisionA);
		colliderB->GetGameObject()->OnCollisionEnter(collisionB);

		contact = contact->GetNext();
	}
}
void Physics2D::EndContact(b2Contact* contact) {
	while (contact != nullptr) {

		auto fixtureA = contact->GetFixtureA();
		auto fixtureB = contact->GetFixtureB();

		auto colliderA = (Collider2D*)fixtureA->GetUserData();
		auto colliderB = (Collider2D*)fixtureB->GetUserData();

		CollisionInfo2D collisionA;
		collisionA.manifold = *contact->GetManifold();
		collisionA.other = colliderB;

		CollisionInfo2D collisionB;
		collisionB.manifold = collisionA.manifold;
		collisionB.other = colliderA;
		collisionB.manifold.localNormal = -collisionB.manifold.localNormal;

		if(colliderA != nullptr)
			colliderA->GetGameObject()->OnCollisionExit(collisionA);
		if (colliderB != nullptr)
			colliderB->GetGameObject()->OnCollisionExit(collisionB);

		contact = contact->GetNext();
	}
}



void Physics2D::Step() {
	//step the physics2D world
	world2D.Step(physics2DSetting.timestep, physics2DSetting.velocityIterations, physics2DSetting.positionIterations);

}