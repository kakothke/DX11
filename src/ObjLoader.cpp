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
/// �R���X�g���N�^
ObjLoader::ObjLoader()
	: mObjData()
	, mVertexData()
{
	mObjData.clear();
	mVertexData.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
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
/// obj�t�@�C�����쐬����
/// @param aObjList �ǂݍ��݂���obj�t�@�C�����w�肷��\����
bool ObjLoader::load(ObjList aObjList)
{
	if (!mVertexData.empty()) {
		mVertexData.clear();
	}
	if (!createMesh(aObjList)) {
		MessageBox(nullptr, TEXT("���b�V���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aObjList)) {
		MessageBox(nullptr, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aObjList)) {
		MessageBox(nullptr, TEXT("�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	mVertexData.clear();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �ǂݍ���obj�t�@�C����j������
/// @param aObjList �j��������obj�t�@�C�����w�肷��\����
void ObjLoader::release(ObjList aObjList)
{
	mObjData.erase(aObjList);
}

//-------------------------------------------------------------------------------------------------
/// obj�t�@�C���̃f�[�^��Ԃ�
/// @param aObjList �~����obj�t�@�C�����w�肷��\����
ObjData* ObjLoader::getObjData(ObjList aObjList)
{
	return &mObjData[aObjList];
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
/// @param aObjList �ǂݍ��݂���obj�t�@�C�����w�肷��\����
/// @return �쐬���� ����(true)
bool ObjLoader::createMesh(ObjList aObjList)
{
	// �t�@�C����ǂݍ���
	std::ifstream ifs(ObjFileName::fileName(aObjList));
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> positions, normals, textures;

	std::string str;
	while (getline(ifs, str)) {
		// �R�����g�͖�������
		if (str[0] == '#') {
			continue;
		}
		// ���_���W
		if (str.substr(0, 2) == "v ") {
			pushAtofVector(positions, SplitString::split(str.substr(2), ' '));
			// x���𔽓]������
			//positions[positions.size() - 1][0] *= 1.0f;
		}
		// �@�����W
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
			// x���𔽓]������
			//normals[normals.size() - 1][0] *= 1.0f;
		}
		// �e�N�X�`�����W
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// �ʏ��
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				ObjVertexData tmp;
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
				mVertexData.push_back(tmp);
				mObjData[aObjList].indexes.push_back(mVertexData.size() - 1);
			}
			// �|���S���̍쐬�̒��_���Ԃ𔽓]����
			/*int size = mObjData[aObjList].indexes.size();
			int temp = mObjData[aObjList].indexes[size - 1];
			mObjData[aObjList].indexes[size - 1] = mObjData[aObjList].indexes[size - 3];
			mObjData[aObjList].indexes[size - 3] = temp;*/
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @param aObjList �ǂݍ��݂���obj�t�@�C�����w�肷��\����
/// @return �쐬���� ����(true)
bool ObjLoader::createVertexBuffer(ObjList aObjList)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(ObjVertexData) * mVertexData.size();
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
		subResource.pSysMem = &mVertexData[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
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
/// �C���f�b�N�X�o�b�t�@���쐬����
/// @param aObjList �ǂݍ��݂���obj�t�@�C�����w�肷��\����
/// @return �쐬���� ����(true)
bool ObjLoader::createIndexBuffer(ObjList aObjList)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(UWORD) * mObjData[aObjList].indexes.size();
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
		subResource.pSysMem = &mObjData[aObjList].indexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
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
/// �������float�^�ɕϊ����č��W����push����
/// @tparam T �e���v���[�g����
/// @param aData push����f�[�^��
/// @param aStr float�^�ɒ���������
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
