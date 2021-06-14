#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Sound::Sound()
	: mXAudio2(nullptr)
	, mMasteringVoice(nullptr)
	, mSrc()
	, mOneShotSrc()
	, mHandle()
{
	mSrc.clear();
	mOneShotSrc.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Sound::~Sound()
{
	for (auto src : mOneShotSrc) {
		src.srcVoice->DestroyVoice();
		src.srcVoice = nullptr;
	}
	mOneShotSrc.clear();
	for (auto src : mSrc) {
		if (src.second.srcVoice) {
			src.second.srcVoice->DestroyVoice();
			src.second.srcVoice = nullptr;
		}
		if (src.second.wavFmtEx) {
			delete src.second.wavFmtEx;
			src.second.wavFmtEx = nullptr;
		}
		if (src.second.wavBuffer) {
			delete src.second.wavBuffer;
			src.second.wavBuffer = nullptr;
		}
	}
	mSrc.clear();
	if (mMasteringVoice) {
		mMasteringVoice->DestroyVoice();
		mMasteringVoice = nullptr;
	}
	if (mXAudio2) {
		mXAudio2->Release();
		mXAudio2 = nullptr;
	}
	CoUninitialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
/// @return ���� ����(true)
bool Sound::initialize()
{
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}
#if _DEBUG
	hr = XAudio2Create(&mXAudio2, XAUDIO2_DEBUG_ENGINE);
#else
	hr = XAudio2Create(&mXAudio2, NULL);
#endif
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("Xaudio2�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		CoUninitialize();
		return false;
	}
	hr = mXAudio2->CreateMasteringVoice(&mMasteringVoice);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("MasterVoice�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		CoUninitialize();
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �ǂݍ���
/// @brief ���݂�wav�t�@�C���̂ݑΉ��B��Xogg���ǂݍ��߂�悤�ɂ�����
/// @param aFileName �ǂݍ��݂����t�@�C���̃p�X
/// @return �ǂݍ��ݎ��s�i-1�j/ �����i�Ǘ��ԍ��j
int Sound::load(const char* const aFileName)
{
	const int handle = mHandle.update();

	if (!loadWaveFile(aFileName, handle)) {
		MessageBox(nullptr, TEXT(".wav�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return -1;
	}

	return handle;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aHandle �j���������T�E���h�̊Ǘ��ԍ�
void Sound::release(const int& aHandle)
{
	if (!mSrc.count(aHandle)) {
		return;
	}
	mHandle.release(aHandle);

	mSrc[aHandle].srcVoice->DestroyVoice();
	mSrc[aHandle].srcVoice = nullptr;
	mSrc.erase(aHandle);

	auto itr = mOneShotSrc.begin();
	while (itr != mOneShotSrc.end()) {
		auto src = *(itr);
		if (src.handle == aHandle) {
			XAUDIO2_VOICE_STATE state;
			src.srcVoice->GetState(&state);
			if (state.BuffersQueued == 0) {
				src.srcVoice->DestroyVoice();
				src.srcVoice = nullptr;
				itr = mOneShotSrc.erase(itr);
			} else {
				itr++;
			}
		} else {
			itr++;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �ʏ�Đ�
/// @brief �T�E���h�P�̂��Đ�����iBGM�p�j
/// @param aHandle �Đ��������T�E���h�̊Ǘ��ԍ�
void Sound::play(const int& aHandle)
{
	if (!mSrc.count(aHandle)) {
		return;
	}
	
	XAUDIO2_VOICE_STATE state;
	mSrc[aHandle].srcVoice->GetState(&state);
	// �L���[�Ƀo�b�t�@�[��ǉ�
	if (state.BuffersQueued == 0) {
		mSrc[aHandle].srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
	}
	// �Đ�
	mSrc[aHandle].srcVoice->Start();
}

//-------------------------------------------------------------------------------------------------
/// ���d�Đ�
/// @brief �T�E���h�̏I����҂����ɑ��d�Đ����\(SE�p)
/// @param aHandle �Đ��������T�E���h�̊Ǘ��ԍ�
/// @param aPlayPausingFlag �ꎞ��~���̃T�E���h���Đ������邩
void Sound::playOneShot(const int& aHandle, const bool& aPlayPausingFlag)
{
	if (!mSrc.count(aHandle)) {
		return;
	}

	// �������ꂽ�f�[�^�̒��Ɋ��ɏI�����Ă��镨������Δj������
	auto itr = mOneShotSrc.begin();
	while (itr != mOneShotSrc.end()) {
		auto src = *(itr);
		XAUDIO2_VOICE_STATE state;
		src.srcVoice->GetState(&state);
		if (state.BuffersQueued == 0) {
			src.srcVoice->DestroyVoice();
			src.srcVoice = nullptr;
			itr = mOneShotSrc.erase(itr);
		} else {
			itr++;
		}
	}

	// �\�[�X�{�C�X�𕡐�
	if (!aPlayPausingFlag) {
		OneShotSrcData data;
		data.handle = aHandle;
		mXAudio2->CreateSourceVoice(&data.srcVoice, mSrc[aHandle].wavFmtEx);
		mOneShotSrc.emplace_back(data);
		data.srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
	}

	// �Đ�
	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			XAUDIO2_VOICE_STATE state;
			src.srcVoice->GetState(&state);
			if (state.BuffersQueued == 0) {
				src.srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
			}
			src.srcVoice->Start();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ��~
/// @brief ���ɍĐ����鎞�͍ŏ�����n�܂�
/// @param aHandle ��~�������T�E���h�̊Ǘ��ԍ�
void Sound::stop(const int& aHandle)
{
	if (!mSrc.count(aHandle)) {
		return;
	}
	mSrc[aHandle].srcVoice->Stop(0, 0);
	mSrc[aHandle].srcVoice->FlushSourceBuffers();

	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			src.srcVoice->Stop(0, 0);
			src.srcVoice->FlushSourceBuffers();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �ꎞ��~
/// @brief ���ɍĐ�����Ƃ��͒�~�ʒu����ĊJ����
/// @param aHandle ��~�������T�E���h�̊Ǘ��ԍ�
void Sound::pause(const int& aHandle)
{
	if (!mSrc.count(aHandle)) {
		return;
	}
	mSrc[aHandle].srcVoice->Stop(0, 0);

	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			src.srcVoice->Stop(0, 0);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// .wav�`���̃t�@�C����ǂݍ���
/// @param aFileName �t�@�C����
/// @param aHandle �Ǘ��ԍ�
/// @return ���� �����itrue�j
bool Sound::loadWaveFile(const char* const aFileName, const int& aHandle)
{
	HMMIO hMmio = NULL;
	DWORD waveSize = 0;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFmt;

	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	hMmio = mmioOpenA((char*)aFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == NULL) {
		return false;
	}

	//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	MMRESULT mmr;
	mmr = mmioDescend(hMmio, &riffckInfo, NULL, 0);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmr = mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	//�t�H�[�}�b�g��ǂݍ���
	mmioRead(hMmio, (HPSTR)&pcmWaveFmt, sizeof(pcmWaveFmt));
	mSrc[aHandle].wavFmtEx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(mSrc[aHandle].wavFmtEx, &pcmWaveFmt, sizeof(pcmWaveFmt));
	mSrc[aHandle].wavFmtEx->cbSize = 0;
	mmr = mmioAscend(hMmio, &ckInfo, 0);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmr = mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}
	waveSize = ckInfo.cksize;

	// �\�[�X�{�C�X�쐬
	HRESULT hr = mXAudio2->CreateSourceVoice(&mSrc[aHandle].srcVoice, mSrc[aHandle].wavFmtEx);
	if (FAILED(hr)) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// �o�b�t�@�[�̐ݒ�
	mSrc[aHandle].wavBuffer = new BYTE[waveSize];
	mmioRead(hMmio, (HPSTR)mSrc[aHandle].wavBuffer, waveSize);
	mSrc[aHandle].buffer.pAudioData = mSrc[aHandle].wavBuffer;
	mSrc[aHandle].buffer.Flags = XAUDIO2_END_OF_STREAM;
	mSrc[aHandle].buffer.AudioBytes = waveSize;

	// ����
	mmioClose(hMmio, MMIO_FHOPEN);

	return true;
}

} // namespace
// EOF
