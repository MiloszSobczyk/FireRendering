#include "FireScene.h"

FireScene::FireScene()
	: plane(std::make_shared<Plane>())
{
}

void FireScene::Update()
{
}

void FireScene::RenderOnScene()
{
	plane->Render();
}

void FireScene::RenderUI()
{
}
