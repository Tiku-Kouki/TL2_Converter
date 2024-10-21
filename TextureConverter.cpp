#include "TextureConverter.h"
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	SaveDDSTextureToFile();

}

TextureConverter::TextureConverter()
{
}

TextureConverter::~TextureConverter()
{
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	HRESULT result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);

	assert(SUCCEEDED(result));

	//フォルダパスとファイル名分解
	SeparateFilePath(wfilePath);


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

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	// 区切り文字　'.' が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//
	if (pos1 != std::wstring::npos) {
		//
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);

		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}

	// 区切り文字　'\\' が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	//
	if (pos1 != std::wstring::npos) {
		//
		directoryPath_ = exceptExt.substr(0,pos1 + 1);

		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);

		return;
	}

	pos1 = exceptExt.rfind('/');
	//
	if (pos1 != std::wstring::npos) {
		//
		directoryPath_ = exceptExt.substr(0, pos1 + 1);

		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);

		return;
	}

	directoryPath_ = L"";

	fileName_ = exceptExt;




}

void TextureConverter::SaveDDSTextureToFile()
{
	// 読み込んだテクスチャをSRGBとして使う
	metadata_.format = MakeSRGB(metadata_.format);

	HRESULT result;

	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DDS_FLAGS_NONE, filePath.c_str());

	
	assert(SUCCEEDED(result));



}
