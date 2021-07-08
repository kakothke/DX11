#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto WINDOW = Window::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Direct3D11::Direct3D11()
	: mDevice(nullptr)
	, mContext(nullptr)
	, mSwapChain(nullptr)
	, mRenderTargetViews()
	, mDepthStencilView(nullptr)
	, mDepthStencilTexture(nullptr)
	, mDepthStencilState()
	, mSamplerState(nullptr)
	, mBlendState()
	, mConstantBuffer()
{
	mDepthStencilState[0] = nullptr;
	mDepthStencilState[1] = nullptr;
	mBlendState.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Direct3D11::~Direct3D11()
{
	for (auto blend : mBlendState) {
		if (blend.second) {
			blend.second->Release();
			blend.second = nullptr;
		}
	}
	if (mSamplerState) {
		mSamplerState->Release();
		mSamplerState = nullptr;
	}
	for (auto depth : mDepthStencilState) {
		if (depth) {
			depth->Release();
			depth = nullptr;
		}
	}
	if (mDepthStencilTexture) {
		mDepthStencilTexture->Release();
		mDepthStencilTexture = nullptr;
	}
	if (mDepthStencilView) {
		mDepthStencilView->Release();
		mDepthStencilView = nullptr;
	}
	if (mRenderTargetViews) {
		mRenderTargetViews->Release();
		mRenderTargetViews = nullptr;
	}
	if (mSwapChain) {
		mSwapChain->Release();
		mSwapChain = nullptr;
	}
	if (mContext) {
		mContext->ClearState();
		mContext->Flush();
		mContext->Release();
		mContext = nullptr;
	}
	if (mDevice) {
		mDevice->Release();
		mDevice = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
/// @return 初期化結果 成功(true)
bool Direct3D11::initialize()
{
	if (!createDeviceAndSwapChain()) {
		MessageBox(nullptr, TEXT("デバイスとスワップチェーンの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createRenderTargetView()) {
		MessageBox(nullptr, TEXT("レンダーターゲットビューの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createDepthAndStencil()) {
		MessageBox(nullptr, TEXT("深度ステンシルビューの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createDepthStencilState()) {
		MessageBox(nullptr, TEXT("深度ステンシルステートの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createTextureSampler()) {
		MessageBox(nullptr, TEXT("テクスチャサンプラーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createBlendState()) {
		MessageBox(nullptr, TEXT("ブレンドステートの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!mConstantBuffer.initialize(mDevice, mContext)) {
		MessageBox(nullptr, TEXT("コンスタントバッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// ビューポートを設定する
	setUpViewPort();
	// ラスタライズを設定する
	setUpRasterize();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始
/// @param aClearCol 描画クリア色
void Direct3D11::drawStart(const float aClearCol[4])
{
	mContext->ClearRenderTargetView(mRenderTargetViews, aClearCol);
	mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//-------------------------------------------------------------------------------------------------
/// 描画終了
void Direct3D11::drawEnd()
{
	mSwapChain->Present(0, 0);
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aShaderData シェーダーデータ
void Direct3D11::setShader(const ShaderLoader::ShaderData* aShaderData)
{
	// VertexShaderを設定
	mContext->VSSetShader(
		aShaderData->vs,
		nullptr,
		0
	);

	// PixelShaderを設定
	mContext->PSSetShader(
		aShaderData->ps,
		nullptr,
		0
	);

	// InputAssemblerStageに入力レイアウトを設定する
	mContext->IASetInputLayout(aShaderData->inputLayout);
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーを設定する
/// @param aTexture テクスチャー
void Direct3D11::setTexture(ID3D11ShaderResourceView* aTexture)
{
	mContext->PSSetSamplers(0, 1, &mSamplerState);
	mContext->PSSetShaderResources(0, 1, &aTexture);
}

//-------------------------------------------------------------------------------------------------
/// Zバッファを設定する
/// @param aModeNum 0(無効化) / 1(有効化)
void Direct3D11::setZBufferMode(const int& aModeNum)
{
	switch (aModeNum) {
	case 0:
		mContext->OMSetDepthStencilState(mDepthStencilState[0], 0);
		break;
	case 1:
		mContext->OMSetDepthStencilState(mDepthStencilState[1], 0);
		break;
	default:
		mContext->OMSetDepthStencilState(mDepthStencilState[1], 0);
		break;
	}
}

//-------------------------------------------------------------------------------------------------
/// ブレンドモードを設定する
/// @param aBlendNum ブレンドリスト
void Direct3D11::setBlendMode(const BlendList& aBlendList)
{
	mContext->OMSetBlendState(mBlendState[aBlendList], 0, 0xffffffff);
}

//-------------------------------------------------------------------------------------------------
/// デバイスを取得する
/// @return デバイス
ID3D11Device* Direct3D11::getDevice() const
{
	return mDevice;
}

//-------------------------------------------------------------------------------------------------
/// コンテキストを取得する
/// @return コンテキスト
ID3D11DeviceContext* Direct3D11::getContext() const
{
	return mContext;
}

//-------------------------------------------------------------------------------------------------
/// コンスタントバッファを取得する
/// @return コンスタントバッファ
ConstantBuffer* Direct3D11::getConstantBuffer()
{
	return &mConstantBuffer;
}

//-------------------------------------------------------------------------------------------------
/// デバイスとスワップチェーンを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW->windowWidth();
	sd.BufferDesc.Height = WINDOW->windowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = WINDOW->hWnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* featureLevel = nullptr;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&mSwapChain,
		&mDevice,
		featureLevel,
		&mContext
	);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// レンダーターゲットビューを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createRenderTargetView()
{
	HRESULT hr;
	ID3D11Texture2D* backBuffer;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (FAILED(hr)) {
		return false;
	}
	hr = mDevice->CreateRenderTargetView(backBuffer, NULL, &mRenderTargetViews);
	if (FAILED(hr)) {
		return false;
	}
	backBuffer->Release();
	backBuffer = nullptr;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 深度ステンシルビューを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createDepthAndStencil()
{
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW->windowWidth();
	descDepth.Height = WINDOW->windowHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	HRESULT hr;
	hr = mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencilTexture);
	if (FAILED(hr)) {
		return false;
	}
	hr = mDevice->CreateDepthStencilView(mDepthStencilTexture, nullptr, &mDepthStencilView);
	if (FAILED(hr)) {
		return false;
	}

	// OutputMangerRnderTagetの指定
	mContext->OMSetRenderTargets(1, &mRenderTargetViews, mDepthStencilView);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 深度ステンシルステートを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createDepthStencilState()
{
	// 深度ステンシルステートを作成
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = false;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.StencilEnable = false;

	// Zバッファ無し
	HRESULT hr;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthStencilState[0]);
	if (FAILED(hr)) {
		return false;
	}

	// Zバッファ有り
	dc.DepthEnable = true;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthStencilState[1]);
	if (FAILED(hr)) {
		return false;
	}

	// 深度ステンシルステートを適用
	mContext->OMSetDepthStencilState(mDepthStencilState[1], 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーサンプラーを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createTextureSampler()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HRESULT hr;
	hr = mDevice->CreateSamplerState(&samplerDesc, &mSamplerState);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ブレンドステートを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createBlendState()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// 通常
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	HRESULT hr;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::None]);
	if (FAILED(hr)) {
		return false;
	}

	// 透過
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::Normal]);
	if (FAILED(hr)) {
		return false;
	}

	// 加算
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::Addition]);
	if (FAILED(hr)) {
		return false;
	}

	// 加算透過
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::AdditionAlpha]);
	if (FAILED(hr)) {
		return false;
	}

	// 適用
	mContext->OMSetBlendState(mBlendState[BlendList::None], 0, 0xffffffff);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ビューポートを設定する
void Direct3D11::setUpViewPort()
{
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW->windowWidth();
	vp.Height = WINDOW->windowHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mContext->RSSetViewports(1, &vp);
}

//-------------------------------------------------------------------------------------------------
/// ラスタライズを設定する
void Direct3D11::setUpRasterize()
{
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = true;

	ID3D11RasterizerState* rs = nullptr;
	mDevice->CreateRasterizerState(&rdc, &rs);
	mContext->RSSetState(rs);

	rs->Release();
	rs = nullptr;
}

} // namespace
// EOF
