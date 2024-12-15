#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include "Windows.h"

enum Argument {
	kApplicationPath,
	kFilePath,

	NumArgument
};



int main(int argc,char* argv[]) {
	


	for (int i = 0; i < argc; i++) {

		printf(argv[i]);

		//
		printf("\n");

	}

	assert(argc >= NumArgument);

	// COM ライブラリの初期化

	HRESULT	 hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	assert(SUCCEEDED(hr));

	 //　テクスチャコンバータ変換
	TextureConverter converter;
	//　テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// Comライブラリの終了
	CoUninitialize();


	system("pause");

	return 0;
}
