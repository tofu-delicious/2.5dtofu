//Tofu.cpp
#include "Tofu.h"
#include "../../Asset/AssetManager.h"

void C_Tofu::Init()
{
	//ロード
	m_model = ASSETMANAGER.GetModel("Tofu");

	m_mWorld = Math::Matrix::Identity;

	//============= 変数初期化 ===============
	m_isSpaceKey = false;
	m_isJumping = false;

	m_pos = {};
	m_move = {};
	m_color = { 1,0.0,1 };
	m_moveSpeed = 0.1f;
	m_gravity = 0.0f;
}

void C_Tofu::PreUpdate()
{
	//入力取得などUpdate関数の前に必要な処理
	MoveTofu();
}

void C_Tofu::Update()
{
	//リアルタイムで更新する
	CommitPos();	//座標確定処理

	UpdateMatrix();
}

void C_Tofu::PostUpdate()
{
	//全オブジェクトが動き終わった後の処理
	
}

void C_Tofu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void C_Tofu::MoveTofu()
{
	m_move.x = 0.0f;

	bool currentSpace = GetAsyncKeyState(VK_SPACE) & 0x8000;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_move.x = m_moveSpeed;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_move.x = -(m_moveSpeed);
	}
	//スペースキーの連打制御 & ジャンプしていない
	if (currentSpace && !m_isSpaceKey && !m_isJumping)
	{
		m_move.y = JUMP_POW;
		m_gravity = 0.0f;	//ジャンプ時に重力をリセット
		m_isJumping = true;
	}

	m_gravity += GRAVITY_INCREMENT;
	m_move.y -= m_gravity;

	m_isSpaceKey = currentSpace;
}

void C_Tofu::CommitPos()
{
	m_pos += m_move;
	
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
		m_gravity = 0.0f;
		m_isJumping = false;
	}
}

void C_Tofu::UpdateMatrix()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}
