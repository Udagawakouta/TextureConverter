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
	/// </summary>
	/// <param name = "filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filePath);
	
private:

	/// <summary>
	/// フォルダパスとファイル名を分離する
	/// </summary>
	/// <param name = "filePath">ファイルパス</param>
	void SeparateFilepath(const std::wstring& filePath);

	void LoadWICTextureFromFile(const std::string& filepath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	// 画像の情報
	DirectX::TexMetadata metadata_;
	// 画像のイメージのコンテナ
	DirectX::ScratchImage scratchImage_;

	// ディレクトリパス
	std::wstring directoryPath_;
	// ファイル名
	std::wstring fileName_;
	// ファイル拡張子
	std::wstring fileExt_;
};
