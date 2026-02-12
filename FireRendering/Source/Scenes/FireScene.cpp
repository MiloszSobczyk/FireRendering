#include "FireScene.h"

#include <chrono>

FireScene::FireScene()
	: plane(std::make_shared<Plane>()), 
    flameParticleSystem(std::make_shared<FlameParticleSystem>(100)),
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
    static float fireSize = 0.05f;
    static float fireSpeed = 1.0f;
    static float fireNoise1 = 2.0f;
    static float fireNoise2 = 12.0f;
    static float fireWarp = 0.15f;
    static float fireErosionLo = 0.3f;
    static float fireErosionHi = 0.6f;
    static glm::vec3 startingPosition;

    ImGui::Begin("Fire Debug");
    ImGui::Checkbox("Turn off Plane", &turnOffPlane);
    ImGui::Checkbox("Turn off Flame", &turnOffFlame);
    ImGui::Checkbox("Turn off Ember", &turnOffEmber);
    ImGui::Checkbox("Turn off Smoke", &turnOffSmoke);

    ImGui::SliderFloat3("Starting Position", &(startingPosition[0]), -2.f, 2.f);

    ImGui::SliderFloat("Particle Size", &fireSize, 0.01f, 0.2f);
    ImGui::SliderFloat("Rise Speed", &fireSpeed, 0.1f, 5.0f);

    ImGui::Separator();

    ImGui::SliderFloat("Base Noise Scale", &fireNoise1, 0.1f, 5.0f);
    ImGui::SliderFloat("Detail Noise Scale", &fireNoise2, 1.0f, 30.0f);
    ImGui::SliderFloat("Warp Strength", &fireWarp, 0.0f, 0.5f);

    ImGui::Separator();

    ImGui::SliderFloat("Erosion Low", &fireErosionLo, 0.0f, 1.0f);
    ImGui::SliderFloat("Erosion High", &fireErosionHi, 0.0f, 1.0f);

    ImGui::End();

    flameParticleSystem->startingPosition = startingPosition;
    smokeParticleSystem->startingPosition = startingPosition;
    emberParticleSystem->startingPosition = startingPosition;
}
