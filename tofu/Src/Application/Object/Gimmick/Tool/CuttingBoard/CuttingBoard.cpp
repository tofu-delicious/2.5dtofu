//CuttingBoard.cpp
#include "CuttingBoard.h"
#include "../../../../Asset/AssetManager.h"

void C_CuttingBoard::Init()
{
	m_model = C_AssetManager::Instance().GetModel("CuttingBoard");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape(
		"ObstacleCollision", m_model, KdCollider::Type::TypeBump);
}

void C_CuttingBoard::Update()
{}

void C_CuttingBoard::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(
		*m_model, m_mWorld);
}