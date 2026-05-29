#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Camera/Camera.h"
#include "../../Object/Tofu/Tofu.h"

GameScene::GameScene() { Init(); }

GameScene::~GameScene(){}

void GameScene::Event()
{
	/*if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}*/
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();
	//拡縮行列（S）
	Math::Matrix _mScale = Math::Matrix::CreateScale(1.0f);
	//回転行列（R）0～360度はディグリー角、変換後はラジアン角
	Math::Matrix _mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0.0f));
	//位置行列（T）　指定方法➀：Vector3型で渡す　指定方法➁：X・Y・Zの値を渡す
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(0.0f, 0.0f, -5.0f);
	//合成行列（SRT）== ワールド行列
	Math::Matrix _mWorld = _mScale * _mRotation * _mTrans;

	m_camera->SetCameraMatrix(_mWorld);

	//とうふ
	m_tofu = std::make_unique<C_Tofu>();
	m_tofu->Init();
	m_objList.push_back(std::move(m_tofu));
}
