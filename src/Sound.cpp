#include "Sound.h"

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
	const int handle = mHandle.update();

	if (!loadWaveFile(aFileName, handle)) {
		MessageBox(nullptr, TEXT(".wavファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return -1;
	}

	return handle;
}

//-------------------------------------------------------------------------------------------------
/// 破棄
/// @param aHandle 破棄したいサウンドの管理番号
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
/// 通常再生
/// @brief サウンド単体を再生する（BGM用）
/// @param aHandle 再生したいサウンドの管理番号
void Sound::play(const int& aHandle)
{
	if (!mSrc.count(aHandle)) {
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
	if (!mSrc.count(aHandle)) {
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
		OneShotSrcData data;
		data.handle = aHandle;
		mXAudio2->CreateSourceVoice(&data.srcVoice, mSrc[aHandle].wavFmtEx);
		mOneShotSrc.emplace_back(data);
		data.srcVoice->SubmitSourceBuffer(&mSrc[aHandle].buffer);
	}

	// 再生
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
/// 停止
/// @brief 次に再生する時は最初から始まる
/// @param aHandle 停止したいサウンドの管理番号
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
/// 一時停止
/// @brief 次に再生するときは停止位置から再開する
/// @param aHandle 停止したいサウンドの管理番号
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
/// .wav形式のファイルを読み込む
/// @param aFileName ファイル名
/// @param aHandle 管理番号
/// @return 結果 成功（true）
bool Sound::loadWaveFile(const char* const aFileName, const int& aHandle)
{
	HMMIO hMmio = NULL;
	DWORD waveSize = 0;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFmt;

	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	hMmio = mmioOpenA((char*)aFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == NULL) {
		return false;
	}

	//ファイルポインタをRIFFチャンクの先頭にセットする
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

	//フォーマットを読み込む
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
