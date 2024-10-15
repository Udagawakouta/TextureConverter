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

	// 画像の情報
	DirectX::TexMetadata metadata_;
	// 画像のイメージのコンテナ
	DirectX::ScratchImage scratchImage_;
};
