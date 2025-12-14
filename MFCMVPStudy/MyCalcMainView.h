#pragma once
#include<string>

class MyCalcMainView
{
	
public:
	virtual ~MyCalcMainView() = default;
	virtual void  UpdateCalcResult(const std::wstring& text) = 0;
	virtual void ShowMessage(const std::wstring& message) = 0;
	virtual void SetInputNumbers() = 0;
};