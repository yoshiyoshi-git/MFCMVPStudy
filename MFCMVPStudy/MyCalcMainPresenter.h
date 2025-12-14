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

		if (_serializeService.SaveData(savedata))
			_mainView->ShowMessage(L"•Û‘¶‚µ‚½‚Ÿ‚Ÿ‚ ‚ ‚ ");
		else
			_mainView->ShowMessage(L"Ž¸”s‚µ‚½‚Ÿ‚Ÿ‚Ÿ‚ ‚ ‚ ");
	}
};