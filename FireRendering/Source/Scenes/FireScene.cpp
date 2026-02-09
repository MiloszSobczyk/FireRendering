#include "FireScene.h"
#include <chrono>

FireScene::FireScene()
	: plane(std::make_shared<Plane>()), particleSystem(std::make_shared<ParticleSystem>(20))
{
}

void FireScene::Update()
{
    using clock = std::chrono::high_resolution_clock;

    static auto lastTime = clock::now();

    auto currentTime = clock::now();
    std::chrono::duration<float> delta = currentTime - lastTime;
    lastTime = currentTime;

    float deltaTime = delta.count();

    particleSystem->Update(deltaTime);
}


void FireScene::RenderOnScene()
{
	plane->Render();
	particleSystem->Render();
}

void FireScene::RenderUI()
{
}
