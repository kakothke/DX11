#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
#include "SplitString.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
OBJLoader::OBJLoader()
	: mOBJData()
{
	mOBJData.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
OBJLoader::~OBJLoader()
{
	if (!mOBJData.empty()) {
		mOBJData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを読み込む
/// @param aFileName 読み込みたいOBJのファイルパス
bool OBJLoader::load(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("OBJファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertexData> vertexData;
	if (!createMesh(aFileName, vertexData)) {
		MessageBox(nullptr, TEXT("OBJファイルのメッシュの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aFileName, vertexData)) {
		MessageBox(nullptr, TEXT("OBJファイルの頂点バッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("OBJファイルのインデックスバッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	vertexData.clear();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを破棄する
/// @param aFileName 破棄したいOBJのファイルパス
void OBJLoader::release(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		mOBJData.erase(aFileName);
	} else {
		MessageBox(nullptr, TEXT("存在しないOBJデータを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルのデータを取得する
/// @param aFileName 取得したいOBJのファイルパス
OBJData* OBJLoader::getObjData(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		return &mOBJData[aFileName];
	}
	MessageBox(nullptr, TEXT("存在しないOBJデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// メッシュを作成する
/// @param aFileName 読み込みたいOBJのファイルパス
/// @param aVertexData 要素を追加させる頂点データ構造体
/// @return 作成結果 成功(true)
bool OBJLoader::createMesh(const char* aFileName, std::vector<OBJVertexData>& aVertexData)
{
	// ファイルを読み込む
	std::ifstream ifs(aFileName);
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> positions, textures, normals;

	std::string str;
	while (getline(ifs, str)) {
		// コメントは無視する
		if (str[0] == '#') {
			continue;
		}
		// 頂点座標
		if (str.substr(0, 2) == "v ") {
			pushAtofVector(positions, SplitString::split(str.substr(2), ' '));
		}
		// UV座標
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// 法線座標
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
		}
		// 面情報
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertexData tmp;
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
				aVertexData.push_back(tmp);
				mOBJData[aFileName].indexes.push_back(aVertexData.size() - 1);
			}
		}
		// 使用しているmtlファイルの追加
		else if (str.substr(0, 6) == "usemtl") {

		}
		// 所属しているマテリアルの名前を覚えておく
		else if (str.substr(0, 6) == "mtllib") {

		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @param aFileName 読み込みたいOBJのファイルパス
/// @param aVertexData 参照する頂点データ構造体
/// @return 作成結果 成功(true)
bool OBJLoader::createVertexBuffer(const char* aFileName, const std::vector<OBJVertexData>& aVertexData)
{
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(OBJVertexData) * aVertexData.size();
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
		subResource.pSysMem = &aVertexData[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aFileName].vertexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// インデックスバッファを作成する
/// @param aFileName 読み込みたいOBJのファイルパス
/// @return 作成結果 成功(true)
bool OBJLoader::createIndexBuffer(const char* aFileName)
{
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(UWORD) * mOBJData[aFileName].indexes.size();
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
		subResource.pSysMem = &mOBJData[aFileName].indexes[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aFileName].indexBuffer
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
void OBJLoader::pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr)
{
	std::vector<T> values;
	for (UINT i = 0; i < aStr.size(); i++) {
		values.push_back(std::stof(aStr[i]));
	}
	aData.push_back(values);
}

} // namespace
// EOF
