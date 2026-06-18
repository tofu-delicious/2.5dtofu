//Pot.cpp
#include "Pot.h"
#include "../../../../Asset/AssetManager.h"

void C_Pot::Init()
{
	m_model = C_AssetManager::Instance().GetModel("Pot");

	m_pCollider = std::make_unique<KdCollider>();
	// 縁にぶつかる → TypeBump
	m_pCollider->RegisterCollisionShape(
		"PotCollision", m_model, KdCollider::Type::TypeBump);
}

void C_Pot::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(
		*m_model, m_mWorld);
}

void C_Pot::ImGui()
{
	//Sameline()：次のウィジェットを横方向に位置付ける
	ImGui::SameLine();

	if (ImGui::Button("Pot")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::Text("m_pos.x : %.2f", m_pos.x);
		ImGui::Text("m_pos.y : %.2f", m_pos.y);
		ImGui::Text("m_pos.z : %.2f", m_pos.z);
	}
}
