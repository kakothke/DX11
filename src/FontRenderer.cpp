#include "FontRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
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
/// デストラクタ
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
/// 描画
/// @param aString 表示文字
/// @param aTransform 表示位置
void FontRenderer::draw(const LPCTSTR aString, const DirectX::XMFLOAT3X3& aTransform)
{
	// チェック
	if (!mShaderData && mString) {
		return;
	}

	// テクスチャー作成
	if (mString != aString) {
		mString = aString;
		if (!cretaeTexture()) {
			mString = NULL;
			return;
		}
	}

	// Direct3D11取得
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	d3D11->setShader(mShaderData);

	UINT strides = sizeof(FontVertex);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	cBuf->updateColor(mColor, mColor);
	cBuf->updateSprite(aTransform, mAnchor, mPivot, { 1,1 });

	// テクスチャーセット
	d3D11->setTexture(mTexture);

	// 描画
	context->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aShaderFileName シェーダーのファイルパス
void FontRenderer::setShaderData(const char* const aShaderFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// フォントを設定する
void FontRenderer::setFont(const LPCTSTR aFontName)
{
	// テクスチャー作成
	if (mFontName != aFontName) {
		mFontName = aFontName;
		if (mString) {
			!cretaeTexture();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// カラーを設定する
/// @param aColor 色(0~1)
void FontRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// 描画中心位置を設定する
/// @param aPivot 中心位置(x,y){0~1}
void FontRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始位置を設定する
/// @param aAnchor 開始位置(x,y){-1~1}
void FontRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーを作成する
/// @return 結果 成功(true)
bool FontRenderer::cretaeTexture()
{
	UINT code = 0;

#if _UNICODE
	for (int i = 0; i < lstrlen(mString); i++) {
		code = (UINT)mString[i];
		if (!createFontTexture(code)) {
			return false;
		}
	}
#else
	LPCTSTR str = mString;
	for (int i = 0; i < lstrlen(mString); i++, str++) {
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
		if (!createFontTexture(code)) {
			return false;
		}
	}
#endif

	return true;
}

//-------------------------------------------------------------------------------------------------
/// フォントテクスチャーを作成する
/// @param aCode 文字のコード
/// @return 結果 成功(true)
bool FontRenderer::createFontTexture(const UINT& aCode)
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
	int iBmpW = (gm.gmBlackBoxX + 3) / 4 * 4;
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
	if (mTexture) {
		mTexture->Release();
		mTexture = nullptr;
	}
	hr = device->CreateShaderResourceView(tex2D, &srvDesc, &mTexture);
	if (FAILED(hr)) {
		return false;
	}

	// 頂点バッファを作成する
	if (!createVertexBuffer()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @return 作成結果 成功(true)
bool FontRenderer::createVertexBuffer()
{
	FontVertex vertexes[4];
	createMesh(vertexes);
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(FontVertex) * 4;
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
/// メッシュ作成
/// @param aVertexes 頂点データ
void FontRenderer::createMesh(FontVertex* aVertexes)
{
	// テクスチャーのサイズを参照
	ID3D11Resource* res = nullptr;
	mTexture->GetResource(&res);
	ID3D11Texture2D* tex2D = nullptr;
	res->QueryInterface(&tex2D);
	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);
	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

	float width = (float)desc.Width / 4;
	float height = (float)desc.Height / 4;

	// 表面
	{
		// 頂点0
		aVertexes[0].pos[0] = -width;
		aVertexes[0].pos[1] = -height;
		aVertexes[0].uv[0] = 0;
		aVertexes[0].uv[1] = 1;
		// 頂点1
		aVertexes[1].pos[0] = width;
		aVertexes[1].pos[1] = -height;
		aVertexes[1].uv[0] = 1;
		aVertexes[1].uv[1] = 1;
		// 頂点2
		aVertexes[2].pos[0] = -width;
		aVertexes[2].pos[1] = height;
		aVertexes[2].uv[0] = 0;
		aVertexes[2].uv[1] = 0;
		//// 頂点3
		aVertexes[3].pos[0] = width;
		aVertexes[3].pos[1] = height;
		aVertexes[3].uv[0] = 1;
		aVertexes[3].uv[1] = 0;
	}
}

} // namespace
// EOF
