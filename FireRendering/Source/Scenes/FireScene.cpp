#include "FireScene.h"

#include <chrono>

FireScene::FireScene()
	: plane(std::make_shared<Plane>()), 
    flameParticleSystem(std::make_shared<FlameParticleSystem>(10000)),
	smokeParticleSystem(std::make_shared<SmokeParticleSystem>(100)),
    emberParticleSystem(std::make_shared<EmberParticleSystem>(50))
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
    if(!turnOffPlane)
	    plane->Render();
    if (!turnOffFlame)
		flameParticleSystem->Render();
    if (!turnOffSmoke)
		smokeParticleSystem->Render();
    if (!turnOffEmber)
		emberParticleSystem->Render();
}

void FireScene::RenderUI()
{
    static glm::vec3 startingPosition;

    ImGui::Begin("Fire Debug");
    ImGui::Checkbox("Turn off Plane", &turnOffPlane);
    ImGui::Checkbox("Turn off Flame", &turnOffFlame);
    ImGui::Checkbox("Turn off Ember", &turnOffEmber);
    ImGui::Checkbox("Turn off Smoke", &turnOffSmoke);

    ImGui::DragFloat3("Starting Position", &(startingPosition[0]), 0.01f, -2.f, 2.f);

    ImGui::Checkbox("Add randomness to flame", &flameParticleSystem->addFlameRandomness);

    ImGui::DragFloat("Starting flame disk radius", &flameParticleSystem->diskRadius, 0.01f, 0.f, 0.5f);
    ImGui::DragFloat("Starting flame cone radius", &flameParticleSystem->coneRadius, 0.01f, 0.f, 1.f);

    flameParticleSystem->RenderUI();
    emberParticleSystem->RenderUI();

    ImGui::End();

    flameParticleSystem->startingPosition = startingPosition;
    smokeParticleSystem->startingPosition = startingPosition;
    emberParticleSystem->startingPosition = startingPosition;
}
