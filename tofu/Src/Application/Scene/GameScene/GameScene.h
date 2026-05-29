#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class C_Tofu;

class GameScene : public C_BaseScene
{
public :

	GameScene();
	~GameScene();

private:

	void Event() override;
	void Init()  override;

	std::unique_ptr<C_Tofu> m_tofu = nullptr;
};
