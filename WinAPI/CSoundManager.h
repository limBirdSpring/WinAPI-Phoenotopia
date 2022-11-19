#pragma once

class CCore;
class CSound;

class CSoundManager : public SingleTon<CSoundManager>
{
	friend SingleTon<CSoundManager>;
	friend CCore;
private:
	CSoundManager();
	virtual ~CSoundManager();

private:
	FMOD::System* m_pSystem;	// 사운드 시스템

	float m_fStartVolume;
	float m_fEndVolume;
	float m_fTime;
	float m_fFadeSpeed;
	float m_fFadeTime;
	CSound* pFadeSound;

public:
	System* GetSystem();

	void Play(CSound* pSound, float volume = 1.f, bool loop = false);
	void Stop(CSound* pSound);
	void Stop();

	void Pause(CSound* pSound);
	void Resume(CSound* pSound);
	void FadeOut(CSound* pSound, float time, float volume);
	void FadeIn(CSound* pSound, float time, float volume = 1.f, bool loop = false);
	float GetVolume(CSound* pSound);
	void SetVolume(CSound* pSound, float volume);

private:
	void Init();
	void Update();
	void Release();
};

#define SOUND	CSoundManager::GetInstance()