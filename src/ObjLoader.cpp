#include "ObjLoader.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <fstream>
#include <string>
#include "SplitString.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
ObjLoader::ObjLoader()
	: mObjData()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
ObjLoader::~ObjLoader()
{
}

//-------------------------------------------------------------------------------------------------
/// obj�t�@�C����ǂݍ���
/// @param aObjList �ǂݍ���obj�t�@�C��
bool ObjLoader::load(ObjList aObjList)
{
	if (!createMesh(aObjList)) {
		MessageBox(nullptr, TEXT("���b�V���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer()) {
		MessageBox(nullptr, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer()) {
		MessageBox(nullptr, TEXT("�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �ǂݍ���obj�t�@�C����j������
void ObjLoader::release(ObjList aObjList)
{
	mObjData.erase(aObjList);
}

//-------------------------------------------------------------------------------------------------
/// obj�t�@�C���̃f�[�^��Ԃ�
const ObjData& ObjLoader::objData(ObjList aObjList)
{
	return mObjData[aObjList];
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
bool ObjLoader::createMesh(ObjList aObjList)
{
	// �t�@�C����ǂݍ���
	std::ifstream ifs(ObjFilePath::filePath(aObjList));
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<double>> positions, normals, textures;
	std::string str;
	while (getline(ifs, str)) {
		// �R�����g�͖�������
		if (str[0] == '#') {
			continue;
		}
		// ���_���W
		if (str.substr(0, 2) == "v ") {
			pushAtofVector(positions, SplitString::split(str.substr(2), ' '));
		}
		// �@�����W
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
		}
		// �e�N�X�`�����W
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// �ʏ��
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
				// �e�o�b�t�@���X�g�ɒǉ�
				mObjData[aObjList].vertexData.push_back(tmpData);
				mObjData[aObjList].indexes.push_back(mObjData[aObjList].vertexData.size() - 1);
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
bool ObjLoader::createVertexBuffer()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
/// �C���f�b�N�X�o�b�t�@���쐬����
bool ObjLoader::createIndexBuffer()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
/// �������float�^�ɕϊ����č��W����push����
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
