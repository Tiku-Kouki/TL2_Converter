#pragma once
#include <string>
#include <Windows.h>
#include  "externals/DirectXTex/DirectXTex.h"
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

	// 画像の情報
	DirectX::TexMetadata metadata_;

	//　画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;

};

