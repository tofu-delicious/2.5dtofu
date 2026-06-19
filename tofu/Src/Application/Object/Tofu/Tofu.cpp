//Tofu.cpp
#include "Tofu.h"
#include "../../Asset/AssetManager.h"
#include "../../Scene/SceneManager.h"

void C_Tofu::Init()
{
	//=========== デバッグ表示 ===============
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//=========== モデルロード ===============
	m_model = C_AssetManager::Instance().GetModel("Tofu");

	m_mWorld = Math::Matrix::Identity;

	//============= 変数初期化 ===============
	m_isSpaceKey = false;
	m_isJumping = false;

	m_pos = INITIAL_POS;
	m_color = { 1,0.0,1 };
	m_gravity = 0.01f;

	//============= 初期化処理 ===============
	UpdateMatrix();
}
void C_Tofu::PreUpdate()
{
	//入力取得などUpdate関数の前に必要な処理
	JumpTofu();
}

void C_Tofu::Update()
{
	//リアルタイムで更新する
}

void C_Tofu::PostUpdate()
{
	UpdateMatrix();

	CheckRay();
	CheckSphere();
}

void C_Tofu::DrawLit()
{

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void C_Tofu::JumpTofu()
{
	bool currentSpace = GetAsyncKeyState(VK_SPACE) & 0x8000;

	//地面にいるときだけチャージ & ジャンプ受付
	if (!m_isJumping)
	{
		//押している間カウントを増やす（上限に頭打ち）
		if (currentSpace)
		{
			m_chargeCount++;
			if (m_chargeCount > MAX_CHARGE) { m_chargeCount = MAX_CHARGE; }
		}

		//離した瞬間にジャンプ発動（前フレーム押下 && 今フレーム離した）
		if (!currentSpace && m_isSpaceKey && m_chargeCount > 0)
		{
			//チャージ量（0.0 ~ 1.0）からジャンプ力を線形補間
			float chargeRatio = m_chargeCount / static_cast<float>(MAX_CHARGE);
			float jumpPow = MIN_JUMP_POW_Y + (MAX_JUMP_POW_Y - MIN_JUMP_POW_Y) * chargeRatio;

			m_gravity = -jumpPow;	//上向きの初速を与える
			m_isJumping = true;
			m_chargeCount = 0;		//チャージをリセット
		}
	}

	m_isSpaceKey = currentSpace;

	//=========== 縦の移動（重力） ============
	m_pos.y -= m_gravity;
	m_gravity += GRAVITY_INCREMENT;

	//=========== 横の移動（前進） ============
	if (m_isJumping)
	{
		//ジャンプ中は前に進む
		m_pos.x += JUMP_FORWARD;

		//前進と同時に定位置（HOME_X）へ徐々に引き戻す
		if (m_pos.x > HOME_X)
		{
			m_pos.x -= RETURN_SPEED;
		}
	}
	else
	{
		//念のためジャンプしていない状態でも定位置に固定
		m_pos.x = HOME_X;
	}
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
	float enableStepHigh = 0.1f;	//許容する段差の高さ

	ray.m_pos = m_pos + Math::Vector3{ 0.0f,enableStepHigh,0.0f };				//0.2fの段差を許容する
	ray.m_dir = { 0,-1,0 };														//レイの方向（真下）
	ray.m_range = m_gravity + enableStepHigh; /*> MIN_RAY_RANGE ? (m_gravity + enableStepHigh) : MIN_RAY_RANGE;	*///レイの長さ
	ray.m_type = KdCollider::TypeGround;										//地面に配置されているオブジェクトと判定を行う

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
		m_gravity = 0.0f;					//m_gravityが0.0fのときは地面
		m_isJumping = false;
	}
}

void C_Tofu::CheckSphere()
{
	//============ 球初期化処理 ================
	KdCollider::SphereInfo sphere;			//球判定用の変数を用意
	sphere.m_sphere.Center = m_pos;			//球の中心座標を設定
	sphere.m_sphere.Radius = 0.1f;			//球の半径を設定
	sphere.m_type = KdCollider::TypeBump;	//当たり判定をしたいタイプを指定

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

		OnHit();
	}
}

void C_Tofu::OnHit()
{
	m_isExpired = true;
}

void C_Tofu::ImGui()
{
	//Sameline()：次のウィジェットを横方向に位置付ける
	ImGui::SameLine();

	if (ImGui::Button("Tofu")) m_isDebugOpen = !m_isDebugOpen;

	if(m_isDebugOpen)
	{
		ImGui::Text("m_pos.x : %.2f", m_pos.x);
		ImGui::Text("m_pos.y : %.2f", m_pos.y);
		ImGui::Text("m_pos.z : %.2f", m_pos.z);
	}
}
