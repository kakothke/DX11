#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Singleton.h"
#include "ConstantBuffer.h"
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "D3D11.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	void drawStart();
	void drawEnd();
	//@}

	void setUpContext(const ShaderData* aShaderData);
	void setTexture(ID3D11ShaderResourceView* aTexture);

	/// @name アクセサ
	//@{
	/// デバイスを返す
	ID3D11Device* getDevice() const;
	/// コンテキストを返す
	ID3D11DeviceContext* getContext() const;
	/// コンスタントバッファーを参照する
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
	ID3D11RenderTargetView* mRenderTargetView;
	/// 深度ステンシルビュー
	ID3D11DepthStencilView* mDepthStencilView;
	/// 深度ステンシルビューを生成する為のテクスチャ
	ID3D11Texture2D* mDepthStencilTexture;
	/// 深度ステンシルステート
	ID3D11DepthStencilState* mDepthStencilState;
	/// テクスチャサンプラー
	ID3D11SamplerState* mSamplerState;
	/// コンスタントバッファー
	ConstantBuffer mConstantBuffer;
	//@}

};

} // namespace
// EOF
