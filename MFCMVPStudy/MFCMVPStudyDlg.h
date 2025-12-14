
// MFCMVPStudyDlg.h : ヘッダー ファイル
//

#pragma once

#include "MyCalcMainView.h"
#include "MyCalcMainPresenter.h"
#include <memory>

// CMFCMVPStudyDlg ダイアログ
class CMFCMVPStudyDlg : public CDialogEx, public MyCalcMainView
{
// コンストラクション
public:
	CMFCMVPStudyDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMVPSTUDY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


private:
	std::unique_ptr<MainCalcPresenter> _calcPresenter;

/***MyCalcMainViewの実装***/
public:
	virtual void  UpdateCalcResult(const std::wstring& text) override;
	virtual void ShowMessage(const std::wstring& message) override;
	virtual void SetInputNumbers() override;
/***MyCalcMainViewの実装***/

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox ComboInputNumber;
	CEdit EditResultNumber;
	afx_msg void OnCbnSelchangeComboInputNumber();
};
