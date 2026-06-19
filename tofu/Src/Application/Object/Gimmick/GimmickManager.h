//GimmickManager.h
#pragma once
#include "../Kitchen/Kitchen/Kitchen.h"
#include "Factory/GimmickFactory.h"

class C_GimmickManager
{
public:
	C_GimmickManager() {}
	~C_GimmickManager() {}

	void Update();

	// コンロありキッチンが新しく生成されたときに呼ぶ
	// → そのキッチンの上にギミックを配置する
	void OnKitchenSpawned(std::shared_ptr<C_Kitchen> a_kitchen);

	// objListに渡すため、外部から参照できるようにする
	const std::list<std::shared_ptr<C_GimmickBase>>& GetGimmicks() const
	{
		return m_gimmicks;
	}

	void ImGui();

private:

	//====== インスタンス・可変長配列 ========
	// 現在画面上にあるギミックのリスト
	std::list<std::shared_ptr<C_GimmickBase>> m_gimmicks;

	// ギミックの生成クラス
	C_GimmickFactory m_gimmickFactory;

	//================ 定数 =================
	static constexpr float SCROLL_SPEED = 0.01f;  // キッチンと同じスクロール速度
	static constexpr float DESTROY_THRESHOLD = -3.0f;   // キッチンと同じ削除ライン

	//============= 状態フラグ ===============
	bool m_isDebugOpen = false;
};