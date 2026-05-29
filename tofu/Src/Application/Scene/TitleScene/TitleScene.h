#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public C_BaseScene
{
public :

	TitleScene()  { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init()  override;
};
