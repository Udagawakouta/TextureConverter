#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include <windows.h>

enum Argument
{
	kApplicationPath, // アプリケーションのパス
	kFilePath,		  // 渡されたファイルのパス

	NumArgument
};

int main(int argc, char* argv[]) 
{
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	DirectX::ScratchImage LoadTexture(const std::string & filePath);
	DirectX::ScratchImage mipImages = LoadTexture("resources/uvChecker.png");

	// テクスチャコンバーター
	TextureConverter converter;
	// テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);
	
	CoUninitialize();
	system("pause");
	return 0;
}

DirectX::ScratchImage LoadTexture(const std::string& filePath) {
	//テクスチャファイルを挟んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	//ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	//ミップマップ付きのデータを消す
	return mipImages;
}