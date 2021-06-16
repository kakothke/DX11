#pragma once

//-------------------------------------------------------------------------------------------------
#include <xaudio2.h>
#include <unordered_map>
#include "Singleton.h"
#include "Handle.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �T�E���h����
class Sound : public Singleton<Sound>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Sound();
	~Sound();
	//@}

	/// @name ����������
	//@{
	bool initialize();
	//@}

	/// @name �ǂݍ���/�j��
	//@{
	int load(const char* const aFileName);
	void release(const int& aHandle);
	//@}

	/// @name �T�E���h����
	//@{
	/// �ʏ�Đ�
	void play(const int& aHandle);
	/// ���d�Đ�
	void playOneShot(const int& aHandle, const bool& aPlayPausingFlag = false);
	/// ��~
	void stop(const int& aHandle);
	/// �ꎞ��~
	void pause(const int& aHandle);
	/// �{�����[����ݒ肷��
	void setVolume(const int& aHandle, float aVolume);
	/// �p����ݒ肷��
	void setPan(const int& aHandle, float aPan);
	/// ���[�v�̐ݒ������
	void setLoop(const int& aHandle, const bool& aLoopFlag = true, const int& aLoopCount = 0);
	/// ���[�v�̈ʒu�̐ݒ������
	void setLoopPos(const int& aHandle, const UINT32& aBeginPos, const UINT32& aEndPos = 0);
	/// �Đ��J�n�ʒu��ݒ肷��
	void setBeginPos(const int& aHandle, const UINT32& aBeginPos);
	/// �Đ������ǂ������ׂ�
	bool checkIsPlaying(const int& aHandle);
	//@}

private:
	/// @name ��������
	//@{
	bool loadWaveFile(const char* const aFileName, const int& aHandle);
	//@}

	/// @name �����\����
	//@{
	/// �T�E���h�\�[�X
	struct SrcData
	{
		/// �\�[�X�{�C�X
		IXAudio2SourceVoice* srcVoice;
		/// �\�[�X�o�b�t�@�[
		XAUDIO2_BUFFER buffer = {};
		/// Wave�t�H�[�}�b�g
		WAVEFORMATEX* wavFmtEx;
		/// Wave�o�b�t�@�[
		BYTE* wavBuffer;
	};
	/// ���d�Đ��p�\�[�X
	struct OneShotSrcData
	{
		/// �\�[�X�{�C�X
		IXAudio2SourceVoice* srcVoice;
		/// �Ǘ��ԍ�
		int handle;
	};
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// XAudio2
	IXAudio2* mXAudio2;
	/// �}�X�^�����O�{�C�X
	IXAudio2MasteringVoice* mMasteringVoice;
	/// �T�E���h�\�[�X
	std::unordered_map<int, SrcData> mSrc;
	/// ���d�Đ��p�\�[�X
	std::vector<OneShotSrcData> mOneShotSrc;
	/// �Ǘ��ԍ��p�n���h��
	Handle mHandle;
	//@}

};

} // namespace
// EOF
