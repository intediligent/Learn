// Meaning.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Learn.h"
#include "Meaning.h"


// CMeaning �Ի���

IMPLEMENT_DYNAMIC(CMeaning, CDialog)

CMeaning::CMeaning(CWnd* pParent /*=NULL*/)
	: CDialog(CMeaning::IDD, pParent)
	, m_danci(_T(""))
	, m_word(NULL)
{

}

CMeaning::~CMeaning()
{
}

void CMeaning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, meaning_edit);
}


BEGIN_MESSAGE_MAP(CMeaning, CDialog)
	ON_BN_CLICKED(IDOK3, &CMeaning::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK, &CMeaning::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK4, &CMeaning::OnBnClickedOk4)
END_MESSAGE_MAP()


// CMeaning ��Ϣ�������

void CMeaning::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString meaning;
	meaning_edit.GetWindowText(meaning);
	if ( meaning.GetLength()==0 )
	{
		MessageBox(_T("�����뺬��"));
	}
	else if( m_wordList.add(m_danci,meaning)==0 )
	{
		MessageBox(_T("������ӳɹ�"));
		GetParent()->Invalidate(TRUE);
		OnOK();
	}
}

int CMeaning::setDanci(CString danci)
{
	m_danci = danci;
	return 0;
}

void CMeaning::OnBnClickedOk3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ɾ��
	if( m_word )
	{
		if ( m_wordList.remove(m_danci.GetBuffer()) )
		{
			MessageBox(_T("����ɾ���ɹ�"));
			GetParent()->Invalidate(TRUE);
			OnOK();
		}
	}
	else
		MessageBox(_T("û���������"));
}

void CMeaning::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	m_word = m_wordList.find(m_danci.GetBuffer());
	CString str;
	int lenght=0;

	if( m_word )
	{
		str.Format(_T("����ѷ��%s �Ѿ�����ѯ�� %d ����"), m_danci, m_word->times);
		SetDlgItemText(IDC_STATIC,str);
		meaning_edit.SetWindowText(m_word->mean);
		lenght = (int)wcslen(m_word->mean);
	}
	else
	{
		str.Format(_T("��ϲ�㣬%s �Ǹ��µ��ʣ������뵥�ʺ��壺"), m_danci);
		SetDlgItemText(IDC_STATIC,str);
		meaning_edit.SetWindowText(_T(""));
	}
	//GetDlgItem(IDOK)->SetFocus();
	meaning_edit.SetSel(lenght,lenght);
	meaning_edit.SetFocus();
}

int CMeaning::getSize(void)
{
	return m_wordList.getSize();
}

int CMeaning::saveFile(void)
{
	return m_wordList.saveFile();
}

danciEx* CMeaning::search(wchar_t* mean, int lenth)
{
	return m_wordList.search(mean,lenth);
}

void CMeaning::OnBnClickedOk4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->Invalidate(TRUE);
	OnOK();
}

WordList* CMeaning::getWordList(void)
{
	return &m_wordList;
}
