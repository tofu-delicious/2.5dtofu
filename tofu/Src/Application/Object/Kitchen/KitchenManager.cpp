//KitchenManager.cpp
#include "KitchenManager.h"

void C_KitchenManager::Init()
{
	//最初の1個を生成して配置
	auto first = m_factory.GetNext();
	first->SetPos(INITIAL_POS);
	first->UpdateMatrix();
	m_kitchens.push_back(first);

	auto second = m_factory.GetNext();
	second->SetPos(Math::Vector3{SPAWN_POS_X, INITIAL_POS.y, INITIAL_POS.z });
	second->UpdateMatrix();
	m_kitchens.push_back(second);
}

void C_KitchenManager::Update()
{
	//全キッチンを左方向へ移動
	for (auto& kitchen : m_kitchens)
	{
		Math::Vector3 pos = kitchen->GetPos();
		pos.x -= SCROLL_SPEED;
		kitchen->SetPos(pos);
	}

	//画面外に出たキッチンを削除
	m_kitchens.remove_if([&](const std::shared_ptr<C_Kitchen>& k)
		{
			return k->GetPos().x < DESTROY_THRESHOLD;
		});

	//最後のキッチンが一定位置まで来たら次を生成
	if (!m_kitchens.empty() && m_kitchens.back()->GetPos().x < SPAWN_THRESHOLD)
	{
		auto next = m_factory.GetNext();
		next->SetPos(Math::Vector3{SPAWN_POS_X,INITIAL_POS.y,INITIAL_POS.z});
		next->UpdateMatrix();
		m_kitchens.push_back(next);
	}
}

void C_KitchenManager::ImGui()
{
	//Sameline()：次のウィジェットを横方向に位置付ける
	ImGui::SameLine();

	if (ImGui::Button("KitchenManager")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::Text("m_kitchens.size:%zu",m_kitchens.size());

		/*ImGui::DragFloat("SCROLL_SPEED", &SCROLL_SPEED, -0.01f, -10.0f, 10.0f);
		ImGui::DragFloat("SPAWN_THRESHOLD", &SPAWN_THRESHOLD, -1.0f, -400.0f, 400.0f);
		ImGui::DragFloat("DESTROY_THRESHOLD", &DESTROY_THRESHOLD, -1.0f, -400.0f, 400.0f);
		ImGui::DragFloat("SPAWN_POS_X", &SPAWN_POS_X, -1.0f, -400.0f, 400.0f);*/
	}
}
