// LearnDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "meaning.h"
#include "test.h"


// CLearnDlg �Ի���
class CLearnDlg : public CDialog
{
// ����
public:
	CLearnDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LEARN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
