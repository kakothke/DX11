#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Direct3D11::Direct3D11()
	: mDevice(nullptr)
	, mContext(nullptr)
	, mSwapChain(nullptr)
	, mRenderTargetViews()
	, mDepthStencilView(nullptr)
	, mDepthStencilTexture(nullptr)
	, mDepthStencilState(nullptr)
	, mDepthDisabledStencilState(nullptr)
	, mSamplerState(nullptr)
	, mConstantBuffer()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Direct3D11::~Direct3D11()
{
	if (mSwapChain) {
		mSwapChain->Release();
		mSwapChain = nullptr;
	}
	if (mRenderTargetViews) {
		mRenderTargetViews->Release();
		mRenderTargetViews = nullptr;
	}
	if (mContext) {
		mContext->ClearState();
		mContext->Flush();
		mContext->Release();
		mContext = nullptr;
	}
	if (mSamplerState) {
		mSamplerState->Release();
		mSamplerState = nullptr;
	}
	if (mDepthStencilView) {
		mDepthStencilView->Release();
		mDepthStencilView = nullptr;
	}
	if (mDepthStencilTexture) {
		mDepthStencilTexture->Release();
		mDepthStencilTexture = nullptr;
	}
	if (mDepthStencilState) {
		mDepthStencilState->Release();
		mDepthStencilState = nullptr;
	}
	if (mDepthDisabledStencilState) {
		mDepthDisabledStencilState->Release();
		mDepthDisabledStencilState = nullptr;
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
	// デバイスとスワップチェーンを作成する
	if (!createDeviceAndSwapChain()) {
		MessageBox(nullptr, TEXT("デバイスとスワップチェーンの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// レンダーターゲットビューを作成する
	if (!createRenderTargetView()) {
		MessageBox(nullptr, TEXT("レンダーターゲットビューの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// 深度ステンシルビューを作成する
	if (!createDepthAndStencil()) {
		MessageBox(nullptr, TEXT("深度ステンシルビューの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// 深度ステンシルステートを作成する
	if (!createDepthStencilState()) {
		MessageBox(nullptr, TEXT("深度ステンシルステートの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// テクスチャサンプラーの作成
	if (!createTextureSampler()) {
		MessageBox(nullptr, TEXT("テクスチャサンプラーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// コンスタントバッファを作成する
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
/// コンテキストを設定する
void Direct3D11::setUpContext(const ShaderData* aShaderData)
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
void Direct3D11::zBufferOn()
{
	mContext->OMSetDepthStencilState(mDepthStencilState, 0);
}

//-------------------------------------------------------------------------------------------------
void Direct3D11::zBufferOff()
{
	mContext->OMSetDepthStencilState(mDepthDisabledStencilState, 0);
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーを設定する
void Direct3D11::setTexture(ID3D11ShaderResourceView* aTexture)
{
	mContext->PSSetSamplers(0, 1, &mSamplerState);
	mContext->PSSetShaderResources(0, 1, &aTexture);
}

//-------------------------------------------------------------------------------------------------
/// デバイスを返す
ID3D11Device* Direct3D11::getDevice() const
{
	return mDevice;
}

//-------------------------------------------------------------------------------------------------
/// コンテキストを返す
ID3D11DeviceContext* Direct3D11::getContext() const
{
	return mContext;
}

//-------------------------------------------------------------------------------------------------
/// コンスタントバッファを返す
ConstantBuffer* Direct3D11::getConstantBuffer()
{
	return &mConstantBuffer;
}

//-------------------------------------------------------------------------------------------------
/// デバイスとスワップチェーンを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createDeviceAndSwapChain()
{
	auto window = Window::getInst();
	auto hWnd = window->hWnd();
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = window->windowWidth();
	sd.BufferDesc.Height = window->windowHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
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
	auto window = Window::getInst();

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = window->windowWidth();
	descDepth.Height = window->windowHeight();
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
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.StencilEnable = false;

	// Zバッファ有り
	HRESULT hr;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthStencilState);
	if (FAILED(hr)) {
		return false;
	}

	// Zバッファ無し
	dc.DepthEnable = false;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthDisabledStencilState);
	if (FAILED(hr)) {
		return false;
	}

	// 深度ステンシルステートを適用
	mContext->OMSetDepthStencilState(mDepthStencilState, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
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
/// ビューポートを設定する
void Direct3D11::setUpViewPort()
{
	auto window = Window::getInst();

	D3D11_VIEWPORT vp;
	vp.Width = window->windowWidth();
	vp.Height = window->windowHeight();
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
