#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
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
/// デストラクタ
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
/// デストラクタ
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
int Sound::load(const LPCSTR aFileName)
{
	// エラーチェック
	if (!mXAudio2) {
		return -1;
	}

	const auto handle = mHandle.update();
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
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	// ハンドル破棄
	mHandle.release(aHandle);

	// ソース破棄
	mMainSrc.erase(aHandle);
	for (auto src : mSubSrc[aHandle]) {
		src->DestroyVoice();
		src = nullptr;
	}
	mSubSrc.erase(aHandle);
}

//-------------------------------------------------------------------------------------------------
/// 通常再生
/// @brief サウンド単体を再生する（BGM用）
/// @param aHandle 再生したいサウンドの管理番号
void Sound::play(const int& aHandle)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	XAUDIO2_VOICE_STATE state;
	mMainSrc[aHandle].srcVoice->GetState(&state);
	// キューにバッファーを追加
	if (state.BuffersQueued == 0) {
		mMainSrc[aHandle].srcVoice->SubmitSourceBuffer(&mMainSrc[aHandle].buffer);
	}
	// 再生
	mMainSrc[aHandle].srcVoice->Start();
}

//-------------------------------------------------------------------------------------------------
/// 多重再生
/// @brief サウンドの終了を待たずに多重再生が可能(SE用)
/// @param aHandle 再生したいサウンドの管理番号
/// @param aPlayPausingFlag 一時停止中のサウンドを再生させるか
void Sound::playOneShot(const int& aHandle, const bool& aPlayPausingFlag)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}

	// 複製されたデータの状況を調べる
	for (auto sub : mSubSrc) {
		XAUDIO2_VOICE_STATE state;
		auto itr = mSubSrc[sub.first].begin();
		while (itr != mSubSrc[sub.first].end()) {
			auto src = (*itr);
			src->GetState(&state);
			if (state.BuffersQueued == 0) {
				// 再生終了していたら破棄
				src->DestroyVoice();
				src = nullptr;
				itr = mSubSrc[sub.first].erase(itr);
			} else {
				itr++;
			}
		}
	}

	if (!aPlayPausingFlag) {
		// ソースボイスを複製する
		IXAudio2SourceVoice* src;
		mXAudio2->CreateSourceVoice(&src, mMainSrc[aHandle].wavFmtEx);
		src->SubmitSourceBuffer(&mMainSrc[aHandle].buffer);
		// ボリュームをコピー
		float volume;
		mMainSrc[aHandle].srcVoice->GetVolume(&volume);
		src->SetVolume(volume);
		// vectorに追加
		mSubSrc[aHandle].emplace_back(src);
	}

	// 再生
	for (auto src : mSubSrc[aHandle]) {
		src->Start();
	}
}

//-------------------------------------------------------------------------------------------------
/// 停止
/// @brief 次に再生する時は最初から始まる
/// @param aHandle 停止したいサウンドの管理番号
void Sound::stop(const int& aHandle)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// 停止
	mMainSrc[aHandle].srcVoice->Stop(0, 0);
	mMainSrc[aHandle].srcVoice->FlushSourceBuffers();
	for (auto src : mSubSrc[aHandle]) {
		src->Stop(0, 0);
		src->FlushSourceBuffers();
	}
}

//-------------------------------------------------------------------------------------------------
/// 一時停止
/// @brief 次に再生するときは停止位置から再開する
/// @param aHandle 停止したいサウンドの管理番号
void Sound::pause(const int& aHandle)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// 一時停止
	mMainSrc[aHandle].srcVoice->Stop(0, 0);
	for (auto src : mSubSrc[aHandle]) {
		src->Stop(0, 0);
	}
}

