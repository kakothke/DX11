#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Singleton.h"
#include "ConstantBuffer.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// Direct3D11の管理
class Direct3D11 : public Singleton<Direct3D11>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Direct3D11();
	~Direct3D11();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize();
	//@}

	/// @name 描画開始/描画終了
	//@{
	void drawStart(const float aClearCol[4]);
	void drawEnd();
	//@}

	/// @name 描画設定
	//@{
	/// シェーダーを設定する
	void setShader(const ShaderLoader::ShaderData* aShaderData);
	/// テクスチャーをセットする
	void setTexture(ID3D11ShaderResourceView* aTexture);
	/// Zバッファを有効化する
	void zBufferOn();
	/// Zバッファを無効化する
	void zBufferOff();
	//@}

	/// @name アクセサ
	//@{
	/// デバイスを取得する
	ID3D11Device* getDevice() const;
	/// コンテキストを取得する
	ID3D11DeviceContext* getContext() const;
	/// コンスタントバッファーを取得する
	ConstantBuffer* getConstantBuffer();
	//@}

private:
	/// @name 内部実装関数
	//@{
	/// デバイスとスワップチェーンを作成する
	bool createDeviceAndSwapChain();
	/// レンダーターゲットビューを作成する
	bool createRenderTargetView();
	/// 深度ステンシルビューを作成する
	bool createDepthAndStencil();
	/// 深度ステンシルステートを作成する
	bool createDepthStencilState();
	/// テクスチャサンプラーを作成する
	bool createTextureSampler();
	/// ブレンドステートを作成する
	bool createBlendState();
	/// ビューポートを設定する
	void setUpViewPort();
	/// ラスタライズを設定する
	void setUpRasterize();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// デバイスのインターフェース
	ID3D11Device* mDevice;
	/// コンテキスト
	ID3D11DeviceContext* mContext;
	/// スワップチェーンのインターフェース
	IDXGISwapChain* mSwapChain;
	/// レンダーターゲットビューのインターフェース
	ID3D11RenderTargetView* mRenderTargetViews;
	/// 深度ステンシルビュー
	ID3D11DepthStencilView* mDepthStencilView;
	/// 深度ステンシルビューを生成する為のテクスチャ
	ID3D11Texture2D* mDepthStencilTexture;
	/// 深度ステンシルステート
	ID3D11DepthStencilState* mDepthStencilState;
	ID3D11DepthStencilState* mDepthDisabledStencilState;
	/// テクスチャサンプラー
	ID3D11SamplerState* mSamplerState;
	/// ブレンドステート
	ID3D11BlendState* mBlendState;
	/// コンスタントバッファー
	ConstantBuffer mConstantBuffer;
	//@}

};

} // namespace
// EOF
