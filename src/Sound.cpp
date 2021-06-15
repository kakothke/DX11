#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
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
/// デストラクタ
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
/// 初期化処理
/// @return 結果 成功(true)
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
		MessageBox(nullptr, TEXT("Xaudio2の作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		CoUninitialize();
		return false;
	}
	hr = mXAudio2->CreateMasteringVoice(&mMasteringVoice);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("MasterVoiceの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		CoUninitialize();
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 読み込み
/// @brief 現在はwavファイルのみ対応。後々oggも読み込めるようにしたい
/// @param aFileName 読み込みたいファイルのパス
/// @return 読み込み失敗（-1）/ 成功（管理番号）
int Sound::load(const char* const aFileName)
{
	// エラーチェック
	if (!mXAudio2) {
		return -1;
	}

	const int handle = mHandle.update();
	if (!loadWaveFile(aFileName, handle)) {
		MessageBox(nullptr, TEXT(".wavファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mHandle.release(handle);
		return -1;
	}

	return handle;
}

//-------------------------------------------------------------------------------------------------
/// 破棄
/// @param aHandle 破棄したいサウンドの管理番号
void Sound::release(const int& aHandle)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
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
/// 通常再生
/// @brief サウンド単体を再生する（BGM用）
/// @param aHandle 再生したいサウンドの管理番号
void Sound::play(const int& aHandle)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	XAUDIO2_VOICE_STATE state;
	mSrc[aHandle].srcVoice->GetState(&state);
	// キューにバッファーを追加
	if (state.BuffersQueued == 0) {
		mSrc[aHandle].srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
	}
	// 再生
	mSrc[aHandle].srcVoice->Start();
}

//-------------------------------------------------------------------------------------------------
/// 多重再生
/// @brief サウンドの終了を待たずに多重再生が可能(SE用)
/// @param aHandle 再生したいサウンドの管理番号
/// @param aPlayPausingFlag 一時停止中のサウンドを再生させるか
void Sound::playOneShot(const int& aHandle, const bool& aPlayPausingFlag)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	// 複製されたデータの中に既に終了している物があれば破棄する
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

	// ソースボイスを複製
	if (!aPlayPausingFlag) {
		// 複製
		OneShotSrcData data;
		data.handle = aHandle;
		mXAudio2->CreateSourceVoice(&data.srcVoice, mSrc[aHandle].wavFmtEx);
		mOneShotSrc.emplace_back(data);
		data.srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
		// ボリュームをコピー
		float volume;
		mSrc[aHandle].srcVoice->GetVolume(&volume);
		data.srcVoice->SetVolume(volume);
	}

	// 再生
	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			src.srcVoice->Start();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 停止
/// @brief 次に再生する時は最初から始まる
/// @param aHandle 停止したいサウンドの管理番号
void Sound::stop(const int& aHandle)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
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
/// 一時停止
/// @brief 次に再生するときは停止位置から再開する
/// @param aHandle 停止したいサウンドの管理番号
void Sound::pause(const int& aHandle)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
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
/// ボリュームを変更する
/// @param aHandle 変更したいサウンドの管理番号
/// @param aVolume 設定する音量（0~2）
void Sound::setVolume(const int& aHandle, float aVolume)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	aVolume = Math::Clamp(aVolume, 0.0f, 2.0f);
	float nowVolume;
	mSrc[aHandle].srcVoice->GetVolume(&nowVolume);
	if (nowVolume != aVolume) {
		mSrc[aHandle].srcVoice->SetVolume(aVolume);
		for (auto src : mOneShotSrc) {
			if (src.handle == aHandle) {
				src.srcVoice->SetVolume(aVolume);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// パンを設定する（未完成）
/// @param aHandle 変更したいサウンドの管理番号
/// @param aPan 設定するパン（-1~1）
void Sound::setPan(const int& aHandle, float aPan)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	aPan = Math::Clamp(aPan, -1.0f, 1.0f);

	XAUDIO2_VOICE_DETAILS details;
	mSrc[aHandle].srcVoice->GetVoiceDetails(&details);
	int inCh = details.InputChannels;
	mMasteringVoice->GetVoiceDetails(&details);
	int outCh = details.InputChannels;

	float* volumes = new float[inCh];
	for (int i = 0; i > inCh; i++) {

	}

	//mSrc[aHandle].srcVoice->SetOutputMatrix(NULL, inCh, outCh, volumes);
	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			//src.srcVoice->SetOutputMatrix(NULL, inCh, outCh, volumes);
		}
	}

	delete volumes;
	volumes = nullptr;
}

//-------------------------------------------------------------------------------------------------
/// ループの設定をする
/// @param aHandle 設定したいサウンドの管理番号
/// @param aLoopFlag ループ設定 ループさせる（true）ループ解除（false）
/// @param aLoopCount ループ数（0 = 無限ループ）
void Sound::setLoop(const int& aHandle, const bool& aLoopFlag, const int& aLoopCount)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	if (aLoopFlag) {
		if (aLoopCount == 0) {
			// 無限ループ
			mSrc[aHandle].buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		} else {
			// 回数付きループ
			mSrc[aHandle].buffer.LoopCount = aLoopCount;
		}
	} else if (mSrc[aHandle].buffer.LoopCount != 0) {
		// ループ解除
		mSrc[aHandle].buffer.LoopCount = 0;
		mSrc[aHandle].srcVoice->ExitLoop();
		for (auto src : mOneShotSrc) {
			if (src.handle == aHandle) {
				src.srcVoice->ExitLoop();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ループの位置の設定をする
/// @param aHandle 設定したいサウンドの管理番号
/// @param aBeginPos 開始サンプル位置（0 = 設定しない）
/// @param aEndPos 終了サンプル位置（0 = 設定しない）
void Sound::setLoopPos(const int& aHandle, const UINT32& aBeginPos, const UINT32& aEndPos)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	if (aBeginPos != 0) {
		mSrc[aHandle].buffer.LoopBegin = aBeginPos;
	}
	if (aEndPos != 0 || aBeginPos < aEndPos) {
		mSrc[aHandle].buffer.LoopLength = aEndPos - aBeginPos;
	}
}

//-------------------------------------------------------------------------------------------------
/// 再生開始位置を設定する
/// @param aHandle 設定したいサウンドの管理番号
/// @param aBeginPos 開始サンプル位置
void Sound::setBeginPos(const int& aHandle, const UINT32& aBeginPos)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	mSrc[aHandle].buffer.PlayBegin = aBeginPos;
}

//-------------------------------------------------------------------------------------------------
/// 再生中かどうか調べる
/// @param aHandle 調べたいサウンドの管理番号
/// @return 結果 再生中（true）
const bool& Sound::checkIsPlaying(const int& aHandle)
{
	// エラーチェック
	if (!mSrc.count(aHandle) || !mXAudio2) {
		return false;
	}

	XAUDIO2_VOICE_STATE state;
	mSrc[aHandle].srcVoice->GetState(&state);
	if (state.BuffersQueued > 0) {
		return true;
	}
	for (auto src : mOneShotSrc) {
		if (src.handle == aHandle) {
			src.srcVoice->GetState(&state);
			if (state.BuffersQueued > 0) {
				return true;
			}
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
/// .wav形式のファイルを読み込む
/// @param aFileName ファイル名
/// @param aHandle 管理番号
/// @return 結果 成功（true）
bool Sound::loadWaveFile(const char* const aFileName, const int& aHandle)
{
	HMMIO hMmio = NULL;
	DWORD waveSize = 0;
	MMCKINFO ckInfo = {};
	MMCKINFO riffckInfo = {};
	PCMWAVEFORMAT pcmWaveFmt = {};

	// .wavファイル内のヘッダー情報（音データ以外）の確認と読み込み
	hMmio = mmioOpenA((char*)aFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == NULL) {
		return false;
	}

	// ファイルポインタをRIFFチャンクの先頭にセットする
	MMRESULT mmr;
	mmr = mmioDescend(hMmio, &riffckInfo, NULL, 0);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmr = mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// フォーマットを読み込む
	mmioRead(hMmio, (HPSTR)&pcmWaveFmt, sizeof(pcmWaveFmt));
	mSrc[aHandle].wavFmtEx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(mSrc[aHandle].wavFmtEx, &pcmWaveFmt, sizeof(pcmWaveFmt));
	mSrc[aHandle].wavFmtEx->cbSize = 0;
	mmr = mmioAscend(hMmio, &ckInfo, 0);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// WAVファイル内の音データの読み込み	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmr = mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	if (mmr != MMSYSERR_NOERROR) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}
	waveSize = ckInfo.cksize;

	// ソースボイス作成
	HRESULT hr = mXAudio2->CreateSourceVoice(&mSrc[aHandle].srcVoice, mSrc[aHandle].wavFmtEx);
	if (FAILED(hr)) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// バッファーの設定
	mSrc[aHandle].wavBuffer = new BYTE[waveSize];
	mmioRead(hMmio, (HPSTR)mSrc[aHandle].wavBuffer, waveSize);
	mSrc[aHandle].buffer.pAudioData = mSrc[aHandle].wavBuffer;
	mSrc[aHandle].buffer.Flags = XAUDIO2_END_OF_STREAM;
	mSrc[aHandle].buffer.AudioBytes = waveSize;

	// 閉じる
	mmioClose(hMmio, MMIO_FHOPEN);

	return true;
}

} // namespace
// EOF
