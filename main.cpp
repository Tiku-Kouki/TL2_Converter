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

	// COM

	HRESULT	 hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	assert(SUCCEEDED(hr));


	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();


	system("pause");

	return 0;
}
