#pragma once
#include <string>
#include <Windows.h>
class TextureConverter
{
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// 
	void ConvertTextureWICToDDS(const std::string& filePath);

private:

	TextureConverter();
	~TextureConverter();


	void LoadWICTextureFromFile(const std::string& filePath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);


};

