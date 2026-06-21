//SoundManager.cpp
#include "SoundManager.h"

void C_SoundManager::GroupVolume(SoundType a_type, float a_vol)
{
	// 0.0～1.0にクランプ
	if (a_vol < 0.0f) a_vol = 0.0f;
	if (a_vol > 1.0f) a_vol = 1.0f;

	if (a_type == SoundType::BGM)
	{
		m_bgmVolume = a_vol;

		// 再生中のBGMがあれば即反映
		if (m_bgmInstance)
		{
			m_bgmInstance->SetVolume(m_bgmVolume);
		}
	}
	else
	{
		m_seVolume = a_vol;
	}
}

std::shared_ptr<KdSoundInstance> C_SoundManager::PlayBGM(std::string_view a_fileName, bool a_loop)
{
	m_bgmInstance = KdAudioManager::Instance().Play(a_fileName, a_loop);

	if (m_bgmInstance)
	{
		m_bgmInstance->SetVolume(m_bgmVolume);
	}

	return m_bgmInstance;
}

std::shared_ptr<KdSoundInstance> C_SoundManager::PlaySE(std::string_view a_fileName)
{
	auto se = KdAudioManager::Instance().Play(a_fileName, false);

	if (se)
	{
		se->SetVolume(m_seVolume);
	}

	return se;
}