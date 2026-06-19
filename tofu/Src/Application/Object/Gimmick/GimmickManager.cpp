//GimmickManager.cpp
#include "GimmickManager.h"

void C_GimmickManager::Update()
{
	// 全ギミックをキッチンと同じ速度で左へ移動
	for (auto& gimmick : m_gimmicks)
	{
		Math::Vector3 pos = gimmick->GetPos();
		pos.x -= SCROLL_SPEED;
		gimmick->SetPos(pos);
		//gimmick->Update(); // UpdateMatrix()を内部で呼ぶ
	}

	// 画面外に出たギミックを削除
	m_gimmicks.remove_if([](const std::shared_ptr<C_GimmickBase>& g)
		{
			return g->GetPos().x < DESTROY_THRESHOLD;
		});
}

void C_GimmickManager::OnKitchenSpawned(std::shared_ptr<C_Kitchen> a_kitchen)
{
	// コンロなしキッチンなら何もしない ← これが前回のバグの対策
	if (a_kitchen->GetKitchenType() != C_Kitchen::KitchenType::withAppliances)
		return;

	// コンロありキッチンのときだけ、そのX座標を渡してギミックを生成
	auto newGimmicks = m_gimmickFactory.GetNextPattern(a_kitchen->GetPos().x, SCROLL_SPEED);

	for (auto& g : newGimmicks)
	{
		m_gimmicks.push_back(g);
	}
}

void C_GimmickManager::ImGui()
{
	//Sameline()：次のウィジェットを横方向に位置付ける
	ImGui::SameLine();

	if (ImGui::Button("GimmickMgr")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::Text("m_gimmicks.size:%zu", m_gimmicks.size());
	}
}
