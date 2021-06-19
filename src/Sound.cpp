#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Sound::Sound()
	: mXAudio2(nullptr)
	, mMasteringVoice(nullptr)
	, mMainSrc()
	, mSubSrc()
	, mHandle()
{
	mMainSrc.clear();
	mSubSrc.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Sound::~Sound()
{
	for (auto sub : mSubSrc) {
		for (auto src : sub.second) {
			src->DestroyVoice();
			src = nullptr;
		}
	}
	mSubSrc.clear();
	mMainSrc.clear();
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
/// �f�X�g���N�^
Sound::SrcData::~SrcData()
{
	if (srcVoice) {
		srcVoice->DestroyVoice();
		srcVoice = nullptr;
	}
	if (wavFmtEx) {
		delete wavFmtEx;
		wavFmtEx = nullptr;
	}
	if (wavBuffer) {
		delete wavBuffer;
		wavBuffer = nullptr;
	}
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
int Sound::load(const LPCSTR aFileName)
{
	// �G���[�`�F�b�N
	if (!mXAudio2) {
		return -1;
	}

	const auto handle = mHandle.update();
	if (!loadWaveFile(aFileName, handle)) {
		MessageBox(nullptr, TEXT(".wav�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mHandle.release(handle);
		return -1;
	}

	return handle;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aHandle �j���������T�E���h�̊Ǘ��ԍ�
void Sound::release(const int& aHandle)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	// �n���h���j��
	mHandle.release(aHandle);

	// �\�[�X�j��
	mMainSrc.erase(aHandle);
	for (auto src : mSubSrc[aHandle]) {
		src->DestroyVoice();
		src = nullptr;
	}
	mSubSrc.erase(aHandle);
}

//-------------------------------------------------------------------------------------------------
/// �ʏ�Đ�
/// @brief �T�E���h�P�̂��Đ�����iBGM�p�j
/// @param aHandle �Đ��������T�E���h�̊Ǘ��ԍ�
void Sound::play(const int& aHandle)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	XAUDIO2_VOICE_STATE state;
	mMainSrc[aHandle].srcVoice->GetState(&state);
	// �L���[�Ƀo�b�t�@�[��ǉ�
	if (state.BuffersQueued == 0) {
		mMainSrc[aHandle].srcVoice->SubmitSourceBuffer(&mMainSrc[aHandle].buffer);
	}
	// �Đ�
	mMainSrc[aHandle].srcVoice->Start();
}

//-------------------------------------------------------------------------------------------------
/// ���d�Đ�
/// @brief �T�E���h�̏I����҂����ɑ��d�Đ����\(SE�p)
/// @param aHandle �Đ��������T�E���h�̊Ǘ��ԍ�
/// @param aPlayPausingFlag �ꎞ��~���̃T�E���h���Đ������邩
void Sound::playOneShot(const int& aHandle, const bool& aPlayPausingFlag)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	// �������ꂽ�f�[�^�̏󋵂𒲂ׂ�
	for (auto sub : mSubSrc) {
		XAUDIO2_VOICE_STATE state;
		auto itr = mSubSrc[sub.first].begin();
		while (itr != mSubSrc[sub.first].end()) {
			auto src = (*itr);
			src->GetState(&state);
			if (state.BuffersQueued == 0) {
				// �Đ��I�����Ă�����j��
				src->DestroyVoice();
				src = nullptr;
				itr = mSubSrc[sub.first].erase(itr);
			} else {
				itr++;
			}
		}
	}

	if (!aPlayPausingFlag) {
		// �\�[�X�{�C�X�𕡐�����
		IXAudio2SourceVoice* src;
		mXAudio2->CreateSourceVoice(&src, mMainSrc[aHandle].wavFmtEx);
		src->SubmitSourceBuffer(&mMainSrc[aHandle].buffer);
		// �{�����[�����R�s�[
		float volume;
		mMainSrc[aHandle].srcVoice->GetVolume(&volume);
		src->SetVolume(volume);
		// vector�ɒǉ�
		mSubSrc[aHandle].emplace_back(src);
	}

	// �Đ�
	for (auto src : mSubSrc[aHandle]) {
		src->Start();
	}
}

//-------------------------------------------------------------------------------------------------
/// ��~
/// @brief ���ɍĐ����鎞�͍ŏ�����n�܂�
/// @param aHandle ��~�������T�E���h�̊Ǘ��ԍ�
void Sound::stop(const int& aHandle)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ��~
	mMainSrc[aHandle].srcVoice->Stop(0, 0);
	mMainSrc[aHandle].srcVoice->FlushSourceBuffers();
	for (auto src : mSubSrc[aHandle]) {
		src->Stop(0, 0);
		src->FlushSourceBuffers();
	}
}

//-------------------------------------------------------------------------------------------------
/// �ꎞ��~
/// @brief ���ɍĐ�����Ƃ��͒�~�ʒu����ĊJ����
/// @param aHandle ��~�������T�E���h�̊Ǘ��ԍ�
void Sound::pause(const int& aHandle)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// �ꎞ��~
	mMainSrc[aHandle].srcVoice->Stop(0, 0);
	for (auto src : mSubSrc[aHandle]) {
		src->Stop(0, 0);
	}
}

//-------------------------------------------------------------------------------------------------
/// �{�����[����ύX����
/// @param aHandle �ύX�������T�E���h�̊Ǘ��ԍ�
/// @param aVolume �ݒ肷�鉹�ʁi0~2�j
void Sound::setVolume(const int& aHandle, float aVolume)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// �{�����[����ύX����
	aVolume = Math::Clamp(aVolume, 0.0f, 2.0f);
	float nowVolume;
	mMainSrc[aHandle].srcVoice->GetVolume(&nowVolume);

	if (nowVolume != aVolume) {
		mMainSrc[aHandle].srcVoice->SetVolume(aVolume);
		for (auto src : mSubSrc[aHandle]) {
			src->SetVolume(aVolume);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ���[�v�̐ݒ������
/// @param aHandle �ݒ肵�����T�E���h�̊Ǘ��ԍ�
/// @param aLoopFlag ���[�v�ݒ� ���[�v������itrue�j���[�v�����ifalse�j
/// @param aLoopCount ���[�v���i0 = �������[�v�j
void Sound::setLoop(const int& aHandle, const bool& aLoopFlag, const int& aLoopCount)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ���[�v�ݒ�
	if (aLoopFlag) {
		if (aLoopCount == 0) {
			// �������[�v
			mMainSrc[aHandle].buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		} else {
			// �񐔕t�����[�v
			mMainSrc[aHandle].buffer.LoopCount = aLoopCount;
		}
	} else if (mMainSrc[aHandle].buffer.LoopCount != 0) {
		// ���[�v����
		mMainSrc[aHandle].buffer.LoopCount = 0;
		mMainSrc[aHandle].srcVoice->ExitLoop();
		for (auto src : mSubSrc[aHandle]) {
			src->ExitLoop();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ���[�v�̈ʒu�̐ݒ������
/// @param aHandle �ݒ肵�����T�E���h�̊Ǘ��ԍ�
/// @param aBeginPos �J�n�T���v���ʒu�i0 = �ݒ肵�Ȃ��j
/// @param aEndPos �I���T���v���ʒu�i0 = �ݒ肵�Ȃ��j
void Sound::setLoopPos(const int& aHandle, const UINT32& aBeginPos, const UINT32& aEndPos)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ���[�v�ʒu�ݒ�
	if (aBeginPos != 0) {
		mMainSrc[aHandle].buffer.LoopBegin = aBeginPos;
	}
	if (aEndPos != 0 || aBeginPos < aEndPos) {
		mMainSrc[aHandle].buffer.LoopLength = aEndPos - aBeginPos;
	}
}

//-------------------------------------------------------------------------------------------------
/// �Đ��J�n�ʒu��ݒ肷��
/// @param aHandle �ݒ肵�����T�E���h�̊Ǘ��ԍ�
/// @param aBeginPos �J�n�T���v���ʒu
void Sound::setBeginPos(const int& aHandle, const UINT32& aBeginPos)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// �Đ��J�n�ʒu�ݒ�
	mMainSrc[aHandle].buffer.PlayBegin = aBeginPos;
}

//-------------------------------------------------------------------------------------------------
/// �Đ������ǂ������ׂ�
/// @param aHandle ���ׂ����T�E���h�̊Ǘ��ԍ�
/// @return ���� �Đ����itrue�j
bool Sound::checkIsPlaying(const int& aHandle)
{
	// �G���[�`�F�b�N
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return false;
	}
	// �Đ��������ׂ�
	XAUDIO2_VOICE_STATE state;
	mMainSrc[aHandle].srcVoice->GetState(&state);
	if (state.BuffersQueued > 0) {
		return true;
	}
	for (auto src : mSubSrc[aHandle]) {
		src->GetState(&state);
		if (state.BuffersQueued > 0) {
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/// .wav�`���̃t�@�C����ǂݍ���
/// @param aFileName �t�@�C����
/// @param aHandle �Ǘ��ԍ�
/// @return ���� �����itrue�j
bool Sound::loadWaveFile(const LPCSTR aFileName, const int& aHandle)
{
	HMMIO hMmio = NULL;
	DWORD wavSize = 0;
	MMCKINFO ckInfo = {};
	MMCKINFO riffckInfo = {};
	PCMWAVEFORMAT pcmWavFmt = {};

	// .wav�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	hMmio = mmioOpenA((char*)aFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == NULL) {
		return false;
	}

	// �t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
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

	// �t�H�[�}�b�g��ǂݍ���
	mmioRead(hMmio, (HPSTR)&pcmWavFmt, sizeof(pcmWavFmt));
	mMainSrc[aHandle].wavFmtEx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(mMainSrc[aHandle].wavFmtEx, &pcmWavFmt, sizeof(pcmWavFmt));
	mMainSrc[aHandle].wavFmtEx->cbSize = 0;
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
	wavSize = ckInfo.cksize;

	// �\�[�X�{�C�X�쐬
	HRESULT hr = mXAudio2->CreateSourceVoice(&mMainSrc[aHandle].srcVoice, mMainSrc[aHandle].wavFmtEx);
	if (FAILED(hr)) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// �o�b�t�@�[�̐ݒ�
	mMainSrc[aHandle].wavBuffer = new BYTE[wavSize];
	mmioRead(hMmio, (HPSTR)mMainSrc[aHandle].wavBuffer, wavSize);
	mMainSrc[aHandle].buffer.pAudioData = mMainSrc[aHandle].wavBuffer;
	mMainSrc[aHandle].buffer.Flags = XAUDIO2_END_OF_STREAM;
	mMainSrc[aHandle].buffer.AudioBytes = wavSize;

	// ����
	mmioClose(hMmio, MMIO_FHOPEN);

	return true;
}

} // namespace
// EOF
