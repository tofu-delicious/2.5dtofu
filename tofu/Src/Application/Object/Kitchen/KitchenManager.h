//KitchenManager.h
#pragma once
#include "../Kitchen/Factory/KitchenFactory.h"

// 前方宣言（循環インクルードを避けるため）
class C_GimmickManager;

class C_KitchenManager
{
public:
	C_KitchenManager() {}
	~C_KitchenManager() {}

	void Init();
	void Update();

	// objListに渡すため、外部から参照できるようにする
	const std::list<std::shared_ptr<C_Kitchen>>& GetKitchens() const
	{
		return m_kitchens;
	}

	// GimmickManagerを登録する（GameScene::Init()で呼ぶ）
	// キッチンが新たに生成されたとき、ここに登録したGimmickManagerへ通知する
	void SetGimmickManager(std::shared_ptr<C_GimmickManager> a_gimmickMgr)
	{
		m_wpGimmickMgr = a_gimmickMgr;
	}

	//============= デバッグ ================
	void ImGui();

private:

	// 新しいキッチンを生成したあとにGimmickManagerへ通知する内部関数
	void NotifyKitchenSpawned(std::shared_ptr<C_Kitchen> a_kitchen);

	//====== インスタンス・可変長配列 ========
	std::list<std::shared_ptr<C_Kitchen>> m_kitchens;

	// GimmickManagerへの弱参照（所有はGameScene側）
	std::weak_ptr<C_GimmickManager> m_wpGimmickMgr;

	// 生成クラス
	C_KitchenFactory m_kitchenFactory;

	//================ 定数 =================
	static constexpr Math::Vector3 INITIAL_POS = Math::Vector3{ 0.0f, 0.7f, 0.0f };
	static constexpr float KITCHEN_WIDTH = 2.4f;
	static constexpr float SCROLL_SPEED = 0.01f;
	static constexpr float SPAWN_POS_X = 6.0f;
	static constexpr float SPAWN_THRESHOLD = 2.0f;
	static constexpr float DESTROY_THRESHOLD = -3.0f;

	//============ 状態フラグ ===============
	bool m_isDebugOpen = false;
};