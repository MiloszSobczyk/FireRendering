#include "FireScene.h"

#include <chrono>

FireScene::FireScene()
	: plane(std::make_shared<Plane>()), 
    flameParticleSystem(std::make_shared<FlameParticleSystem>(20)),
	smokeParticleSystem(std::make_shared<SmokeParticleSystem>(20))
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

    flameParticleSystem->Update(deltaTime);
	smokeParticleSystem->Update(deltaTime);
}


void FireScene::RenderOnScene()
{
	plane->Render();
    smokeParticleSystem->Render();
    flameParticleSystem->Render();
}

void FireScene::RenderUI()
{
}
