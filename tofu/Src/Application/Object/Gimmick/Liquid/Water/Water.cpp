//Water.cpp
#include "Water.h"
#include "../../../../Asset/AssetManager.h"

void C_Water::Init()
{
	m_model = C_AssetManager::Instance().GetModel("Water");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"WaterCollision", m_model, KdCollider::Type::TypeBump);
}

void C_Water::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(
		*m_model, m_mWorld);
}