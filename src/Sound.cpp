#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
Sound::Sound()
	: mXAudio2(nullptr)
	, mMasteringVoice(nullptr)
	, mSourceVoice(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
Sound::~Sound()
{
	if (mXAudio2) {
		mXAudio2->Release();
		mXAudio2 = nullptr;
	}
	if (mMasteringVoice) {
		mMasteringVoice->DestroyVoice();
		mMasteringVoice = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
bool Sound::initialize()
{
	HRESULT hr;

	hr = XAudio2Create(&mXAudio2);
	if (FAILED(hr)) {
		return false;
	}
	hr = mXAudio2->CreateMasteringVoice(&mMasteringVoice);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sound::load(const char* const aFileName)
{
	return true;
}

} // namespace
// EOF
