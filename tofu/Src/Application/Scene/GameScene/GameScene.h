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

	//m_kitchensリストをm_objListへ格納する
	void SyncKitchensObjList();

	//m_gimmicksリストをm_objListへ格納する
	void SyncGimmicksObjList();

	//デバッグ表示させたいクラス情報を、ImGuiManagerへ送信する
	void SetUpImGuiManager();

	//ポーズ画面を表示させる
	void DrawOverlayPauseScene();

	//シーンをResultシーンへ遷移させる
	void ChangeResultScene();

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

	//================ 状態フラグ ==============
	bool m_isChangeResultScene = false;		//true：リザルトシーンへ遷移する
};