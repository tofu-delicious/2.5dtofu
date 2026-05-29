//Tofu.cpp
#include "Tofu.h"
#include "../../Asset/AssetManager.h"

void C_Tofu::Init()
{
	//➀実体化
	m_model = std::make_shared<KdModelData>();
	//➁ロード
	m_model = ASSETMANAGER.GetModel("Tofu");

	m_mWorld = Math::Matrix::Identity;
}

void C_Tofu::PreUpdate()
{
}

void C_Tofu::Update()
{
}

void C_Tofu::PostUpdate()
{
}

void C_Tofu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
