#include "FontRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
FontRenderer::FontRenderer()
	: mString(NULL)
	, mFontName(NULL)
	, mVertexBuffer(nullptr)
	, mTexture(nullptr)
	, mShaderData()
	, mColor(1, 1, 1, 1)
	, mPivot(0.5f, 0.5f)
	, mAnchor(0, 0)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
FontRenderer::~FontRenderer()
{
	if (mVertexBuffer) {
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
	if (mTexture) {
		mTexture->Release();
		mTexture = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aString �\������
/// @param aTransform �\���ʒu
/// @param aFontName �t�H���g��
void FontRenderer::draw(
	const LPCTSTR aString,
	const DirectX::XMFLOAT3X3& aTransform,
	const LPCTSTR aFontName)
{
	// �`�F�b�N
	if (!mShaderData) {
		return;
	}

	// �e�N�X�`���[�쐬
	if (mString != aString || mFontName != aFontName) {
		mString = aString;
		mFontName = aFontName;
		if (!cretaeTexture()) {
			mString = NULL;
			mFontName = NULL;
			return;
		}
		if (!createVertexBuffer()) {
			mString = NULL;
			mFontName = NULL;
			return;
		}
	}

	// Direct3D11�擾
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	d3D11->setShader(mShaderData);

	UINT strides = sizeof(FontVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	cBuf->updateColor(mColor, mColor);
	cBuf->updateSprite(aTransform, mAnchor, mPivot, { 1,1 });

	// �e�N�X�`���[�Z�b�g
	d3D11->setTexture(mTexture);

	// �`��
	context->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aShaderFileName �V�F�[�_�[�̃t�@�C���p�X
void FontRenderer::setShaderData(const char* const aShaderFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// �J���[��ݒ肷��
/// @param aColor �F(0~1)
void FontRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// �`�撆�S�ʒu��ݒ肷��
/// @param aPivot ���S�ʒu(x,y){0~1}
void FontRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
/// �`��J�n�ʒu��ݒ肷��
/// @param aAnchor �J�n�ʒu(x,y){-1~1}
void FontRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`���[���쐬����
/// @return ���� ����(true)
bool FontRenderer::cretaeTexture()
{
	// �����R�[�h�擾
	UINT code = 0;
#if _UNICODE
	code = (UINT)*mString;
#else
	if (IsDBCSLeadByte(*mString)) {
		code = (BYTE)mString[0] << 8 | (BYTE)mString[1];
	} else {
		code = mString[0];
	}
#endif

	// �t�H���g�r�b�g�}�b�v�擾
	const auto hdc = FontLoader::getInst()->hdc(mFontName);
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 Mat = { {0,1}, {0,0}, {0,0}, {0,1} };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, 0, NULL, &Mat);
	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &Mat);

	// �e�N�X�`���쐬
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = gm.gmCellIncX;
	desc.Height = tm.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr;
	ID3D11Texture2D* tex2D;
	const auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateTexture2D(&desc, 0, &tex2D);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	const auto context = Direct3D11::getInst()->getContext();
	hr = context->Map(tex2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &hMappedResource);
	if (FAILED(hr)) {
		return false;
	}

	// �t�H���g���̏�������
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	int iOfs_x = gm.gmptGlyphOrigin.x;
	int iOfs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int iBmp_w = (gm.gmBlackBoxX + 3) / 4 * 4;
	int iBmp_h = gm.gmBlackBoxY;
	int level = 16;
	int x, y;
	DWORD alpha, col;
	memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++) {
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++) {
			alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / level;
			col = 0x00ffffff | (alpha << 24);
			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &col, sizeof(DWORD));
		}
	}
	context->Unmap(tex2D, 0);
	delete[] ptr;

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	// ShaderResourceView���쐬����
	if (mTexture) {
		mTexture->Release();
		mTexture = nullptr;
	}
	hr = device->CreateShaderResourceView(tex2D, &srvDesc, &mTexture);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @return �쐬���� ����(true)
bool FontRenderer::createVertexBuffer()
{
	FontVertex vertexes[4];
	createMesh(vertexes);
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(FontVertex) * 4;
		// �g�p���@
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND�ݒ�
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
		bufferDesc.CPUAccessFlags = 0;
		// ���\�[�X�I�v�V�����̃t���O
		bufferDesc.MiscFlags = 0;
		// �\���̂̃T�C�Y
		bufferDesc.StructureByteStride = 0;
	}

	// ���\�[�X���
	D3D11_SUBRESOURCE_DATA subResource;
	{
		// �o�b�t�@�̒��g�̐ݒ�
		subResource.pSysMem = &vertexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	HRESULT hr;
	const auto device = Direct3D11::getInst()->getDevice();
	if (mVertexBuffer) {
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
	hr = device->CreateBuffer(&bufferDesc, &subResource, &mVertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�V���쐬
/// @param aFileName �t�@�C���p�X
/// @param aVertexes ���_�f�[�^
void FontRenderer::createMesh(FontVertex* aVertexes)
{
	// �e�N�X�`���[�̃T�C�Y���Q��
	ID3D11Resource* res = nullptr;
	mTexture->GetResource(&res);
	ID3D11Texture2D* tex2D = nullptr;
	res->QueryInterface(&tex2D);
	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);

	float width = (float)desc.Width;
	float height = (float)desc.Height;

	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

	// �\��
	{
		// ���_0
		aVertexes[0].pos[0] = -width;
		aVertexes[0].pos[1] = -height;
		aVertexes[0].uv[0] = 0;
		aVertexes[0].uv[1] = 1;
		// ���_1
		aVertexes[1].pos[0] = width;
		aVertexes[1].pos[1] = -height;
		aVertexes[1].uv[0] = 1;
		aVertexes[1].uv[1] = 1;
		// ���_2
		aVertexes[2].pos[0] = -width;
		aVertexes[2].pos[1] = height;
		aVertexes[2].uv[0] = 0;
		aVertexes[2].uv[1] = 0;
		//// ���_3
		aVertexes[3].pos[0] = width;
		aVertexes[3].pos[1] = height;
		aVertexes[3].uv[0] = 1;
		aVertexes[3].uv[1] = 0;
	}
}

} // namespace
// EOF
