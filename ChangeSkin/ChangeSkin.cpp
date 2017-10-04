// ChangeSkin.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ChangeSkin.h"
#include "ChangeSkinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinApp

BEGIN_MESSAGE_MAP(CChangeSkinApp, CWinApp)
	//{{AFX_MSG_MAP(CChangeSkinApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinApp construction

CChangeSkinApp::CChangeSkinApp()
{
	m_bLoadDll=FALSE;
	pSkin=NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CChangeSkinApp object

CChangeSkinApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinApp initialization

BOOL CChangeSkinApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	int ret=AlterSkin(_T("../SkinOne/Debug/SkinDll.ski"));
	if(!ret)
		return FALSE;
	CChangeSkinDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}





/***************************************************
* BOOL CChangeSkinApp::AlterSkin(LPCTSTR lpFileName)
* ���ܣ���Ӧ�ó����ʼ��ʱ����Ĭ�ϵ�Ƥ���ļ����н��滻��
* ������lpFileName,��̬����ļ�λ��
* ����ֵ:�Ƿ���سɹ�
****************************************************/


BOOL CChangeSkinApp::AlterSkin(LPCTSTR lpFileName)
{
	HINSTANCE hTemp;
	hTemp=LoadLibrary(lpFileName);
	fCreateSkinObj CreateSkinObj=NULL;
	try
	{
		//��ȡ��̬���е�CreateSkinObj������ַ
		CreateSkinObj=(fCreateSkinObj)GetProcAddress(hTemp,_T("CreateSkinObj"));

	}
	catch(...)
	{
		m_bLoadDll=FALSE;
		return FALSE;
	}
	if(CreateSkinObj==NULL)
		return FALSE;
	else
	{
		if(m_bLoadDll)
		{
			pSkin->Release();
			FreeLibrary(m_hInstance);
		}
		m_bLoadDll=TRUE;
		m_hInstance=hTemp;
		pSkin=CreateSkinObj();
		return TRUE;
	}
}


/***********************************************
* int CChangeSkinApp::ExitInstance() 
* �麯������Ӧ�ó����˳�ʱ���ͷ�Ƥ���ļ�����
***********************************************/
//typedef void (__stdcall* fReleaseSkin)(CSkin* pSkin);
int CChangeSkinApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bLoadDll)
	{

		pSkin->Release();//ע�⣬Release()Ŀǰ�Ǵ��麯������û������
		FreeLibrary(m_hInstance);//����ʱ�����ŵ����������������ȣ���������ǵû����޸�
	}
	return CWinApp::ExitInstance();
}

