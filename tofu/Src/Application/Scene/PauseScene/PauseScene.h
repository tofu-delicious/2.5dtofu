//PauseScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

class C_PauseScene :public C_BaseScene
{
public:
	C_PauseScene();
	~C_PauseScene();

private:

	void Event()override;
	void Init()override;
};