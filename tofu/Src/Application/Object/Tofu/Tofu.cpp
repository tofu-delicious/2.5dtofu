//Tofu.cpp
#include "Tofu.h"
#include "../../Asset/AssetManager.h"
#include "../../Scene/SceneManager.h"

void C_Tofu::Init()
{
	//=========== デバッグ表示 ===============
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//=========== モデルロード ===============
	m_model = ASSETMANAGER.GetModel("Tofu");

	m_mWorld = Math::Matrix::Identity;

	//============= 変数初期化 ===============
	m_isSpaceKey = false;
	m_isJumping = false;

	m_pos = {0.0f,2.0f,0.0f};
	m_move = {};
	m_color = { 1,0.0,1 };
	m_moveSpeed = 0.05f;
	m_gravity = 0.0f;

	//============= 初期化処理 ===============
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
	CheckRay();

	//CheckSphere();
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
	
	/*if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
		m_gravity = 0.0f;
		m_isJumping = false;
	}*/
}

void C_Tofu::UpdateMatrix()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void C_Tofu::CheckRay()
{
	//============= レイ初期化 ===============
	KdCollider::RayInfo ray;
	float enableStepHigh = 0.2f;

	ray.m_pos = m_pos + Math::Vector3{0.0f,enableStepHigh,0.0f};	//0.2fの段差を許容する
	ray.m_dir = { 0,-1,0 };											//レイの方向（真下）
	ray.m_range = abs(m_move.y) + enableStepHigh;					//レイの長さ
	ray.m_type = KdCollider::TypeGround;							//地面に配置されているオブジェクトと判定を行う

	//=========== レイデバッグ表示 ===========
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//============= 衝突物リスト =============
	std::list<KdCollider::CollisionResult> retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	//  リストからTofuと近いオブジェクトを探索
	float maxOverLap = 0.0f;
	Math::Vector3 hitPos;
	bool isHit = false;

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			isHit = true;
		}
	}

	//============== 衝突処理 ================
	if (isHit)
	{
		m_pos = hitPos;
		m_pos.y -= enableStepHigh;
		m_pos.y += 0.2f;
		m_move.y = 0.0f;
		m_gravity = 0.0f;
		m_isJumping = false;
	}
}

void C_Tofu::CheckSphere()
{
	//============ 球初期化処理 ================
	KdCollider::SphereInfo sphere;			//球判定用の変数を用意
	sphere.m_sphere.Center = m_pos;			//球の中心座標を設定
	sphere.m_sphere.Radius = 0.3f;			//球の半径を設定
	sphere.m_type = KdCollider::TypeGround;	//当たり判定をしたいタイプを指定

	//============ デバッグ表示 ================
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//============ 衝突物リスト ================
	std::list<KdCollider::CollisionResult> retSphereList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}

	//衝突物リストから一番近距離のオブジェクトを探索
	float maxOverLap = 0.0f;
	bool isHit = false;
	Math::Vector3 hitDir;

	for (auto& ret : retSphereList)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}

	//============== 衝突処理 ================
	if (isHit)
	{
		hitDir.z = 0.0f;

		//方向ベクトルは長さ1
		hitDir.Normalize();

		m_pos += hitDir * maxOverLap;
	}
}

void C_Tofu::ImGui()
{
	if (ImGui::Begin("Log Window"))  // ★ウィンドウを開く
	{
		ImGui::Text("m_pos.y : %.2f", m_pos.y);
	}
	ImGui::End();  // ★必ずBeginとペアで呼ぶ
}
