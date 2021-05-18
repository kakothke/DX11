#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <fstream>
#include <string>
#include "SplitString.h"
#include "Direct3D11.h"
#include "OBJFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
OBJLoader::OBJLoader()
	: mOBJData()
{
	mOBJData.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
OBJLoader::~OBJLoader()
{
	if (!mOBJData.empty()) {
		mOBJData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C����ǂݍ���
/// @param aOBJList �ǂݍ��݂���OBJ�t�@�C�����w�肷��\����
bool OBJLoader::load(const OBJList& aOBJList)
{
	if (mOBJData.count(aOBJList)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertexData> vertexData;
	if (!createMesh(aOBJList, vertexData)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̃��b�V���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aOBJList, vertexData)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̒��_�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aOBJList)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̃C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	vertexData.clear();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C����j������
/// @param aObjList �j��������OBJ�t�@�C�����w�肷��\����
void OBJLoader::release(const OBJList& aOBJList)
{
	if (mOBJData.count(aOBJList)) {
		mOBJData.erase(aOBJList);
	}
	MessageBox(nullptr, TEXT("���݂��Ȃ�OBJ�f�[�^��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C���̃f�[�^���擾����
/// @param aObjList �擾������OBJ�t�@�C�����w�肷��\����
OBJData* OBJLoader::getObjData(OBJList aOBJList)
{
	if (mOBJData.count(aOBJList)) {
		return &mOBJData[aOBJList];
	}
	MessageBox(nullptr, TEXT("�ǂݍ��܂�Ă��Ȃ�OBJ�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
/// @param aOBJList �ǂݍ��݂���OBJ�t�@�C�����w�肷��\����
/// @param aVertexData �v�f��ǉ������钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createMesh(const OBJList& aOBJList, std::vector<OBJVertexData>& aVertexData)
{
	// �t�@�C����ǂݍ���
	std::ifstream ifs(OBJFileName::fileName(aOBJList));
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> positions, textures, normals;

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
		// UV���W
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// �@�����W
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
		}
		// �ʏ��
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertexData tmp;
				std::vector<std::string> slashSplit = SplitString::split(spaceSplit[i], '/');
				// ���_���W
				for (UINT j = 0; !positions.empty() && j < positions[0].size(); j++) {
					tmp.pos[j] = positions[std::stoi(slashSplit[0]) - 1][j];
				}
				// UV���W
				for (UINT j = 0; !textures.empty() && j < textures[0].size(); j++) {
					tmp.uv[j] = textures[std::stoi(slashSplit[1]) - 1][j];
				}
				// �@�����W
				for (UINT j = 0; !normals.empty() && j < normals[0].size(); j++) {
					tmp.nor[j] = normals[std::stoi(slashSplit[2]) - 1][j];
				}
				// �e�o�b�t�@�R���e�i�ɒǉ�
				aVertexData.push_back(tmp);
				mOBJData[aOBJList].indexes.push_back(aVertexData.size() - 1);
			}
		}
		// �������Ă���}�e���A���̖��O���o���Ă���
		else if (str.substr(0, 6) == "mtllib") {

		}
		// �g�p���Ă���mtl�t�@�C���̒ǉ�
		else if (str.substr(0, 6) == "usemtl") {

		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @param aOBJList �ǂݍ��݂���OBJ�t�@�C�����w�肷��\����
/// @param aVertexData �Q�Ƃ��钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createVertexBuffer(const OBJList& aOBJList, const std::vector<OBJVertexData>& aVertexData)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(OBJVertexData) * aVertexData.size();
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
		subResource.pSysMem = &aVertexData[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aOBJList].vertexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �C���f�b�N�X�o�b�t�@���쐬����
/// @param aOBJList �ǂݍ��݂���obj�t�@�C�����w�肷��\����
/// @return �쐬���� ����(true)
bool OBJLoader::createIndexBuffer(const OBJList& aOBJList)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(UWORD) * mOBJData[aOBJList].indexes.size();
		// �g�p���@
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND�ݒ�
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
		subResource.pSysMem = &mOBJData[aOBJList].indexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aOBJList].indexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �������float�^�ɕϊ����č��W����push����
/// @tparam T �e���v���[�g����
/// @param aData push����f�[�^��
/// @param aStr float�^�ɒ���������
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
