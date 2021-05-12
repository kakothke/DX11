#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Direct3D11::Direct3D11()
	: mDevice(nullptr)
	, mContext(nullptr)
	, mSwapChain(nullptr)
	, mRenderTargetView(nullptr)
	, mDepthStencilView(nullptr)
	, mDepthStencilTexture(nullptr)
	, mDepthStencilState(nullptr)
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
	if (mRenderTargetView) {
		mRenderTargetView->Release();
		mRenderTargetView = nullptr;
	}
	if (mContext) {
		mContext->ClearState();
		mContext->Flush();
		mContext->Release();
		mContext = nullptr;
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
	// ビューポートを設定する
	setUpViewPort();
	// ラスタライズを設定する
	setUpRasterize();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始
void Direct3D11::drawStart()
{
	mContext->ClearRenderTargetView(mRenderTargetView, Define::ClearColor);
	mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//-------------------------------------------------------------------------------------------------
/// 描画終了
void Direct3D11::drawEnd()
{
	mSwapChain->Present(0, 0);
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
/// デバイスとスワップチェーンを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createDeviceAndSwapChain()
{
	HWND hWnd = FindWindow(Define::WindowName, nullptr);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = Define::WindowWidth;
	sd.BufferDesc.Height = Define::WindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = Define::Fps;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* featureLevel = nullptr;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
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
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// レンダーターゲットビューを作成する
/// @return 作成結果 成功(true)
bool Direct3D11::createRenderTargetView()
{
	ID3D11Texture2D* backBuffer;
	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer))) {
		return false;
	}
	if (FAILED(mDevice->CreateRenderTargetView(backBuffer, NULL, &mRenderTargetView))) {
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
	descDepth.Width = Define::WindowWidth;
	descDepth.Height = Define::WindowHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	if (FAILED(mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencilTexture))) {
		return false;
	}
	if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilTexture, nullptr, &mDepthStencilView))) {
		return false;
	}

	// レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	mContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

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

	if (FAILED(mDevice->CreateDepthStencilState(&dc, &mDepthStencilState))) {
		return false;
	}

	// 深度ステンシルステートを適用
	mContext->OMSetDepthStencilState(mDepthStencilState, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ビューポートを設定する
void Direct3D11::setUpViewPort()
{
	D3D11_VIEWPORT vp;
	vp.Width = Define::WindowWidth;
	vp.Height = Define::WindowHeight;
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
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* rs = nullptr;
	mDevice->CreateRasterizerState(&rdc, &rs);
	mContext->RSSetState(rs);

	rs->Release();
	rs = nullptr;
}

} // namespace
// EOF
