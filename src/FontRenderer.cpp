#include "FontRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
FontRenderer::FontRenderer()
	: mString(NULL)
	, mFontName(NULL)
{
}

//-------------------------------------------------------------------------------------------------
FontRenderer::~FontRenderer()
{
}

//-------------------------------------------------------------------------------------------------
void FontRenderer::draw(const LPCTSTR aString, const LPCTSTR aFontName)
{
	if (mString != aString || mFontName != aFontName) {
		mString = aString;
		mFontName = aFontName;
		if (!cretaeTexture()) {
			return;
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool FontRenderer::cretaeTexture()
{
	// 文字コード取得
	UINT code = 0;
#if _UNICODE
	code = (UINT)*mString;
#else
	if (IsDBCSLeadByte(*aString)) {
		code = (BYTE)aString[0] << 8 | (BYTE)aString[1];
	} else {
		code = aString[0];
	}
#endif

	// フォントビットマップ取得
	auto hdc = FontLoader::getInst()->hdc(mFontName);
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 Mat = { {0,1}, {0,0}, {0,0}, {0,1} };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, 0, NULL, &Mat);
	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &Mat);

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
	static auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateTexture2D(&desc, 0, &tex2D);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	static auto context = Direct3D11::getInst()->getContext();
	hr = context->Map(tex2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &hMappedResource);
	if (FAILED(hr)) {
		return false;
	}

	// フォント情報の書き込み
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	int iOfs_x = gm.gmptGlyphOrigin.x;
	int iOfs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int iBmp_w = (gm.gmBlackBoxX + 3) / 4 * 4;/*gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;*/
	int iBmp_h = gm.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD alpha, col;
	memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++) {
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++) {
			alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
			col = 0x00ffffff | (alpha << 24);
			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &col, sizeof(DWORD));
		}
	}
	context->Unmap(tex2D, 0);
	delete[] ptr;

	return true;
}

} // namespace
// EOF
