//KitchenManager.cpp
#include "KitchenManager.h"
#include "../Gimmick/GimmickManager.h" // 通知先

void C_KitchenManager::Init()
{
	// 最初の1個を生成して配置
	auto first = m_kitchenFactory.GetNext();
	first->SetPos(INITIAL_POS);
	first->UpdateMatrix();
	m_kitchens.push_back(first);
	NotifyKitchenSpawned(first); // GimmickManagerへ通知

	auto second = m_kitchenFactory.GetNext();
	second->SetPos(Math::Vector3{ INITIAL_POS.x + KITCHEN_WIDTH, INITIAL_POS.y, INITIAL_POS.z });
	second->UpdateMatrix();
	m_kitchens.push_back(second);
	NotifyKitchenSpawned(second); // GimmickManagerへ通知
}

void C_KitchenManager::Update()
{
	// 全キッチンを左方向へ移動
	for (auto& kitchen : m_kitchens)
	{
		Math::Vector3 pos = kitchen->GetPos();
		pos.x -= SCROLL_SPEED;
		kitchen->SetPos(pos);
	}

	// 画面外に出たキッチンを削除
	m_kitchens.remove_if([&](const std::shared_ptr<C_Kitchen>& k)
		{
			return k->GetPos().x < DESTROY_THRESHOLD;
		});

	// 最後のキッチンが一定位置まで来たら次を生成
	while(!m_kitchens.empty() && m_kitchens.back()->GetPos().x < SPAWN_THRESHOLD)
	{
		auto next = m_kitchenFactory.GetNext();
		float nextX = m_kitchens.back()->GetPos().x + KITCHEN_WIDTH;
		next->SetPos(Math::Vector3{ nextX, INITIAL_POS.y, INITIAL_POS.z });
		next->UpdateMatrix();
		m_kitchens.push_back(next);
		NotifyKitchenSpawned(next); // GimmickManagerへ通知
	}
}

void C_KitchenManager::NotifyKitchenSpawned(std::shared_ptr<C_Kitchen> a_kitchen)
{
	// GimmickManagerが登録されていなければ何もしない
	if (m_wpGimmickMgr.expired()) return;

	m_wpGimmickMgr.lock()->OnKitchenSpawned(a_kitchen);
}

void C_KitchenManager::ImGui()
{
	ImGui::SameLine();

	if (ImGui::Button("KitchenManager")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::Text("m_kitchens.size:%zu", m_kitchens.size());
	}
}