#include "ObjLoader.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <fstream>
#include <string>
#include "SplitString.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ObjLoader::ObjLoader()
	: mObjData()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ObjLoader::~ObjLoader()
{
}

//-------------------------------------------------------------------------------------------------
/// objファイルを読み込む
/// @param aObjList 読み込むobjファイル
bool ObjLoader::load(ObjList aObjList)
{
	if (!createMesh(aObjList)) {
		MessageBox(nullptr, TEXT("メッシュの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer()) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer()) {
		MessageBox(nullptr, TEXT("インデックスバッファの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 読み込んだobjファイルを破棄する
void ObjLoader::release(ObjList aObjList)
{
	mObjData.erase(aObjList);
}

//-------------------------------------------------------------------------------------------------
/// objファイルのデータを返す
const ObjData& ObjLoader::objData(ObjList aObjList)
{
	return mObjData[aObjList];
}

//-------------------------------------------------------------------------------------------------
/// メッシュを作成する
bool ObjLoader::createMesh(ObjList aObjList)
{
	// ファイルを読み込む
	std::ifstream ifs(ObjFilePath::filePath(aObjList));
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<double>> positions, normals, textures;
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
		// 法線座標
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
		}
		// テクスチャ座標
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// 面情報
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> space = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < space.size(); i++) {
				VertexData tmpData;
				std::vector<std::string> slash = SplitString::split(space[i], '/');
				for (UINT j = 0; positions.size() > 0 && j < positions[0].size(); j++) {
					tmpData.position[j] = positions[std::stoi(slash[0]) - 1][j];
				}
				for (UINT j = 0; textures.size() > 0 && j < textures[0].size(); j++) {
					tmpData.texture[j] = textures[std::stoi(slash[1]) - 1][j];
				}
				for (UINT j = 0; normals.size() > 0 && j < normals[0].size(); j++) {
					tmpData.normal[j] = normals[std::stoi(slash[2]) - 1][j];
				}
				// 各バッファリストに追加
				mObjData[aObjList].vertexData.push_back(tmpData);
				mObjData[aObjList].indexes.push_back(mObjData[aObjList].vertexData.size() - 1);
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
bool ObjLoader::createVertexBuffer()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
/// インデックスバッファを作成する
bool ObjLoader::createIndexBuffer()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
/// 文字列をfloat型に変換して座標情報をpushする
template <typename T>
void ObjLoader::pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr)
{
	std::vector<T> values;
	for (UINT i = 0; i < aStr.size(); i++) {
		values.push_back(std::stod(aStr[i]));
	}
	aData.push_back(values);
}

} // namespace
// EOF
