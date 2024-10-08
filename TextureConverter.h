#pragma once
#include <string>

// �e�N�X�`���R���o�[�^�[
class TextureConverter
{
public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// <summary>
	/// <param name = "filePath">�t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:
	void LoadWICTextureFromFile(const std::string& filepath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
};
