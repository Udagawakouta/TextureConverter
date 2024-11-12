#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include <windows.h>

enum Argument
{
	kApplicationPath, // �A�v���P�[�V�����̃p�X
	kFilePath,		  // �n���ꂽ�t�@�C���̃p�X

	NumArgument
};

int main(int argc, char* argv[]) 
{
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	DirectX::ScratchImage LoadTexture(const std::string & filePath);
	DirectX::ScratchImage mipImages = LoadTexture("resources/uvChecker.png");

	// �e�N�X�`���R���o�[�^�[
	TextureConverter converter;
	// �e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath]);
	
	CoUninitialize();
	system("pause");
	return 0;
}

DirectX::ScratchImage LoadTexture(const std::string& filePath) {
	//�e�N�X�`���t�@�C��������Ńv���O�����ň�����悤�ɂ���
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	//�~�b�v�}�b�v�̍쐬
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	//�~�b�v�}�b�v�t���̃f�[�^������
	return mipImages;
}