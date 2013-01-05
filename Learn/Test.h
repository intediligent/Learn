#pragma once
#include "wordlist.h"


// CTest �Ի���

class CTest : public CDialog
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTest();

// �Ի�������
	enum { IDD = IDD_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedRight();
public:
	afx_msg void OnBnClickedWrong();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	WordList * m_wl;
public:
	int setWordList(WordList * wordList);
	danciEx* m_currWord;
public:
	danciEx* generateWord(void);
	bool** m_wordMap;
	int* m_levelSize;
public:
	int getLevel(void);
public:
	int m_level;
};
