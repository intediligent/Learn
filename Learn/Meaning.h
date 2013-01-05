#pragma once
#include "afxwin.h"
#include "wordlist.h"


// CMeaning 对话框

class CMeaning : public CDialog
{
	DECLARE_DYNAMIC(CMeaning)

public:
	CMeaning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeaning();

// 对话框数据
	enum { IDD = IDD_MEANING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int setDanci(CString danci);

public:
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:
	WordList m_wordList;
	CString m_danci;
	CEdit meaning_edit;
	danciEx* m_word;
public:
	int getSize(void);
public:
	int saveFile(void);
public:
	danciEx* search(wchar_t* mean, int lenth);
public:
	afx_msg void OnBnClickedOk4();
public:
	WordList* getWordList(void);
};
