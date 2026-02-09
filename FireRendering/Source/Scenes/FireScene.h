#pragma once

#include <memory>

#include "IScene.h"
#include "Objects/Plane.h"
#include "Particles/ParticleSystem.h"


class FireScene : public IScene
{
public:
	FireScene();
	~FireScene() override = default;
	
	void Update() override;
	void RenderOnScene() override;
	void RenderUI() override;

private:
	std::shared_ptr<Plane> plane;
	std::shared_ptr<ParticleSystem> particleSystem;
};