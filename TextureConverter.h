#pragma once
#include <string>
#include "external/DirectXTex/DirectXTex.h"

// テクスチャコンバーター
class TextureConverter
{
public:
	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// <summary>
	/// <param name = "filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:
	void LoadWICTextureFromFile(const std::string& filepath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);


	DirectX::TexMetadata metadata_;

	DirectX::ScratchImage scratchImage_;
};
