#pragma once
#include <string>
#include <Windows.h>
#include  "externals/DirectXTex/DirectXTex.h"
class TextureConverter
{
public:

	TextureConverter();
	~TextureConverter();

	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// 
	void ConvertTextureWICToDDS(const std::string& filePath);

private:

	


	void LoadWICTextureFromFile(const std::string& filePath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private:

	// 画像の情報
	DirectX::TexMetadata metadata_;

	//　画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;

private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filePath"></param>
	void SeparateFilePath(const std::wstring& filePath);
	/// <summary>
	/// 
	/// </summary>
	void SaveDDSTextureToFile();

	// 
	std::wstring directoryPath_;
	// 
	std::wstring fileName_;
	// 
	std::wstring fileExt_;

};

