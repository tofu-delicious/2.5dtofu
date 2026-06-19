//GameScene.h
#pragma once
#include "../BaseScene/BaseScene.h"

// 前方宣言
class C_BackGroundScroller;
class C_Tofu;
class C_KitchenManager;
class C_GimmickManager; // 追加

class GameScene : public C_BaseScene
{
public:

	GameScene();
	~GameScene();

	void SyncKitchensObjList();
	void SyncGimmicksObjList(); // 追加
	void SetUpImGuiManager();

private:

	void Event() override;
	void Init()  override;

	//=============== インスタンス =============
	std::shared_ptr<C_BackGroundScroller> m_back = nullptr;
	std::shared_ptr<C_Tofu>              m_tofu = nullptr;
	std::shared_ptr<C_KitchenManager>    m_kitchenMgr = nullptr;
	std::shared_ptr<C_GimmickManager>    m_gimmickMgr = nullptr; // 追加

	//================= 定数 ===============
	static constexpr Math::Vector3 CAMERA_POS = { 0.0f, 1.1f, -1.0f };
	static constexpr float         CAMERA_ROTATE = 15.0f;
};