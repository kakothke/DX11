#include "ObjLoader.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <fstream>
#include <string>
#include "SplitString.h"
#include "Direct3D11.h"
#include "ObjFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ObjLoader::ObjLoader()
	: mObjData()
	, mVertexData()
{
	mObjData.clear();
	mVertexData.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ObjLoader::~ObjLoader()
{
	if (!mObjData.empty()) {
		mObjData.clear();
	}
	if (!mVertexData.empty()) {
		mVertexData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// objファイルを作成する
/// @param aObjList 読み込みたいobjファイルを指定する構造体
bool ObjLoader::load(ObjList aObjList)
{
	if (!mVertexData.empty()) {
		mVertexData.clear();
	}
	if (!createMesh(aObjList)) {
		MessageBox(nullptr, TEXT("メッシュの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aObjList)) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aObjList)) {
		MessageBox(nullptr, TEXT("インデックスバッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	mVertexData.clear();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 読み込んだobjファイルを破棄する
/// @param aObjList 破棄したいobjファイルを指定する構造体
void ObjLoader::release(ObjList aObjList)
{
	mObjData.erase(aObjList);
}

//-------------------------------------------------------------------------------------------------
/// objファイルのデータを返す
/// @param aObjList 欲しいobjファイルを指定する構造体
ObjData* ObjLoader::getObjData(ObjList aObjList)
{
	return &mObjData[aObjList];
}

//-------------------------------------------------------------------------------------------------
/// メッシュを作成する
/// @param aObjList 読み込みたいobjファイルを指定する構造体
/// @return 作成結果 成功(true)
bool ObjLoader::createMesh(ObjList aObjList)
{
	// ファイルを読み込む
	std::ifstream ifs(ObjFileName::fileName(aObjList));
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> positions, normals, textures;

	std::string str;
	while (getline(ifs, str)) {
		// コメントは無視する
		if (str[0] == '#') {
			continue;
		}
		// 頂点座標
		if (str.substr(0, 2) == "v ") {
			pushAtofVector(positions, SplitString::split(str.substr(2), ' '));
			// x軸を反転させる
			//positions[positions.size() - 1][0] *= 1.0f;
		}
		// 法線座標
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
			// x軸を反転させる
			//normals[normals.size() - 1][0] *= 1.0f;
		}
		// テクスチャ座標
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// 面情報
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				ObjVertexData tmp;
				std::vector<std::string> slashSplit = SplitString::split(spaceSplit[i], '/');
				// 頂点座標
				for (UINT j = 0; !positions.empty() && j < positions[0].size(); j++) {
					tmp.pos[j] = positions[std::stoi(slashSplit[0]) - 1][j];
				}
				// UV座標
				for (UINT j = 0; !textures.empty() && j < textures[0].size(); j++) {
					tmp.uv[j] = textures[std::stoi(slashSplit[1]) - 1][j];
				}
				// 法線座標
				for (UINT j = 0; !normals.empty() && j < normals[0].size(); j++) {
					tmp.nor[j] = normals[std::stoi(slashSplit[2]) - 1][j];
				}
				// 各バッファコンテナに追加
				mVertexData.push_back(tmp);
				mObjData[aObjList].indexes.push_back(mVertexData.size() - 1);
			}
			// ポリゴンの作成の頂点順番を反転する
			/*int size = mObjData[aObjList].indexes.size();
			int temp = mObjData[aObjList].indexes[size - 1];
			mObjData[aObjList].indexes[size - 1] = mObjData[aObjList].indexes[size - 3];
			mObjData[aObjList].indexes[size - 3] = temp;*/
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @param aObjList 読み込みたいobjファイルを指定する構造体
/// @return 作成結果 成功(true)
bool ObjLoader::createVertexBuffer(ObjList aObjList)
{
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(ObjVertexData) * mVertexData.size();
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
		subResource.pSysMem = &mVertexData[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mObjData[aObjList].vertexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// インデックスバッファを作成する
/// @param aObjList 読み込みたいobjファイルを指定する構造体
/// @return 作成結果 成功(true)
bool ObjLoader::createIndexBuffer(ObjList aObjList)
{
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(UWORD) * mObjData[aObjList].indexes.size();
		// 使用方法
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND設定
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
		subResource.pSysMem = &mObjData[aObjList].indexes[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mObjData[aObjList].indexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 文字列をfloat型に変換して座標情報をpushする
/// @tparam T テンプレート引数
/// @param aData pushするデータ先
/// @param aStr float型に直す文字列
template <typename T>
void ObjLoader::pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr)
{
	std::vector<T> values;
	for (UINT i = 0; i < aStr.size(); i++) {
		values.push_back(std::stof(aStr[i]));
	}
	aData.push_back(values);
}

} // namespace
// EOF
