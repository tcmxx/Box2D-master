
#include "DebugDraw.h"
#include "Box2D/Box2D.h"
#include "Engine\Engine.h"
#include <stdio.h>


#include "Game\TargetBall.h"
#include "Game\GameController.h"
#include "Game\StaticWall.h"
#include "Game\TargetSpawner.h"
#include "Game\Basket.h"
#include "Game\GameplayUI.h"

void CreateObjects(Scene* scene);

int main(int argc, char** argv)
{
	Engine::Initialize();

	Scene* scene = Engine::GetScene();

	CreateObjects(scene);

	Engine::Run();

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}

void CreateObjects(Scene* scene) {


	//scene->InstantiateGameObject<TargetBall>(b2Vec2(0, 20), 0);


	//create the static walls of the scene
	StaticWallData wallDataground;
	wallDataground.size = b2Vec2(20, 1);
	scene->InstantiateGameObject<StaticWall>(b2Vec2(0, 0), 0, "Ground", &wallDataground);
	scene->InstantiateGameObject<StaticWall>(b2Vec2(-45, 0), 0, "Ground", &wallDataground);
	scene->InstantiateGameObject<StaticWall>(b2Vec2(45, 0), 0, "Ground", &wallDataground);
	StaticWallData wallDataleft;
	wallDataleft.size = b2Vec2(1, 10);
	scene->InstantiateGameObject<StaticWall>(b2Vec2(-28,10),0,"WallLeft", &wallDataleft);
	StaticWallData wallDataRight;
	wallDataRight.size = b2Vec2(1, 10);
	scene->InstantiateGameObject<StaticWall>(b2Vec2(28, 10), 0, "WallRight", &wallDataRight);

	//the baskets
	BasketData playerOneBasketData;
	playerOneBasketData.isPlayerOne = true;
	playerOneBasketData.color = b2Color(0, 1, 0, 1);
	scene->InstantiateGameObject<Basket>(b2Vec2(-22.5f, -4), 0, "PlayerOneBasket", &playerOneBasketData);
	BasketData playerTwoBasketData;
	playerTwoBasketData.isPlayerOne = false;
	playerTwoBasketData.color = b2Color(0, 0, 1, 1);
	scene->InstantiateGameObject<Basket>(b2Vec2(22.5, -4), 0, "PlayerTwoBasket", &playerTwoBasketData);


	//game logic related
	scene->InstantiateGameObject<GameController>();
	scene->InstantiateGameObject<TargetSpawner>();

	//UI
	scene->InstantiateGameObject<GameplayUI>();
}
