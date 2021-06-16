#pragma once

//-------------------------------------------------------------------------------------------------
#include <xaudio2.h>
#include <unordered_map>
#include "Singleton.h"
#include "Handle.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// サウンド制御
class Sound : public Singleton<Sound>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Sound();
	~Sound();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize();
	//@}

	/// @name 読み込み/破棄
	//@{
	int load(const char* const aFileName);
	void release(const int& aHandle);
	//@}

	/// @name サウンド制御
	//@{
	/// 通常再生
	void play(const int& aHandle);
	/// 多重再生
	void playOneShot(const int& aHandle, const bool& aPlayPausingFlag = false);
	/// 停止
	void stop(const int& aHandle);
	/// 一時停止
	void pause(const int& aHandle);
	/// ボリュームを設定する
	void setVolume(const int& aHandle, float aVolume);
	/// パンを設定する
	void setPan(const int& aHandle, float aPan);
	/// ループの設定をする
	void setLoop(const int& aHandle, const bool& aLoopFlag = true, const int& aLoopCount = 0);
	/// ループの位置の設定をする
	void setLoopPos(const int& aHandle, const UINT32& aBeginPos, const UINT32& aEndPos = 0);
	/// 再生開始位置を設定する
	void setBeginPos(const int& aHandle, const UINT32& aBeginPos);
	/// 再生中かどうか調べる
	bool checkIsPlaying(const int& aHandle);
	//@}

private:
	/// @name 内部実装
	//@{
	bool loadWaveFile(const char* const aFileName, const int& aHandle);
	//@}

	/// @name 内部構造体
	//@{
	/// サウンドソース
	struct SrcData
	{
		/// ソースボイス
		IXAudio2SourceVoice* srcVoice;
		/// ソースバッファー
		XAUDIO2_BUFFER buffer = {};
		/// Waveフォーマット
		WAVEFORMATEX* wavFmtEx;
		/// Waveバッファー
		BYTE* wavBuffer;
	};
	/// 多重再生用ソース
	struct OneShotSrcData
	{
		/// ソースボイス
		IXAudio2SourceVoice* srcVoice;
		/// 管理番号
		int handle;
	};
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// XAudio2
	IXAudio2* mXAudio2;
	/// マスタリングボイス
	IXAudio2MasteringVoice* mMasteringVoice;
	/// サウンドソース
	std::unordered_map<int, SrcData> mSrc;
	/// 多重再生用ソース
	std::vector<OneShotSrcData> mOneShotSrc;
	/// 管理番号用ハンドル
	Handle mHandle;
	//@}

};

} // namespace
// EOF
