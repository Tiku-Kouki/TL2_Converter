#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	   HRESULT result = LoadWICTextureFromFile(wFilePath.c_str(),)

}

TextureConverter::~TextureConverter()
{
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ワイド文字列
	std::wstring wString;

	wString.resize(filePathBufferSize);

	// ワイド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);



	return wString;
}
