#pragma once

#include <afx.h>
#include "MyCalcData.h"
#include <string>

// シリアライズ担当-Calc
class MyCalcSerializeService
{
	const std::wstring _defaultSaveFilePath = L"CalcData.dat";
public:
	const std::wstring& GetDefaultSaveFilePath() const { return _defaultSaveFilePath; }

	bool SaveData(const MyCalcStruct& data)
	{
		try
		{
			CFile file;
			if (!file.Open(_defaultSaveFilePath.c_str(), CFile::modeCreate | CFile::modeWrite))
			{
				return false;
			}
			CArchive archive(&file, CArchive::store);
			archive << data._inputNumber;
			archive << data._resultNumber;
			archive.Close();
			file.Close();
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool LoadData(MyCalcStruct& data)
	{
		try
		{
			CFile file;
			if (!file.Open(_defaultSaveFilePath.c_str(), CFile::modeRead))
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