#include "FontRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();
const static auto FONT_LOADER = FontLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
FontRenderer::FontRenderer()
	: mString(NULL)
	, mFontName(NULL)
	, mTextures()
	, mShaderData()
	, mColor()
	, mPivot()
	, mAnchor()
{
	mTextures.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
FontRenderer::~FontRenderer()
{
	for (const auto line : mTextures) {
		for (auto tex : line) {
			if (tex.vertexBuffer) {
				tex.vertexBuffer->Release();
				tex.vertexBuffer = nullptr;
			}
			if (tex.texture) {
				tex.texture->Release();
				tex.texture = nullptr;
			}
		}
	}
	mTextures.clear();
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aString �\������
/// @param aTransform �\���ʒu
void FontRenderer::draw(Transform aTransform)
{
	// �`�F�b�N
	if (!mShaderData || !mString) {
		return;
	}


	// �v���~�e�B�u�̌`����w��
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	D3D11->setShader(mShaderData);

	UINT strides = sizeof(VertexData);
	UINT offsets = 0;

	Transform initTransform = aTransform;

	// �`�揉���ʒu��ύX
	for (const auto line : mTextures) {
		aTransform.pos.x = initTransform.pos.x;
		// �����ʒu�v�Z
		for (int i = 0; i < line.size(); i++) {
			if (i > 0) {
				aTransform.pos.x -= line[i].nextPos / 2;
			}
		}
		// �`��
		float nextPos = 0.0f;
		for (const auto tex : line) {
			if (!tex.hideFlag) {
				// ���T�C�Y
				aTransform.scale = initTransform.scale;/*
				aTransform.scale.x *= tex.texSize.x;
				aTransform.scale.y *= tex.texSize.y;*/

				// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
				D3D11->getContext()->IASetVertexBuffers(0, 1, &tex.vertexBuffer, &strides, &offsets);

				// �R���X�^���g�o�b�t�@���X�V
				D3D11->getConstantBuffer()->setSpriteSplit(1);
				D3D11->getConstantBuffer()->updateColor(mColor, mColor);
				D3D11->getConstantBuffer()->setSpriteMatrixW(aTransform, mPivot);
				D3D11->getConstantBuffer()->setSpriteMatrixP(mAnchor);
				D3D11->getConstantBuffer()->updateSprite();

				// �e�N�X�`���[�Z�b�g
				D3D11->setTexture(tex.texture);

				// �`��
				D3D11->getContext()->Draw(8, 0);
			}

			// �`��ʒu�����炷
			nextPos += tex.nextPos * aTransform.scale.x;
			aTransform.pos.x += tex.nextPos * aTransform.scale.x;
			if (tex.newLine != 0) {
				aTransform.pos.x -= nextPos;
				nextPos = 0;
				aTransform.pos.y += tex.newLine * aTransform.scale.y;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
void FontRenderer::setString(const LPCTSTR aString)
{
	if (mString != aString) {
		mString = aString;
		if (!cretaeFontMesh()) {
			mString = NULL;
			return;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aFileName �V�F�[�_�[�̃t�@�C���p�X
void FontRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �t�H���g��ݒ肷��
/// @param aFontName �t�H���g��
void FontRenderer::setFont(const LPCTSTR aFontName)
{
	if (mFontName != aFontName) {
		mFontName = aFontName;
		// �e�N�X�`���[�쐬
		if (mString) {
			cretaeFontMesh();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �J���[��ݒ肷��
/// @param aColor �J���[
void FontRenderer::setColor(const Color& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// �`�撆�S�ʒu��ݒ肷��
/// @param aX ���_x(-1~1)
/// @param aY ���_y(-1~1)
void FontRenderer::setPivot(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	Vector2 size(0.0f, 0.0f);
	for (const auto line : mTextures) {
		for (const auto tex : line) {
			size.x += tex.nextPos;
		}
	}

	mPivot.x = (size.x / 2.0f) * -aX;
	mPivot.y = (size.y / 2.0f) * aY;
}

//-------------------------------------------------------------------------------------------------
/// �`��J�n�ʒu��ݒ肷��
/// @param aX �`��J�n�ʒux(-1~1)
/// @param aY �`��J�n�ʒuy(-1~1)
void FontRenderer::setAnchor(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mAnchor.x = aX;
	mAnchor.y = aY;
}

//-------------------------------------------------------------------------------------------------
/// �t�H���g���b�V�����쐬����
/// @return ���� ����(true)
bool FontRenderer::cretaeFontMesh()
{
	// �t�H���g���b�V��������
	for (const auto line : mTextures) {
		for (auto tex : line) {
			if (tex.vertexBuffer) {
				tex.vertexBuffer->Release();
				tex.vertexBuffer = nullptr;
			}
			if (tex.texture) {
				tex.texture->Release();
				tex.texture = nullptr;
			}
		}
	}
	mTextures.clear();
	mTextures.emplace_back();

	// �e�N�X�`���[�쐬
	UINT code = 0;
	int lineCount = 0;
	int indexNum = 0;
	LPCTSTR str = mString;
	for (int i = 0; i < lstrlen(mString); i++) {
#if _UNICODE
		code = (UINT)mString[i];
#else
		if (IsDBCSLeadByte(*str)) {
			// 2�o�C�g����
			code = (BYTE)mString[i] << 8 | (BYTE)mString[i + 1];
			// ���𖳎�����
			i++;
			str++;
		} else {
			// 1�o�C�g����
			code = mString[i];
		}
		str++;
#endif
		if (!createFontTexture(code, lineCount)) {
			return false;
		}
		if (!createVertexBuffer(lineCount, indexNum)) {
			return false;
		}
		indexNum++;
		// ���s
		if (code == 10) {
			indexNum = 0;
			lineCount++;
			mTextures.emplace_back();
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �t�H���g�e�N�X�`���[���쐬����
/// @param aCode �����R�[�h
/// @return ���� ����(true)
bool FontRenderer::createFontTexture(const UINT& aCode, const int& aLineCount)
{
	// �t�H���g�r�b�g�}�b�v�擾
	const auto hdc = FONT_LOADER->hdc(mFontName);
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
	DWORD size = GetGlyphOutline(hdc, aCode, GGO_GRAY4_BITMAP, &gm, 0, NULL, &mat);
	BYTE* pMono = new BYTE[size];
	GetGlyphOutline(hdc, aCode, GGO_GRAY4_BITMAP, &gm, size, pMono, &mat);

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
	hr = D3D11->getDevice()->CreateTexture2D(&desc, 0, &tex2D);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	hr = D3D11->getContext()->Map(tex2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &hMappedResource);
	if (FAILED(hr)) {
		return false;
	}

	// �t�H���g���̏�������
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	int iOfsX = gm.gmptGlyphOrigin.x;
	int iOfsY = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int iBmpW = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
	int iBmpH = gm.gmBlackBoxY;
	int grad = 16;
	int x, y;
	DWORD alpha, col;
	memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
	for (y = iOfsY; y < iOfsY + iBmpH; y++) {
		for (x = iOfsX; x < iOfsX + iBmpW; x++) {
			alpha = (255 * pMono[x - iOfsX + iBmpW * (y - iOfsY)]) / grad;
			col = 0x00ffffff | (alpha << 24);
			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &col, sizeof(DWORD));
		}
	}
	D3D11->getContext()->Unmap(tex2D, 0);
	delete[] pMono;

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	// ShaderResourceView���쐬����
	ID3D11ShaderResourceView* texture;
	hr = D3D11->getDevice()->CreateShaderResourceView(tex2D, &srvDesc, &texture);
	if (FAILED(hr)) {
		return false;
	}

	// vector�ɒǉ�
	TextureData texData;
	texData.texture = texture;
	texData.nextPos = (float)iBmpW / 2.0f;
	texData.newLine = 0;
	texData.hideFlag = false;
	if (aCode == 32 || aCode == 12288) {
		// �X�y�[�X
		texData.nextPos = (float)gm.gmCellIncX / 2.0f;
		texData.hideFlag = true;
	} else if (aCode == 9) {
		// �C���f���g
		texData.nextPos = (float)gm.gmCellIncX * 2.0f;
		texData.hideFlag = true;
	} else if (aCode == 10) {
		// ���s
		texData.newLine = (float)gm.gmptGlyphOrigin.y;
		texData.hideFlag = true;
	}
	// �T�C�Y���L�^
	texData.texSize.x = (float)desc.Width / 4.0f;
	texData.texSize.y = (float)desc.Height / 4.0f;

	mTextures[aLineCount].emplace_back(texData);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @param aIndexNum �z��ԍ�
/// @return �쐬���� ����(true)
bool FontRenderer::createVertexBuffer(const int& aLineCount, const int& aIndexNum)
{
	VertexData vertexes[8];
	Vector2 size = mTextures[aLineCount][aIndexNum].texSize;

	// ���_0
	vertexes[0].pos[0] = -size.x;
	vertexes[0].pos[1] = -size.y;
	vertexes[0].uv[0] = 0.0f;
	vertexes[0].uv[1] = 1.0f;
	vertexes[0].nor[2] = -1.0f;
	// ���_1
	vertexes[1].pos[0] = size.x;
	vertexes[1].pos[1] = -size.y;
	vertexes[1].uv[0] = 1.0f;
	vertexes[1].uv[1] = 1.0f;
	vertexes[1].nor[2] = -1.0f;
	// ���_2
	vertexes[2].pos[0] = -size.x;
	vertexes[2].pos[1] = size.y;
	vertexes[2].uv[0] = 0.0f;
	vertexes[2].uv[1] = 0.0f;
	vertexes[2].nor[2] = -1.0f;
	// ���_3
	vertexes[3].pos[0] = size.x;
	vertexes[3].pos[1] = size.y;
	vertexes[3].uv[0] = 1.0f;
	vertexes[3].uv[1] = 0.0f;
	vertexes[3].nor[2] = -1.0f;
	// ���_4
	vertexes[4].pos[0] = -size.x;
	vertexes[4].pos[1] = -size.y;
	vertexes[4].uv[0] = 0.0f;
	vertexes[4].uv[1] = 1.0f;
	vertexes[4].nor[2] = 1.0f;
	// ���_5
	vertexes[5].pos[0] = size.x;
	vertexes[5].pos[1] = -size.y;
	vertexes[5].uv[0] = 1.0f;
	vertexes[5].uv[1] = 1.0f;
	vertexes[5].nor[2] = 1.0f;
	// ���_6
	vertexes[6].pos[0] = -size.x;
	vertexes[6].pos[1] = size.y;
	vertexes[6].uv[0] = 0.0f;
	vertexes[6].uv[1] = 0.0f;
	vertexes[6].nor[2] = 1.0f;
	// ���_7
	vertexes[7].pos[0] = size.x;
	vertexes[7].pos[1] = size.y;
	vertexes[7].uv[0] = 1.0f;
	vertexes[7].uv[1] = 0.0f;
	vertexes[7].nor[2] = 1.0f;

	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(VertexData) * 8;
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
	hr = D3D11->getDevice()->CreateBuffer(&bufferDesc, &subResource, &mTextures[aLineCount][aIndexNum].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

} // namespace
// EOF
