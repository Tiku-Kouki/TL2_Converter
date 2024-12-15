#include "TextureConverter.h"
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);
	//DDS形式にして書き出す
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
	// ファイルパスを	ワイド文字列に変換
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	HRESULT result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);

	assert(SUCCEEDED(result));

	//フォルダパスとファイル名分解
	SeparateFilePath(wfilePath);


}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ワイド文字列に変換した際の文字列を計算
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
	HRESULT result;

	//ミニマップの作成
	ScratchImage mipChain;
	result = GenerateMipMaps(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(),
		scratchImage_.GetMetadata(),
		TEX_FILTER_SRGB, 0, mipChain);

	if (SUCCEEDED(result)) {

		//イメージとメタデータを、ミップマップ版に書き換える
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();

	}


	//ミニマップの作成
	ScratchImage converted;
	result = Compress(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(),metadata_,
		DXGI_FORMAT_BC7_UNORM_SRGB,TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT|
		TEX_COMPRESS_PARALLEL,1.0f,converted);

	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();

	}



	// 読み込んだテクスチャをSRGBとして使う
	metadata_.format = MakeSRGB(metadata_.format);

	

	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DDS_FLAGS_NONE, filePath.c_str());

	
	assert(SUCCEEDED(result));



}
