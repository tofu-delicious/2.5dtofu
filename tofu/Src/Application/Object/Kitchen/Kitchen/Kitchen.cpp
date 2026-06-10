//Kitchen.cpp
#include "Kitchen.h"
#include "../../../Asset/AssetManager.h"

void C_Kitchen::Init()
{
	//============ 初期化 ==============
	if (m_kitchenType == KitchenType::withAppliances)
	{
		m_model = ASSETMANAGER.GetModel("Kitchen");			//コンロ・シンクありモデル
	}
	else
	{
		m_model = ASSETMANAGER.GetModel("SimpleKitchen");	//コンロ・シンクなしモデル
	}
	//初期座標はZ座標を-4の位置にする
	m_pos = INITIAL_POS;

	//========= 衝突判定初期化 =========
	m_pCollider = std::make_unique<KdCollider>();

	m_pCollider->RegisterCollisionShape("KitchenCollision", m_model, KdCollider::Type::TypeGround);
}

void C_Kitchen::PreUpdate()
{
}

void C_Kitchen::Update()
{
	UpdateMatrix();
}

void C_Kitchen::PostUpdate()
{
}

void C_Kitchen::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}

void C_Kitchen::UpdateMatrix()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotateMat = Math::Matrix::CreateRotationX(m_rotate);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * rotateMat * transMat;
}

void C_Kitchen::InitCollision()
{
	m_pCollider = std::make_unique<KdCollider>();
	
	m_pCollider->RegisterCollisionShape("KitchenCollision", m_model, KdCollider::Type::TypeGround);
}

void C_Kitchen::ImGui()
{
	if (ImGui::Button("Kitchen")) m_isDebugOpen = !m_isDebugOpen;

	if(m_isDebugOpen)
	{
		ImGui::DragFloat("posX", &m_pos.x,-0.01f,-640.0f, 640.0f);
		ImGui::DragFloat("posY", &m_pos.y,-0.01f, -360.0f, 360.0f);
		ImGui::DragFloat("posZ", &m_pos.z,-0.01f, -100.0f, 100.0f);
		ImGui::DragFloat("rotate", &m_rotate, -0.01f,0.0f, 360.0f);
		ImGui::DragFloat("scale", &m_scale, -0.01f,0.01f, 10.0f);

		ImGui::Text("pos : % .2f, % .2f, % .2f", m_pos.x, m_pos.y, m_pos.z);
		ImGui::Text("rotate : % .2f", m_rotate);
		ImGui::Text("scale : %.2f", m_scale);
	}
}
