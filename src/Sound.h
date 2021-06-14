#pragma once

//-------------------------------------------------------------------------------------------------
#include <xaudio2.h>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

class Sound : public Singleton<Sound>
{
public:
	Sound();
	~Sound();

	bool initialize();
	bool load(const char* const aFileName);

private:
	IXAudio2* mXAudio2;
	IXAudio2MasteringVoice* mMasteringVoice;
	IXAudio2SourceVoice* mSourceVoice;

};

} // namespace
// EOF
