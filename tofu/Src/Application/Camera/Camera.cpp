//Camera.cpp
#include "Camera.h"

C_Camera::C_Camera(){}

C_Camera::~C_Camera(){}

void C_Camera::Init()
{
	m_spCamera = std::make_unique<KdCamera>();

	m_spCamera->SetCameraMatrix(Math::Matrix::Identity);

	m_pos = { 0.0f,1.0f,-5.0f };
}

void C_Camera::Update()
{
	//拡縮行列（S）
	Math::Matrix _mScale = Math::Matrix::CreateScale(1.0f);
	//回転行列（R）0～360度はディグリー角、変換後はラジアン角
	Math::Matrix _mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(10.0f));
	//位置行列（T）　指定方法➀：Vector3型で渡す　指定方法➁：X・Y・Zの値を渡す
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos);
	//合成行列（SRT）== ワールド行列
	Math::Matrix _mWorld = _mScale * _mRotation * _mTrans;

	m_spCamera->SetCameraMatrix(_mWorld);
}

void C_Camera::SetShader()
{
	m_spCamera->SetToShader();
}
