#include "FontRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
FontRenderer::FontRenderer()
	: mString(NULL)
	, mFontName(NULL)
	, mTextures()
	, mShaderData()
	, mColor()
	, mPivot(0.0f, 0.0f)
	, mAnchor(0.0f, 0.0f)
{
	mTextures.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
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
/// 描画
/// @param aString 表示文字
/// @param aTransform 表示位置
void FontRenderer::draw(const LPCTSTR aString, Transform aTransform)
{
	// チェック
	if (!mShaderData && mString) {
		return;
	}

	// テクスチャー作成
	if (mString != aString) {
		mString = aString;
		if (!cretaeFontMesh()) {
			mString = NULL;
			return;
		}
	}

	// Direct3D11取得
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto constantBuffer = d3D11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	d3D11->setShader(mShaderData);

	UINT strides = sizeof(FontVertex);
	UINT offsets = 0;

	float initPosX = aTransform.pos.x;

	// 描画初期位置を変更
	for (const auto line : mTextures) {
		aTransform.pos.x = initPosX;
		// 初期位置計算
		for (int i = 0; i < line.size(); i++) {
			if (i > 0) {
				aTransform.pos.x -= line[i].nextPos / 2;
			}
		}
		// 描画
		float nextPos = 0.0f;
		for (const auto tex : line) {
			if (!tex.hideFlag) {
				// IAに設定する頂点バッファの指定
				context->IASetVertexBuffers(0, 1, &tex.vertexBuffer, &strides, &offsets);

				// コンスタントバッファを更新
				constantBuffer->updateColor(mColor, mColor);
				constantBuffer->setSpriteMatrixW(aTransform, mPivot);
				constantBuffer->setSpriteMatrixP(mAnchor);
				constantBuffer->updateSprite();

				// テクスチャーセット
				d3D11->setTexture(tex.texture);

				// 描画
				context->Draw(8, 0);
			}

			// 描画位置をずらす
			nextPos += tex.nextPos;
			aTransform.pos.x += tex.nextPos;
			if (tex.newLine != 0) {
				aTransform.pos.x -= nextPos;
				nextPos = 0;
				aTransform.pos.y += tex.newLine;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName シェーダーのファイルパス
void FontRenderer::setShader(const LPCSTR aFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// フォントを設定する
/// @param aFontName フォント名
void FontRenderer::setFont(const LPCTSTR aFontName)
{
	if (mFontName != aFontName) {
		mFontName = aFontName;
		// テクスチャー作成
		if (mString) {
			cretaeFontMesh();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// カラーを設定する
/// @param aColor カラー
void FontRenderer::setColor(const Color& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// 描画中心位置を設定する
/// @param aX 原点x(-1~1)
/// @param aY 原点y(-1~1)
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
/// 描画開始位置を設定する
/// @param aX 描画開始位置x(-1~1)
/// @param aY 描画開始位置y(-1~1)
void FontRenderer::setAnchor(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mAnchor.x = aX;
	mAnchor.y = aY;
}

//-------------------------------------------------------------------------------------------------
/// フォントメッシュを作成する
/// @return 結果 成功(true)
bool FontRenderer::cretaeFontMesh()
{
	// フォントメッシュ初期化
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

	// テクスチャー作成
	UINT code = 0;
	int lineCount = 0;
	int indexNum = 0;
	LPCTSTR str = mString;
	for (int i = 0; i < lstrlen(mString); i++) {
#if _UNICODE
		code = (UINT)mString[i];
#else
		if (IsDBCSLeadByte(*str)) {
			// 2バイト文字
			code = (BYTE)mString[i] << 8 | (BYTE)mString[i + 1];
			// 次を無視する
			i++;
			str++;
		} else {
			// 1バイト文字
			code = mString[i];
		}
		str++;
#endif
		if (!createFontTexture(code, lineCount)) {
			return false;
		}
		if (!createVertexBuffer(indexNum, lineCount)) {
			return false;
		}
		indexNum++;
		// 改行
		if (code == 10) {
			indexNum = 0;
			lineCount++;
			mTextures.emplace_back();
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// フォントテクスチャーを作成する
/// @param aCode 文字コード
/// @return 結果 成功(true)
bool FontRenderer::createFontTexture(const UINT& aCode, const int& aLineCount)
{
	// フォントビットマップ取得
	const auto hdc = FontLoader::getInst()->hdc(mFontName);
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
	DWORD size = GetGlyphOutline(hdc, aCode, GGO_GRAY4_BITMAP, &gm, 0, NULL, &mat);
	BYTE* pMono = new BYTE[size];
	GetGlyphOutline(hdc, aCode, GGO_GRAY4_BITMAP, &gm, size, pMono, &mat);

	// テクスチャ作成
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

	// フォント情報の書き込み
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
	context->Unmap(tex2D, 0);
	delete[] pMono;

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	// ShaderResourceViewを作成する
	ID3D11ShaderResourceView* texture;
	hr = device->CreateShaderResourceView(tex2D, &srvDesc, &texture);
	if (FAILED(hr)) {
		return false;
	}

	// vectorに追加
	TextureData texData;
	texData.texture = texture;
	texData.nextPos = (float)iBmpW / 2.0f;
	texData.newLine = 0;
	texData.hideFlag = false;
	if (aCode == 32 || aCode == 12288) {
		// スペース
		texData.nextPos = (float)gm.gmCellIncX / 2.0f;
		texData.hideFlag = true;
	} else if (aCode == 9) {
		// インデント
		texData.nextPos = (float)gm.gmCellIncX * 2.0f;
		texData.hideFlag = true;
	} else if (aCode == 10) {
		// 改行
		texData.newLine = (float)gm.gmptGlyphOrigin.y;
		texData.hideFlag = true;
	}
	mTextures[aLineCount].emplace_back(texData);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @param aIndexNum 配列番号
/// @return 作成結果 成功(true)
bool FontRenderer::createVertexBuffer(const int& aIndexNum, const int& aLineCount)
{
	FontVertex vertexes[8];
	createMesh(vertexes, aIndexNum, aLineCount);
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(FontVertex) * 8;
		// 使用方法
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND設定
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// リソースへのCPUのアクセス権限についての設定
		bufferDesc.CPUAccessFlags = 0;
		// リソースオプションのフラグ
		bufferDesc.MiscFlags = 0;
		// 構造体のサイズ
		bufferDesc.StructureByteStride = 0;
	}

	// リソース情報
	D3D11_SUBRESOURCE_DATA subResource;
	{
		// バッファの中身の設定
		subResource.pSysMem = &vertexes[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	HRESULT hr;
	const auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateBuffer(&bufferDesc, &subResource, &mTextures[aLineCount][aIndexNum].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッシュ作成
/// @param aVertexes 頂点データ
/// @param aIndexNum 配列番号
void FontRenderer::createMesh(FontVertex* aVertexes, const int& aIndexNum, const int& aLineCount)
{
	// テクスチャーのサイズを参照
	ID3D11Resource* res = nullptr;
	ID3D11Texture2D* tex2D = nullptr;
	D3D11_TEXTURE2D_DESC desc = {};
	mTextures[aLineCount][aIndexNum].texture->GetResource(&res);
	res->QueryInterface(&tex2D);
	tex2D->GetDesc(&desc);
	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

	float width = (float)desc.Width / 4.0f;
	float height = (float)desc.Height / 4.0f;

	// 表面
	{
		// 頂点0
		aVertexes[0].pos[0] = -width;
		aVertexes[0].pos[1] = -height;
		aVertexes[0].uv[0] = 0.0f;
		aVertexes[0].uv[1] = 1.0f;
		// 頂点1
		aVertexes[1].pos[0] = width;
		aVertexes[1].pos[1] = -height;
		aVertexes[1].uv[0] = 1.0f;
		aVertexes[1].uv[1] = 1.0f;
		// 頂点2
		aVertexes[2].pos[0] = -width;
		aVertexes[2].pos[1] = height;
		aVertexes[2].uv[0] = 0.0f;
		aVertexes[2].uv[1] = 0.0f;
		//// 頂点3
		aVertexes[3].pos[0] = width;
		aVertexes[3].pos[1] = height;
		aVertexes[3].uv[0] = 1.0f;
		aVertexes[3].uv[1] = 0.0f;
		// 頂点4
		aVertexes[4].pos[0] = -width;
		aVertexes[4].pos[1] = -height;
		aVertexes[4].uv[0] = 0.0f;
		aVertexes[4].uv[1] = 1.0f;
		// 頂点5
		aVertexes[5].pos[0] = width;
		aVertexes[5].pos[1] = -height;
		aVertexes[5].uv[0] = 1.0f;
		aVertexes[5].uv[1] = 1.0f;
		// 頂点6
		aVertexes[6].pos[0] = -width;
		aVertexes[6].pos[1] = height;
		aVertexes[6].uv[0] = 0.0f;
		aVertexes[6].uv[1] = 0.0f;
		//// 頂点7
		aVertexes[7].pos[0] = width;
		aVertexes[7].pos[1] = height;
		aVertexes[7].uv[0] = 1.0f;
		aVertexes[7].uv[1] = 0.0f;
	}
}

} // namespace
// EOF
