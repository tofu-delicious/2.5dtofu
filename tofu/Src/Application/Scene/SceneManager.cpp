#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "SettingScene/SettingScene.h"
#include "GameScene/GameScene.h"
#include "PauseScene/PauseScene.h"
#include "ResultScene/ResultScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	//オーバーレイ解除の予約が有効なら解除処理を行う
	if (m_isPopOverlayReserved)
	{
		m_overlayScene = nullptr;
		m_isPopOverlayReserved = false;
	}

	//Overlayがあれば優先的に更新
	if (m_overlayScene)
		m_overlayScene->PreUpdate();
	else
		m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	if (m_overlayScene)
		m_overlayScene->Update();
	else
		m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	if (m_overlayScene)
		m_overlayScene->PostUpdate();
	else
		m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();

	//Overlayは重ねて表示するため、両方描画する
	if (m_overlayScene)
		m_overlayScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();

	if (m_overlayScene)
		m_overlayScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();

	if (m_overlayScene)
		m_overlayScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

void SceneManager::PushOverlay(SceneType _nextOverlay)
{
	//シーン切替
	switch (_nextOverlay)
	{
	case SceneType::Setting:
		m_overlayScene = std::make_shared<C_SettingScene>();
		break;
	case SceneType::Pause:
		m_overlayScene = std::make_shared<C_PauseScene>();
		break;
	case SceneType::Result:
		m_overlayScene = std::make_shared<C_ResultScene>();
		break;
	}

	m_overlaySceneType = _nextOverlay;
}

void SceneManager::PopOverlay()
{
	m_isPopOverlayReserved = true;	//即座にオーバーレイ画面を消さず、予約だけにする
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;
}
