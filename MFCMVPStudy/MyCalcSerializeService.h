#pragma once

#include <afx.h>
#include "MyCalcData.h"
#include <string>
#include <memory>
#include <functional>

struct MySaveThreadParam
{
	// 完了コールバック (成功:true 失敗:false)
	std::function<void(bool)> OnComplete;
	MyCalcStruct data;
};

// シリアライズ担当-Calc
class MyCalcSerializeService
{
public:
	static std::wstring GetDefaultSaveFilePath() { return L"CalcData.dat"; }

	static UINT SaveDataThread(LPVOID pParam)
	{
		std::unique_ptr<MySaveThreadParam> saveParam(static_cast<MySaveThreadParam*>(pParam));

		bool success = false;
		try
		{
			CFile file;
			if (!file.Open(MyCalcSerializeService::GetDefaultSaveFilePath().c_str(), CFile::modeCreate | CFile::modeWrite))
			{
				return false;
			}
			CArchive archive(&file, CArchive::store);
			archive << saveParam->data._inputNumber;
			archive << saveParam->data._resultNumber;
			archive.Close();
			file.Close();
			success = true;
		}
		catch (...)
		{
			success = false;
		}

		if (saveParam->OnComplete)
		{
			saveParam->OnComplete(success);
		}

		return 0;
	}

	bool SaveData(const MyCalcStruct& data, std::function<void(bool)> onComplete)
	{
		auto sendparam = std::make_unique<MySaveThreadParam>();
		sendparam->OnComplete = onComplete;
		sendparam->data = data;

		MySaveThreadParam* rawParam = sendparam.release();

		auto threadResult = AfxBeginThread(SaveDataThread, static_cast<LPVOID>(rawParam));
		if (threadResult == nullptr)
		{
			std::unique_ptr<MySaveThreadParam> resecureData(rawParam);
			return false;
		}
		return true;
	}

	bool LoadData(MyCalcStruct& data)
	{
		try
		{
			CFile file;
			if (!file.Open(MyCalcSerializeService::GetDefaultSaveFilePath().c_str(), CFile::modeRead))
				return false;

			CArchive archive(&file, CArchive::load);
			archive >> data._inputNumber;
			archive >> data._resultNumber;
			archive.Close();
			file.Close();
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

};
