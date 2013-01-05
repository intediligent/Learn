// LearnDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "meaning.h"
#include "test.h"


// CLearnDlg 对话框
class CLearnDlg : public CDialog
{
// 构造
public:
	CLearnDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LEARN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	CEdit word_edit;
	CMeaning meaning;
	CFont m_font;

public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedTest();
	CTest m_test;
};
