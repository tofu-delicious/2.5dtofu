//oundManager.h
#pragma once

class C_SoundManager
{
public:

	enum class SoundType
	{
		BGM,
		SE,
	};

	// グループ音量を設定（0.0～1.0）
	void GroupVolume(SoundType a_type, float a_vol);

	// BGM再生（再生中インスタンスを保持し、現在のBGM音量を適用する）
	std::shared_ptr<KdSoundInstance> PlayBGM(std::string_view a_fileName, bool a_loop = true);

	// SE再生（鳴らす瞬間に現在のSE音量を適用する）
	std::shared_ptr<KdSoundInstance> PlaySE(std::string_view a_fileName);

	// グループ音量を取得（0.0～1.0）
	float GetSEVolume()const { return m_seVolume; }
	float GetBGMVolume()const { return m_bgmVolume; }

private:

	C_SoundManager() {}
	~C_SoundManager() {}

	C_SoundManager(const C_SoundManager&) = delete;
	void operator=(const C_SoundManager&) = delete;

	float m_bgmVolume = 0.1f;
	float m_seVolume = 0.1f;

	// 現在再生中のBGM（音量変更時に即反映するため保持）
	std::shared_ptr<KdSoundInstance> m_bgmInstance = nullptr;

public:

	static C_SoundManager& Instance()
	{
		static C_SoundManager instance;
		return instance;
	}
};