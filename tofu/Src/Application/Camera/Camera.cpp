//Camera.cpp
#include "Camera.h"
#include "../Object/Tofu/Tofu.h"

C_Camera::C_Camera(){}

C_Camera::~C_Camera(){}

void C_Camera::Init(const Math::Vector3& a_pos, float a_rotate)
{
	m_spCamera = std::make_shared<KdCamera>();

	m_spCamera->SetCameraMatrix(Math::Matrix::Identity);

	m_pos = a_pos;
	m_rotate = a_rotate;
}

void C_Camera::Update()
{
	Math::Vector3 tofuPos;
	if (!m_tofu.expired())tofuPos = m_tofu.lock()->GetPos();

	//拡縮行列（S）
	Math::Matrix _mScale = Math::Matrix::CreateScale(1.0f);
	//回転行列（R）0～360度はディグリー角、変換後はラジアン角
	Math::Matrix _mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotate));
	//位置行列（T）　指定方法➀：Vector3型で渡す　指定方法➁：X・Y・Zの値を渡す
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos + Math::Vector3{tofuPos.x + 0.5f,0.0f,0.0f});
	//合成行列（SRT）== ワールド行列
	Math::Matrix _mWorld = _mScale * _mRotation * _mTrans;

	m_spCamera->SetCameraMatrix(_mWorld);
}

void C_Camera::SetShader()
{
	m_spCamera->SetToShader();
}

void C_Camera::ImGui()
{
	if (ImGui::Button("Camera")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::SliderFloat("posX", &m_pos.x, -640.0f, 640.0f);
		ImGui::SliderFloat("posY", &m_pos.y, -360.0f, 360.0f);
		ImGui::SliderFloat("posZ", &m_pos.z, -100.0f, 100.0f);
		ImGui::SliderFloat("rotate", &m_rotate, -360.0f, 360.0f);

		ImGui::Text("pos : % .2f, % .2f, % .2f", m_pos.x, m_pos.y, m_pos.z);
	}
}