//-------------------------------------------------------------------------------------------------
/// ボリュームを変更する
/// @param aHandle 変更したいサウンドの管理番号
/// @param aVolume 設定する音量（0~2）
void Sound::setVolume(const int& aHandle, float aVolume)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ボリュームを変更する
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
/// ループの設定をする
/// @param aHandle 設定したいサウンドの管理番号
/// @param aLoopFlag ループ設定 ループさせる（true）ループ解除（false）
/// @param aLoopCount ループ数（0 = 無限ループ）
void Sound::setLoop(const int& aHandle, const bool& aLoopFlag, const int& aLoopCount)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ループ設定
	if (aLoopFlag) {
		if (aLoopCount == 0) {
			// 無限ループ
			mMainSrc[aHandle].buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		} else {
			// 回数付きループ
			mMainSrc[aHandle].buffer.LoopCount = aLoopCount;
		}
	} else if (mMainSrc[aHandle].buffer.LoopCount != 0) {
		// ループ解除
		mMainSrc[aHandle].buffer.LoopCount = 0;
		mMainSrc[aHandle].srcVoice->ExitLoop();
		for (auto src : mSubSrc[aHandle]) {
			src->ExitLoop();
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
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// ループ位置設定
	if (aBeginPos != 0) {
		mMainSrc[aHandle].buffer.LoopBegin = aBeginPos;
	}
	if (aEndPos != 0 || aBeginPos < aEndPos) {
		mMainSrc[aHandle].buffer.LoopLength = aEndPos - aBeginPos;
	}
}

//-------------------------------------------------------------------------------------------------
/// 再生開始位置を設定する
/// @param aHandle 設定したいサウンドの管理番号
/// @param aBeginPos 開始サンプル位置
void Sound::setBeginPos(const int& aHandle, const UINT32& aBeginPos)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return;
	}
	// 再生開始位置設定
	mMainSrc[aHandle].buffer.PlayBegin = aBeginPos;
}

//-------------------------------------------------------------------------------------------------
/// 再生中かどうか調べる
/// @param aHandle 調べたいサウンドの管理番号
/// @return 結果 再生中（true）
bool Sound::checkIsPlaying(const int& aHandle)
{
	// エラーチェック
	if (!mMainSrc.count(aHandle) || !mXAudio2) {
		return false;
	}
	// 再生中か調べる
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
/// .wav形式のファイルを読み込む
/// @param aFileName ファイル名
/// @param aHandle 管理番号
/// @return 結果 成功（true）
bool Sound::loadWaveFile(const LPCSTR aFileName, const int& aHandle)
{
	HMMIO hMmio = NULL;
	DWORD wavSize = 0;
	MMCKINFO ckInfo = {};
	MMCKINFO riffckInfo = {};
	PCMWAVEFORMAT pcmWavFmt = {};

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
	mmioRead(hMmio, (HPSTR)&pcmWavFmt, sizeof(pcmWavFmt));
	mMainSrc[aHandle].wavFmtEx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(mMainSrc[aHandle].wavFmtEx, &pcmWavFmt, sizeof(pcmWavFmt));
	mMainSrc[aHandle].wavFmtEx->cbSize = 0;
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
	wavSize = ckInfo.cksize;

	// ソースボイス作成
	HRESULT hr = mXAudio2->CreateSourceVoice(&mMainSrc[aHandle].srcVoice, mMainSrc[aHandle].wavFmtEx);
	if (FAILED(hr)) {
		mmioClose(hMmio, MMIO_FHOPEN);
		return false;
	}

	// バッファーの設定
	mMainSrc[aHandle].wavBuffer = new BYTE[wavSize];
	mmioRead(hMmio, (HPSTR)mMainSrc[aHandle].wavBuffer, wavSize);
	mMainSrc[aHandle].buffer.pAudioData = mMainSrc[aHandle].wavBuffer;
	mMainSrc[aHandle].buffer.Flags = XAUDIO2_END_OF_STREAM;
	mMainSrc[aHandle].buffer.AudioBytes = wavSize;

	// 閉じる
	mmioClose(hMmio, MMIO_FHOPEN);

	return true;
}

} // namespace
// EOF
