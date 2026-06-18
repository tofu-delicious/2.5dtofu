//Obstacle.cpp
#include "Obstacle.h"
#include "../../../../Asset/AssetManager.h"

void C_Obstacle::Init()
{
	m_model = C_AssetManager::Instance().GetModel("Obstacle");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"ObstacleCollision", m_model, KdCollider::Type::TypeBump);
}

void C_Obstacle::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(
		*m_model, m_mWorld);
}