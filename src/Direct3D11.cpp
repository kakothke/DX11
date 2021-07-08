#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto WINDOW = Window::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
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
/// �f�X�g���N�^
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
/// ����������
/// @return ���������� ����(true)
bool Direct3D11::initialize()
{
	if (!createDeviceAndSwapChain()) {
		MessageBox(nullptr, TEXT("�f�o�C�X�ƃX���b�v�`�F�[���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createRenderTargetView()) {
		MessageBox(nullptr, TEXT("�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createDepthAndStencil()) {
		MessageBox(nullptr, TEXT("�[�x�X�e���V���r���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createDepthStencilState()) {
		MessageBox(nullptr, TEXT("�[�x�X�e���V���X�e�[�g�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createTextureSampler()) {
		MessageBox(nullptr, TEXT("�e�N�X�`���T���v���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createBlendState()) {
		MessageBox(nullptr, TEXT("�u�����h�X�e�[�g�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!mConstantBuffer.initialize(mDevice, mContext)) {
		MessageBox(nullptr, TEXT("�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �r���[�|�[�g��ݒ肷��
	setUpViewPort();
	// ���X�^���C�Y��ݒ肷��
	setUpRasterize();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �`��J�n
/// @param aClearCol �`��N���A�F
void Direct3D11::drawStart(const float aClearCol[4])
{
	mContext->ClearRenderTargetView(mRenderTargetViews, aClearCol);
	mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//-------------------------------------------------------------------------------------------------
/// �`��I��
void Direct3D11::drawEnd()
{
	mSwapChain->Present(0, 0);
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aShaderData �V�F�[�_�[�f�[�^
void Direct3D11::setShader(const ShaderLoader::ShaderData* aShaderData)
{
	// VertexShader��ݒ�
	mContext->VSSetShader(
		aShaderData->vs,
		nullptr,
		0
	);

	// PixelShader��ݒ�
	mContext->PSSetShader(
		aShaderData->ps,
		nullptr,
		0
	);

	// InputAssemblerStage�ɓ��̓��C�A�E�g��ݒ肷��
	mContext->IASetInputLayout(aShaderData->inputLayout);
}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`���[��ݒ肷��
/// @param aTexture �e�N�X�`���[
void Direct3D11::setTexture(ID3D11ShaderResourceView* aTexture)
{
	mContext->PSSetSamplers(0, 1, &mSamplerState);
	mContext->PSSetShaderResources(0, 1, &aTexture);
}

//-------------------------------------------------------------------------------------------------
/// Z�o�b�t�@��ݒ肷��
/// @param aModeNum 0(������) / 1(�L����)
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
/// �u�����h���[�h��ݒ肷��
/// @param aBlendNum �u�����h���X�g
void Direct3D11::setBlendMode(const BlendList& aBlendList)
{
	mContext->OMSetBlendState(mBlendState[aBlendList], 0, 0xffffffff);
}

//-------------------------------------------------------------------------------------------------
/// �f�o�C�X���擾����
/// @return �f�o�C�X
ID3D11Device* Direct3D11::getDevice() const
{
	return mDevice;
}

//-------------------------------------------------------------------------------------------------
/// �R���e�L�X�g���擾����
/// @return �R���e�L�X�g
ID3D11DeviceContext* Direct3D11::getContext() const
{
	return mContext;
}

//-------------------------------------------------------------------------------------------------
/// �R���X�^���g�o�b�t�@���擾����
/// @return �R���X�^���g�o�b�t�@
ConstantBuffer* Direct3D11::getConstantBuffer()
{
	return &mConstantBuffer;
}

//-------------------------------------------------------------------------------------------------
/// �f�o�C�X�ƃX���b�v�`�F�[�����쐬����
/// @return �쐬���� ����(true)
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
/// �����_�[�^�[�Q�b�g�r���[���쐬����
/// @return �쐬���� ����(true)
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
/// �[�x�X�e���V���r���[���쐬����
/// @return �쐬���� ����(true)
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

	// OutputMangerRnderTaget�̎w��
	mContext->OMSetRenderTargets(1, &mRenderTargetViews, mDepthStencilView);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �[�x�X�e���V���X�e�[�g���쐬����
/// @return �쐬���� ����(true)
bool Direct3D11::createDepthStencilState()
{
	// �[�x�X�e���V���X�e�[�g���쐬
	D3D11_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = false;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.StencilEnable = false;

	// Z�o�b�t�@����
	HRESULT hr;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthStencilState[0]);
	if (FAILED(hr)) {
		return false;
	}

	// Z�o�b�t�@�L��
	dc.DepthEnable = true;
	hr = mDevice->CreateDepthStencilState(&dc, &mDepthStencilState[1]);
	if (FAILED(hr)) {
		return false;
	}

	// �[�x�X�e���V���X�e�[�g��K�p
	mContext->OMSetDepthStencilState(mDepthStencilState[1], 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`���[�T���v���[���쐬����
/// @return �쐬���� ����(true)
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
/// �u�����h�X�e�[�g���쐬����
/// @return �쐬���� ����(true)
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

	// �ʏ�
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	HRESULT hr;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::None]);
	if (FAILED(hr)) {
		return false;
	}

	// ����
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::Normal]);
	if (FAILED(hr)) {
		return false;
	}

	// ���Z
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::Addition]);
	if (FAILED(hr)) {
		return false;
	}

	// ���Z����
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	hr = mDevice->CreateBlendState(&blendDesc, &mBlendState[BlendList::AdditionAlpha]);
	if (FAILED(hr)) {
		return false;
	}

	// �K�p
	mContext->OMSetBlendState(mBlendState[BlendList::None], 0, 0xffffffff);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �r���[�|�[�g��ݒ肷��
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
/// ���X�^���C�Y��ݒ肷��
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
