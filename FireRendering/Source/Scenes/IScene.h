#pragma once

class IScene
{
protected:
	bool running = false;

public:
	virtual ~IScene() = default;

	virtual void Update() = 0;
	virtual void RenderOnScene() = 0;
	virtual void RenderUI() = 0;

	inline void ToggleRunning() { running = !running; }
	inline void Stop() { running = false; }
	inline void Start() { running = true; }
};