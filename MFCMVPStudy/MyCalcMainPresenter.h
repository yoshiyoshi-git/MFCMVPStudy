#pragma once

#include "MyCalcMainView.h"
#include "MyCalcNumberService.h"
#include "MyCalcSerializeService.h"
#include "MyCalcData.h"
#include<string>

// Presenter-Calc
class MainCalcPresenter
{
	MyCalcMainView* _mainView;
	MyCalcNumberService _numberService;
	MyCalcSerializeService _serializeService;

	int currentSelectionNumber = 0;

public:
	explicit MainCalcPresenter(MyCalcMainView* mainView)
		: _mainView(mainView){}

	void OnNumberSelected(int number)
	{
		currentSelectionNumber = number;

		int result = _numberService.CalcDouble(number);

		if(_mainView)
			_mainView->UpdateCalcResult(std::to_wstring(result));

	}

	void OnSaveClicked()
	{
		if (!_mainView)	return;

		MyCalcStruct savedata;
		savedata._inputNumber = currentSelectionNumber;
		savedata._resultNumber = _numberService.CalcDouble(currentSelectionNumber);

		auto callback = [this](bool sucess)
		{
			if (_mainView)
			{
				_mainView->OnSaveComplete(sucess);
			}
		};	

		bool isstarted = _serializeService.SaveData(savedata, callback);
		if (!isstarted)
		{
			_mainView->ShowMessage(L"保存スレッドの開始に失敗しました。");
		}
	}

	void OnSaveFinished(bool success)
	{
		if (!_mainView)	return;

		if (success)
			_mainView->ShowMessage(L"保存完了！");
		else
			_mainView->ShowMessage(L"保存失敗！");
	}
};