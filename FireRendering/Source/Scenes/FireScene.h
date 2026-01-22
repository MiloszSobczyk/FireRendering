#pragma once

#include <memory>

#include "IScene.h"
#include "Objects/Plane.h"


class FireScene : public IScene
{
private:
	std::shared_ptr<Plane> plane;

public:
	FireScene();
	~FireScene() override = default;
	
	void Update() override;
	void RenderOnScene() override;
	void RenderUI() override;
};