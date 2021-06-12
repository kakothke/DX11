#include "SpriteLoader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Resource.h"

namespace DX11 {

//-------------------------------------------------------------------------------------------------
SpriteLoader::SpriteLoader()
	: mSpriteData()
{
	mSpriteData.clear();	
}

//-------------------------------------------------------------------------------------------------
SpriteLoader::~SpriteLoader()
{
	if (!mSpriteData.empty()) {
		mSpriteData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
bool SpriteLoader::load(const char* const aFileName)
{
	if (mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("スプライトの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("読み込もうとしているスプライトが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!Resource::getInst()->Texture()->load(aFileName)) {
		return false;
	}
	if (!createVertexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。(Sprite)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mSpriteData.erase(aFileName);
		return false;
	}
	mSpriteData[aFileName].fileName = aFileName;

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteLoader::release(const char* const aFileName)
{
	if (mSpriteData.count(aFileName)) {
		mSpriteData.erase(aFileName);
	} else {
		MessageBox(nullptr, TEXT("存在しないスプライトを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
SpriteData* SpriteLoader::getSpriteData(const char* const aFileName)
{
	if (mSpriteData.count(aFileName)) {
		return &mSpriteData[aFileName];
	}
	MessageBox(nullptr, TEXT("存在しないスプライトを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
bool SpriteLoader::createVertexBuffer(const char* const aFileName)
{
	SpriteVertex vertexes[4];
	createMesh(aFileName, vertexes);
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(SpriteVertex) * 4;
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
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mSpriteData[aFileName].vertexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteLoader::createMesh(const char* const aFileName, SpriteVertex* aVertexes)
{
	// テクスチャーのサイズを参照
	ID3D11Resource* res = nullptr;
	Resource::getInst()->Texture()->getTexture(aFileName)->GetResource(&res);
	ID3D11Texture2D* tex2D = nullptr;
	res->QueryInterface(&tex2D);
	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);

	// そのままだと大きすぎるので除算
	float width = (float)desc.Width;
	float height = (float)desc.Height;
	width /= 2;
	height /= 2;

	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

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
