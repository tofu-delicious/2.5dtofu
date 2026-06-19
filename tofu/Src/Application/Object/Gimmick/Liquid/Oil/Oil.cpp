//Oil.cpp
#include "Oil.h"
#include "../../../../Asset/AssetManager.h"

void C_Oil::Init()
{
	m_model = C_AssetManager::Instance().GetModel("Oil");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"OilCollision", m_model, KdCollider::Type::TypeBump);
}

void C_Oil::DrawLit()
{
 	KdShaderManager::Instance().m_StandardShader.DrawModel(
		*m_model, m_mWorld);
}