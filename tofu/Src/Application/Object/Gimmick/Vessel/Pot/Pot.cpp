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