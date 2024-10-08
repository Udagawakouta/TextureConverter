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

	// テクスチャコンバーター
	TextureConverter converter;
	// テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);
	
	CoUninitialize();
	system("pause");
	return 0;
}