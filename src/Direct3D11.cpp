#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
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
/// �f�X�g���N�^
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
/// ����������
/// @return ���������� ����(true)
bool Direct3D11::initialize()
{
	// �f�o�C�X�ƃX���b�v�`�F�[�����쐬����
	if (!createDeviceAndSwapChain()) {
		MessageBox(nullptr, TEXT("�f�o�C�X�ƃX���b�v�`�F�[���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �����_�[�^�[�Q�b�g�r���[���쐬����
	if (!createRenderTargetView()) {
		MessageBox(nullptr, TEXT("�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �[�x�X�e���V���r���[���쐬����
	if (!createDepthAndStencil()) {
		MessageBox(nullptr, TEXT("�[�x�X�e���V���r���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �[�x�X�e���V���X�e�[�g���쐬����
	if (!createDepthStencilState()) {
		MessageBox(nullptr, TEXT("�[�x�X�e���V���X�e�[�g�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �e�N�X�`���T���v���[�̍쐬
	if (!createTextureSampler()) {
		MessageBox(nullptr, TEXT("�e�N�X�`���T���v���[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �R���X�^���g�o�b�t�@���쐬����
	if (!mConstantBuffer.create()) {
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
void Direct3D11::drawStart()
{
	mContext->ClearRenderTargetView(mRenderTargetViews, Define::ClearColor);
	mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//-------------------------------------------------------------------------------------------------
/// �`��I��
void Direct3D11::drawEnd()
{
	mSwapChain->Present(0, 0);
}

//-------------------------------------------------------------------------------------------------
/// �R���e�L�X�g��ݒ肷��
void Direct3D11::setUpContext(const ShaderData* aShaderData)
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
/// �e�N�X�`���[��ݒ肷��
void Direct3D11::setTexture(ID3D11ShaderResourceView* aTexture)
{
	mContext->PSSetSamplers(0, 1, &mSamplerState);
	mContext->PSSetShaderResources(0, 1, &aTexture);
}

//-------------------------------------------------------------------------------------------------
/// �f�o�C�X��Ԃ�
ID3D11Device* Direct3D11::getDevice() const
{
	return mDevice;
}

//-------------------------------------------------------------------------------------------------
/// �R���e�L�X�g��Ԃ�
ID3D11DeviceContext* Direct3D11::getContext() const
{
	return mContext;
}

//-------------------------------------------------------------------------------------------------
ConstantBuffer* Direct3D11::getConstantBuffer()
{
	return &mConstantBuffer;
}

//-------------------------------------------------------------------------------------------------
/// �f�o�C�X�ƃX���b�v�`�F�[�����쐬����
/// @return �쐬���� ����(true)
bool Direct3D11::createDeviceAndSwapChain()
{
	HWND hWnd = FindWindow(Define::WindowName, nullptr);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = Define::ResolutionWidth;
	sd.BufferDesc.Height = Define::ResolutionHeight;
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
/// �����_�[�^�[�Q�b�g�r���[���쐬����
/// @return �쐬���� ����(true)
bool Direct3D11::createRenderTargetView()
{
	ID3D11Texture2D* backBuffer;
	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer))) {
		return false;
	}
	if (FAILED(mDevice->CreateRenderTargetView(backBuffer, NULL, &mRenderTargetViews))) {
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
	descDepth.Width = Define::ResolutionWidth;
	descDepth.Height = Define::ResolutionHeight;
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
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D11_COMPARISON_LESS;
	dc.StencilEnable = false;

	if (FAILED(mDevice->CreateDepthStencilState(&dc, &mDepthStencilState))) {
		return false;
	}

	dc.DepthEnable = false;
	if (FAILED(mDevice->CreateDepthStencilState(&dc, &mDepthDisabledStencilState))) {
		return false;
	}

	// �[�x�X�e���V���X�e�[�g��K�p
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

	if (FAILED(mDevice->CreateSamplerState(&samplerDesc, &mSamplerState))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �r���[�|�[�g��ݒ肷��
void Direct3D11::setUpViewPort()
{
	D3D11_VIEWPORT vp;
	vp.Width = Define::ResolutionWidth;
	vp.Height = Define::ResolutionHeight;
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
