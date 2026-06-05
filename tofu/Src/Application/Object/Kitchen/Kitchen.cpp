//Kitchen.cpp
#include "Kitchen.h"
#include "../../Asset/AssetManager.h"

void C_Kitchen::Init()
{
	m_model = ASSETMANAGER.GetModel("Kitchen");

	//初期座標はZ座標を-4の位置にする
	m_pos = INITIAL_POS;
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

void C_Kitchen::ImGui()
{
	if (ImGui::Begin("Log Window"))  // ★ウィンドウを開く
	{
		if (ImGui::Button("Kitchen")) m_isDebugOpen = !m_isDebugOpen;

		if(m_isDebugOpen)
		{
			ImGui::SliderFloat("posX", &m_pos.x, -640.0f, 640.0f);
			ImGui::SliderFloat("posY", &m_pos.y, -360.0f, 360.0f);
			ImGui::SliderFloat("posZ", &m_pos.z, -100.0f, 100.0f);
			ImGui::SliderFloat("rotate", &m_rotate, 0.0f, 360.0f);
			ImGui::SliderFloat("scale", &m_scale, 0.01f, 10.0f);

			ImGui::Text("pos : % .2f, % .2f, % .2f, m_pos.x", m_pos.y, m_pos.z);
			ImGui::Text("rotate : % .2f", m_rotate);
			ImGui::Text("scale : %.2f", m_scale);
		}
	}
	ImGui::End();  // ★必ずBeginとペアで呼ぶ
}
