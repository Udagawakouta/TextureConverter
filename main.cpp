#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include "TextureManager.h"
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

	/*DirectX::ScratchImage LoadTexture(const std::string & filePath);
	DirectX::ScratchImage mipImages = LoadTexture("resources/uvChecker.png");*/

	// テクスチャコンバーター
	TextureConverter converter;
	// テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);
	
	CoUninitialize();
	system("pause");
	return 0;
}



std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}

std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
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