#include "Physics2D.h"
#include "GameObject.h"

Physics2D::Physics2D() :world2D(DEFAULT_GRAVITY) {
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

		if (colliderA != nullptr)
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

std::vector<Collider2D*> Physics2D::SphereOverlay(b2Vec2 position, float32 radius) {
	b2AABB aabb;
	aabb.lowerBound = position - b2Vec2(radius, radius);
	aabb.upperBound = position + b2Vec2(radius, radius);
	world2D.QueryAABB(this, aabb);

	b2CircleShape shape;
	shape.m_p = position;
	shape.m_radius = radius;

	vector<Collider2D*> colliders;
	b2Transform transformId;
	transformId.SetIdentity();
	for (std::vector<b2Fixture*>::size_type i = 0; i != tempFixturesHolder.size(); i++) {
		b2Shape* testShape = tempFixturesHolder[i]->GetShape();
		
		if (b2TestOverlap(&shape, 0, testShape, 0, transformId, tempFixturesHolder[i]->GetBody()->GetTransform())) {
			Collider2D* collider = (Collider2D*)tempFixturesHolder[i]->GetUserData();
			if (collider != nullptr) {
				colliders.push_back(collider);
			}
		}
	}
	tempFixturesHolder.clear();
	return colliders;
}

bool Physics2D::ReportFixture(b2Fixture* fixture) {
	tempFixturesHolder.push_back(fixture);
	return true;
}