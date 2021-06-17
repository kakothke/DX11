#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
#include <WICTextureLoader11.h>
#include <codecvt>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TextureLoader::TextureLoader()
	: mTexture()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TextureLoader::~TextureLoader()
{
	for (auto tex : mTexture) {
		if (tex.second) {
			tex.second->Release();
			tex.second = nullptr;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`�����쐬����
/// @param aFileName �t�@�C���p�X
/// @return ���� ����(true)
bool TextureLoader::load(const char* const aFileName)
{
	if (mTexture.count(aFileName)) {
		// �e�N�X�`���[�͓�d�ǂݍ��݂̃G���[���m�����Ȃ�
		return false;
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wFileName = cv.from_bytes(aFileName);

	HRESULT hr;
	const auto device = Direct3D11::getInst()->getDevice();
	hr = DirectX::CreateWICTextureFromFile(device, wFileName.c_str(), nullptr, &mTexture[aFileName]);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("�e�N�X�`���[�̍쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aFileName �t�@�C���p�X
void TextureLoader::release(const char* const aFileName)
{
	if (!mTexture.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ��e�N�X�`���[��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return;
	}
	mTexture[aFileName]->Release();
	mTexture[aFileName] = nullptr;
	mTexture.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`���[���擾����
/// @param aFileName �t�@�C���p�X
/// @return �e�N�X�`���[
ID3D11ShaderResourceView* TextureLoader::getTexture(const char* const aFileName)
{
	if (!mTexture.count(aFileName)) {
		// �`�掞�ɖ��t���[���Ă΂�鏈���Ȃ̂ŃG���[���m�͂��Ȃ�
		return nullptr;
	}
	return mTexture[aFileName];
}

} // namespace
// EOF
