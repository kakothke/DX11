#include "TextureLoader.h"
#include <codecvt>

//-------------------------------------------------------------------------------------------------
#include <WICTextureLoader11.h>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
TextureLoader::TextureLoader()
	: mTexture()
{
}

//-------------------------------------------------------------------------------------------------
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
/// �e�N�X�`���쐬
bool TextureLoader::load(const char* const aFileName)
{
	if (mTexture.count(aFileName)) {
		// �e�N�X�`���[�͓�d�ǂݍ��݂̃G���[���m�����Ȃ�
		return false;
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wFileName = cv.from_bytes(aFileName);

	HRESULT hr;
	static auto device = Direct3D11::getInst()->getDevice();
	hr = DirectX::CreateWICTextureFromFile(device, wFileName.c_str(), nullptr, &mTexture[aFileName]);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("�e�N�X�`���[�̍쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void TextureLoader::release(const char* const aFileName)
{
	if (mTexture.count(aFileName)) {
		mTexture[aFileName]->Release();
		mTexture[aFileName] = nullptr;
		mTexture.erase(aFileName);
	} else {
		MessageBox(nullptr, TEXT("���݂��Ȃ��e�N�X�`���[��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
ID3D11ShaderResourceView* TextureLoader::getTexture(const char* const aFileName)
{
	if (mTexture.count(aFileName)) {
		return mTexture[aFileName];
	}
	// �`�掞�ɖ��t���[���Ă΂�鏈���Ȃ̂ŃG���[���m�͂��Ȃ�
	return nullptr;
}

} // namespace
// EOF
