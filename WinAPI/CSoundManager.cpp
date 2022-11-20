#include "framework.h"
#include "CSoundManager.h"

#include "CSound.h"
#include "CTimeManager.h"

CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
	m_fStartVolume = 0;
	m_fEndVolume =0;
	m_fFadeSpeed = 0;
	m_fFadeTime = 0;
	m_fTime = 0;
	pFadeSound = nullptr;
}

CSoundManager::~CSoundManager()
{
}

System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::Play(CSound* pSound, float volume, bool loop)
{
	FMOD_RESULT result;

	FMOD_MODE mode;
	result = pSound->m_pSound->getMode(&mode);
	assert(FMOD_OK == result && L"Get mode failed");

	if (mode & FMOD_LOOP_NORMAL && (pSound->IsPlaying() || pSound->IsPaused()))
	{
		result = pSound->m_pChannel->stop();
		assert(FMOD_OK == result && L"Stop sound failed");
	}

	if (loop)
		result = pSound->m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		result = pSound->m_pSound->setMode(FMOD_LOOP_OFF);

	assert(FMOD_OK == result && L"Set Loop failed");

	result = m_pSystem->playSound(pSound->m_pSound, nullptr, false, &(pSound->m_pChannel));
	assert(FMOD_OK == result && L"Play sound failed");

	result = pSound->m_pChannel->setVolume(volume);
	assert(FMOD_OK == result && L"Set volume failed");
}

void CSoundManager::Stop(CSound* pSound)
{
	if (!pSound->IsPlaying())
		return;

	FMOD_RESULT result = pSound->m_pChannel->stop();
	assert(FMOD_OK == result && L"Stop sound failed");
}

void CSoundManager::Stop()
{

}


void CSoundManager::Pause(CSound* pSound)
{
	if (pSound->IsPaused())
		return;

	FMOD_RESULT result = pSound->m_pChannel->setPaused(true);
	assert(FMOD_OK == result && L"SetPaused failed");
}

void CSoundManager::Resume(CSound* pSound)
{
	if (!pSound->IsPaused())
		return;

	FMOD_RESULT result = pSound->m_pChannel->setPaused(true);
	assert(FMOD_OK == result && L"Resume failed");
}

void CSoundManager::FadeOut(CSound* pSound, float time, float volume)
{
	if (!pSound->IsPlaying())
		return;

	pSound->m_pChannel->getVolume(&m_fStartVolume); //원래 볼륨 얻기

	m_fFadeSpeed = (m_fStartVolume - volume) / (time / DT);
	
	m_fEndVolume = volume;
	pFadeSound = pSound;
	m_fFadeTime = time;
	m_fTime = 0;

	
}

void CSoundManager::FadeIn(CSound* pSound, float time, float volume, bool loop)
{
	Play(pSound, 0.1f, loop);
	FadeOut(pSound, time, volume);
}

float CSoundManager::GetVolume(CSound* pSound)
{
	float volume;
	pSound->m_pChannel->getVolume(&volume);
	return volume;
}

void CSoundManager::SetVolume(CSound* pSound, float volume)
{
	pSound->m_pChannel->setVolume(volume);
}

void CSoundManager::SoundAllStop()
{
	
}

void CSoundManager::Init()
{
	// 사운드 시스템 생성
	FMOD_RESULT result;
	result = System_Create(&m_pSystem);
	assert(FMOD_OK == result && L"Create sound system falied");

	result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(FMOD_OK == result && L"Init sound system falied");
}

void CSoundManager::Update()
{
	FMOD_RESULT result = m_pSystem->update();
	assert(FMOD_OK == result && L"Update sound system falied");

	if (pFadeSound != nullptr)//페이드
	{
		m_fStartVolume -= m_fFadeSpeed;
		pFadeSound->m_pChannel->setVolume(m_fStartVolume);
		
		m_fTime += DT;

		if (m_fStartVolume <= 0.1)
		{
			pFadeSound->m_pChannel->stop();
			pFadeSound = nullptr;
		}

		if (m_fTime > m_fFadeTime)
		{
			m_fFadeTime = 0;
			pFadeSound = nullptr;
		}
	}

}

void CSoundManager::Release()
{
	if (nullptr != m_pSystem)
	{
		m_pSystem->release();
		m_pSystem->close();
	}
}
