#include "FireScene.h"

#include <chrono>

FireScene::FireScene()
	: plane(std::make_shared<Plane>()), 
    flameParticleSystem(std::make_shared<FlameParticleSystem>(100)),
	smokeParticleSystem(std::make_shared<SmokeParticleSystem>(20)),
    emberParticleSystem(std::make_shared<EmberParticleSystem>(20))
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
	emberParticleSystem->Update(deltaTime);
}


void FireScene::RenderOnScene()
{
	plane->Render();
    flameParticleSystem->Render();
    //smokeParticleSystem->Render();
	emberParticleSystem->Render();
}

void FireScene::RenderUI()
{
}
