#pragma once
#include <string>
#include "external/DirectXTex/DirectXTex.h"

// �e�N�X�`���R���o�[�^�[
class TextureConverter
{
public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name = "filePath">�t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:

	/// <summary>
	/// �t�H���_�p�X�ƃt�@�C�����𕪗�����
	/// </summary>
	/// <param name = "filePath">�t�@�C���p�X</param>
	void SeparateFilepath(const std::wstring& filePath);

	void LoadWICTextureFromFile(const std::string& filepath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	// �摜�̏��
	DirectX::TexMetadata metadata_;
	// �摜�̃C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;

	// �f�B���N�g���p�X
	std::wstring directoryPath_;
	// �t�@�C����
	std::wstring fileName_;
	// �t�@�C���g���q
	std::wstring fileExt_;
};
