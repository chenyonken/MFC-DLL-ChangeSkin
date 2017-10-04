// ChangeSkinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangeSkin.h"
#include "ChangeSkinDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg dialog



CChangeSkinDlg::CChangeSkinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeSkinDlg::IDD, pParent)
{
	m_FirstShow=FALSE;
	m_IsMax=TRUE;
	m_CaptionColor=RGB(255,255,0);	//���ñ�������ɫ
	m_szCaption=_T("��");	//���ñ������ı�����ɫ
	m_bLoadDll=FALSE;				//���ü��ر��Ϊδ����Ƥ���ļ�

	//{{AFX_DATA_INIT(CChangeSkinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChangeSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeSkinDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChangeSkinDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeSkinDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_COMMAND(ID_WINDOWSSKIN, OnWindowsskin)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_LOADFILE, OnLoadfile)
	ON_COMMAND(ID_ABOUTBOX, OnAboutbox)
	ON_WM_NCCALCSIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg message handlers

BOOL CChangeSkinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	//���ز˵�����ȡ����˵���Ϣ��m_Menu������
	HMENU hMenu = GetMenu()->GetSafeHmenu();
	if (hMenu != NULL)
	{
		m_Menu.AttatchMenu(hMenu);//���˵�������˵���Դ���
		m_Menu.SetMenuItemInfo(&m_Menu);//
	}

	m_BorderHeight = GetSystemMetrics(SM_CYBORDER);		//��ȡϵͳ�߽�߶�
	m_BorderWidth = GetSystemMetrics(SM_CXBORDER);		//��ȡϵͳ�߽���
	m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);	//��ȡϵͳ�������߶�
	SkinApplication();									
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChangeSkinDlg::OnPaint() 
{
	if (IsIconic())		//������С���Ļ���
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}


	SkinDialog();			//ÿ��ˢ�¶����»��ƶԻ��������
	m_IsDrawForm=TRUE;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChangeSkinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChangeSkinDlg::DrawDialogText()
{
	if(!m_szCaption.IsEmpty())
	{
		CDC* pDC=GetWindowDC();		//��ȡ�����豸������
		pDC->SetBkMode(TRANSPARENT);//����͸���ı���ģʽ
		pDC->SetTextColor(m_CaptionColor);	//���ñ������ı���ɫ
		pDC->SetTextAlign(TA_CENTER);
		CRect rect;
		GetClientRect(rect);
		pDC->SelectObject(&m_CaptionFont);
		//�ڱ�����������ı�
		pDC->TextOut(rect.Width()/2,m_CaptionHeight/3,m_szCaption);
		ReleaseDC(pDC);
	}
}


/******************************************************************
* HBRUSH CChangeSkinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
* ����:��Ϣ��Ӧ�������޸Ĵ��ڱ�����ɫ
* �����������MSDN
******************************************************************/
HBRUSH CChangeSkinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

	// TODO: Change any attributes of the DC here
	//���Ʊ���,����Ǵ�����Ƥ���ļ��Ѽ���
	if(nCtlColor==CTLCOLOR_DLG && m_bLoadDll==TRUE)
	{
		if(m_bLoadDll)
		{
			CBrush m_Brush(&m_Bk);//CBrush������λͼ������
			CRect rect;
			GetClientRect(rect);
			pDC->SelectObject(&m_Brush);
			pDC->FillRect(rect,&m_Brush);
			return m_Brush;
		}
		else
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	else if(nCtlColor==CTLCOLOR_STATIC)//���Ϊ��̬�ı�
	{
		pDC->SetBkMode(TRANSPARENT);
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	else
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Return a different brush if the default is not desired
}




/**************************************************
* void CChangeSkinDlg::SkinDialog(UINT Flags)
* ���ܣ����ݲ������ʹ��λͼ��Դ�����ƴ��ڵĸ������֣�������Ӧ�ó���ĺ��ģ�
		ʵ�ֻ��ƶԻ������������������ť���Ի���߿򣬶Ի��򱳾��Ĺ���
* ������Flags����Ҫ���ƵĲ��ֵı���
****************************************************/
void CChangeSkinDlg::SkinDialog(UINT Flags)
{
	if(m_bLoadDll)
	{
		m_FrameHeight=GetSystemMetrics(SM_CYFIXEDFRAME);		//��ȡ�Ի����ܸ߶�
		m_BorderHeight=GetSystemMetrics(SM_CYBORDER);			//��ȡ�Ի���߿�ĸ߶�
		m_FrameWidth=GetSystemMetrics(SM_CXFIXEDFRAME);			//��ȡ�Ի����ܵĿ��
		m_BorderWidth=GetSystemMetrics(SM_CXBORDER);			//��ȡ�Ի���߿�Ŀ��
		m_CaptionHeight=GetSystemMetrics(SM_CYCAPTION);			//��ȡ�������߶�
		CRect ClientRect;
		GetClientRect(ClientRect);
		CRect WinRC,FactRC;
		//��ȡ�����������򣬰����ǿͻ�����
		GetWindowRect(WinRC);
		FactRC.CopyRect(CRect(0,0,WinRC.Width(),WinRC.Height()));
		CWindowDC WindowDC(this);
		CBitmap LeftLine,*OldObj;	//����λͼ����
		BITMAPINFO bitInfo;			//����λͼ��Ϣ����
		CDC memDC;					//�����ڴ��豸������
		memDC.CreateCompatibleDC(&WindowDC);
		LeftLine.Attach(pSkin->GetBitmapRes(2));	//�����ұ���λͼ
		LeftLine.GetObject(sizeof(bitInfo),&bitInfo);//��ȡ�ұ���λͼ��Ϣ
		m_rightwidth=bitInfo.bmiHeader.biWidth;		//��ȡ�ұ���λͼ���
		LeftLine.Detach();
		int x,y;

		//���ƶԻ������߿�
		if(Flags&fLeftBand)		//������߿�
		{
			DeleteObject(LeftLine);		//ɾ����ǰ���ص�λͼ
			LeftLine.Attach(pSkin->GetBitmapRes(3));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			OldObj=memDC.SelectObject(&LeftLine);
			//�ж�λͼ�Ŀ���봰���Ե�Ŀ��
			m_leftlinewidth=(x>m_FrameWidth+m_BorderWidth)?x:m_FrameWidth+m_BorderWidth;
			m_Menu.m_nMenuLeft=m_leftlinewidth-m_BorderWidth-m_FrameWidth;

			//�ڴ����л��Ʊ߿�λͼ
			WindowDC.StretchBlt(0,m_CaptionHeight,m_leftlinewidth,
				FactRC.Height()-m_CaptionHeight,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();		//����λͼ	
		}

		//���ƶԻ����������������ȴ�Ƥ���ļ��л�ȡ�������λͼ��Ȼ�����
		if(Flags&fLeftTitle)
		{
			DeleteObject(LeftLine);		//ɾ����ǰ���ص�λͼ
			LeftLine.Attach(pSkin->GetBitmapRes(0));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			m_leftwidth=x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//����������ĸ߶�
			m_TitleDrawHeight=(m_CaptionHeight+4)>y?m_CaptionHeight+4:y;

			m_Menu.m_nMenuTop=m_TitleDrawHeight;	//���ò˵��Ķ���λ��

			//�������������ʾ����
			m_LTitleRc.CopyRect(CRect(0,0,x,m_TitleDrawHeight));
			//�����������λͼ
			WindowDC.StretchBlt(m_LTitleRc.left,m_LTitleRc.top,
				m_LTitleRc.Width(),m_LTitleRc.Height(),
				&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//���ƶԻ�����ұ�����
		if ( Flags & fRightTitle)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(2));
			//��ȡλͼ��С
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj = memDC.SelectObject(&LeftLine);
			x = bitInfo.bmiHeader.biWidth;
			y = bitInfo.bmiHeader.biHeight;
			m_TitleDrawHeight = (m_CaptionHeight+4>y)?m_CaptionHeight+4: y;
			
			m_RTitleRc.CopyRect(CRect(FactRC.right-x,0,FactRC.right,m_TitleDrawHeight));

			WindowDC.StretchBlt(m_RTitleRc.left,m_RTitleRc.top,m_RTitleRc.Width(),m_RTitleRc.Height(),&memDC,0,0,x,y,SRCCOPY);
			DeleteObject( memDC.SelectObject(OldObj));
			LeftLine.Detach();
		}



		//���ƶԻ�����м������
		if(Flags&fMidTitle)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(1));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//����������Ļ��Ƹ߶�
			m_TitleDrawHeight=(m_CaptionHeight+4>y)?m_CaptionHeight+4:y;

			//�����м����������ʾ����
			m_MTitleRc.CopyRect(CRect(m_LTitleRc.right,0,m_RTitleRc.left,m_TitleDrawHeight));
			//�����м������λͼ
			WindowDC.StretchBlt(m_MTitleRc.left,m_MTitleRc.top,
				m_MTitleRc.Width(),m_MTitleRc.Height(),&memDC,
				0,0,x,y,SRCCOPY);
			LeftLine.Detach();
			memDC.SelectObject(OldObj);
		}

		//���ƶԻ�����ұ߿�
		if(Flags&fRightBand)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(5));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//�����ұ߿�Ŀ��
			m_rLineWidth=m_FrameWidth+m_BorderWidth;
			m_rLineWidth=m_rLineWidth>x?m_rLineWidth:x;
			//�����ұ߿�λͼ
			WindowDC.StretchBlt(m_RTitleRc.right-m_rLineWidth,m_TitleDrawHeight,
				m_rLineWidth,FactRC.Height()-m_TitleDrawHeight,
				&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//���ƶԻ���ĵױ߿�
		if(Flags&fBottomBand)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(4));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//����ױ߿�Ŀ��
			m_bLineHeight=m_BorderHeight+m_FrameHeight;
			m_bLineHeight=m_bLineHeight>y?m_bLineHeight:y;
			//���Ƶױ߿�λͼ
			WindowDC.StretchBlt(m_leftlinewidth,FactRC.Height()-m_bLineHeight,
				m_RTitleRc.right-m_rLineWidth-m_leftlinewidth,
				m_bLineHeight,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}
		
		//�������½Ǻ����½�
		if(pSkin->GetDrawRound())
		{
			if(Flags& fLeftBottom)
			{
				DeleteObject(LeftLine);
				LeftLine.Attach(pSkin->GetBitmapRes(12));
				LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
				OldObj=memDC.SelectObject(&LeftLine);
				x=bitInfo.bmiHeader.biWidth;
				y=bitInfo.bmiHeader.biHeight;
				//�������½�λͼ
				WindowDC.StretchBlt(0,FactRC.Height()-m_bLineHeight,
					m_leftlinewidth,m_bLineHeight,
					&memDC,0,0,x,y,SRCCOPY);
				memDC.SelectObject(OldObj);
				LeftLine.Detach();
			}
			if(Flags& fRightBottom)
			{
				DeleteObject(LeftLine);
				LeftLine.Attach(pSkin->GetBitmapRes(13));
				LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
				OldObj=memDC.SelectObject(&LeftLine);
				x=bitInfo.bmiHeader.biWidth;
				y=bitInfo.bmiHeader.biHeight;
				//�������½�λͼ
				WindowDC.StretchBlt(m_RTitleRc.right-x,FactRC.Height()-m_bLineHeight,
					x,m_bLineHeight,
					&memDC,0,0,x,y,SRCCOPY);
				memDC.SelectObject(OldObj);
				LeftLine.Detach();
			}
		}

		//���ݱ�������ťλͼ�Ĵ�С�����������ť����ʾ����
		CPoint pos=pSkin->GetButtonPos(6);
		//������С����ťλͼ����ʾ����
		m_MinRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		pos=pSkin->GetButtonPos(7);
		//������󻯰�ťλͼ��ʾ����
		m_MaxRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		pos=pSkin->GetButtonPos(8);
		//����رհ�ťλͼ��ʾ����
		m_CloseRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		//���ݱ�������ť����ʾ������Ʊ�������ť
		//������С����ť
		if(Flags&fMinButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(6));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//������С��ť
			WindowDC.StretchBlt(m_MinRect.left,m_MinRect.top,m_MinRect.right,	//ע��������right����Width��Height����Ϊ�õ���m_MinRect�������ҵߵ���
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//������󻯰�ť
		if(Flags&fMaxButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(7));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//������󻯰�ť
			WindowDC.StretchBlt(m_MaxRect.left,m_MaxRect.top,m_MinRect.right,
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//���ƹرհ�ť
		if(Flags&fCloseButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(8));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//������󻯰�ť
			WindowDC.StretchBlt(m_CloseRect.left,m_CloseRect.top,m_MinRect.right,
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		m_IsDrawForm=TRUE;
		LeftLine.DeleteObject();	//�Ƿ�λͼ����
		memDC.DeleteDC();			
		DrawDialogText();			//���Ʊ����ı�
	}
}





/*****************************************
* void CChangeSkinDlg::SkinApplication()
* ����: �ԽӶ�̬����غ�Ĳ������봰�������,��ȡ����λͼ��Ϣ
		���˵���Ϣ��������Ϣ
* ****************************************/
void CChangeSkinDlg::SkinApplication()
{
	m_bLoadDll=((CChangeSkinApp*)AfxGetApp())->m_bLoadDll;
	pSkin=((CChangeSkinApp*)AfxGetApp())->pSkin;

	m_Bk.DeleteObject();
	m_CaptionFont.DeleteObject();
	if(m_bLoadDll)
	{
		ModifyStyle(WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU,0);		//�޸Ĵ�����ʽ��ȥ����󻯣���С�����رհ�ť�Ͳ˵�
		m_Bk.Attach(pSkin->GetBitmapRes(14));							//���ر���λͼ���ұ�������û���ͷ�
		//��ȡ��ťλͼ��С
		CBitmap bitmap;
		bitmap.Attach(pSkin->GetBitmapRes(6));
		BITMAPINFO bInfo;
		bitmap.GetObject(sizeof(bInfo),&bInfo);
		m_ButtonWidth=bInfo.bmiHeader.biWidth;			//��ȡ��������ť�Ŀ��
		m_ButtonHeight=bInfo.bmiHeader.biHeight;		//��ȡ��������ť�ĸ߶�
		bitmap.Detach();
		m_WndRgn.DeleteObject();
		SetDlgZone();	
		
		m_Menu.m_BkColor=pSkin->GetMenuBKColor();		//�Ӷ�̬���л�ȡ�˵�������ɫ���͵��˵�����
		m_Menu.m_SelTopColor=pSkin->GetMenuSelColor();
		m_CaptionFont.CreateFont(12,10,0,0,600,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_ROMAN,"MS Sans Serif");

	}
	//���û�м��سɹ���̬�⣬��ʹ��ԭʼ����
	else
	{
		ModifyStyle(0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_CAPTION);
	}

}






/**********************************************
* void CChangeSkinDlg::SetDlgZone()
* ���ܣ�����Ի���4���ǵ�λͼ���а�ɫ��������۳�������
		���Ի���������Բ�Ǿ��Σ����û��ƶԻ��������ƴ���
**********************************************/
void CChangeSkinDlg::SetDlgZone()
{
	SkinDialog();		//���ƶԻ���
	CRect winrect,factRC;		//���洰�ھ��Σ����������θ���
	GetWindowRect(winrect);		//��ȡ��������
	factRC.CopyRect(CRect(0,0,winrect.Width(),winrect.Height()));
	m_WndRgn.DeleteObject();
	m_WndRgn.CreateRectRgnIndirect(factRC);	//����Բ������
	CBitmap bitmap;			//����λͼ����
	BITMAPINFO bInfo;		//����λͼ��Ϣ����

	//ȥ�����ϽǵĿհ����򣬷����Ǹ����������λͼ�İ�ɫ���ص���ȷ��ȥ��������
	bitmap.Attach(pSkin->GetBitmapRes(0));
	bitmap.GetObject(sizeof(bInfo),&bInfo);	//��ȡλͼ��Ϣ
	int x,y,m,n;
	x=bInfo.bmiHeader.biWidth;
	y=bInfo.bmiHeader.biHeight;
	CDC memDC;
	CDC* pDC=GetDC();
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&bitmap);
	for(m=0;m<x;m++)
	{
		for(n=0;n<y;n++)
		{
			if(memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m,n,m+1,n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();

			}
		}
	}
	bitmap.Detach();

	//ȥ�����ϽǵĿհ�����
	bitmap.Attach(pSkin->GetBitmapRes(2));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m_RTitleRc.left+m,m_RTitleRc.top+n,m_RTitleRc.left+ m+1,m_RTitleRc.top+n+1);

				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();


	//ȥ�����½ǵĿհ�����
	bitmap.Attach(pSkin->GetBitmapRes(12));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m,factRC.Height()-y+n ,m+1,factRC.Height()-y+n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();
	//ȥ�����½ǵĿհ�����
	bitmap.Attach(pSkin->GetBitmapRes(13));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m_RTitleRc.right-x+m,factRC.Height()-y+n,m_RTitleRc.right-x+m+1,factRC.Height()-y+n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();
	ReleaseDC(&memDC);
	ReleaseDC(pDC);
	SetWindowRgn(m_WndRgn,TRUE);
	DeleteObject(m_WndRgn);

}

void CChangeSkinDlg::OnSize(UINT nType, int cx, int cy) 
{
//	SetWindowRgn(NULL,TRUE);//������ʹ�����ڴ�С�仯ʱ����˸

	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bLoadDll)
		return;
	CRect rect;
	GetClientRect(rect);
	CPoint pos=pSkin->GetButtonPos(6);	//��ȡ��С����ť��ʾ���λ��
	//������С����ť��ʾλ��
	m_MinRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	pos=pSkin->GetButtonPos(7);	//��ȡ��С����ť��ʾ���λ��
	//������󻯰�ť��ʾλ��
	m_MaxRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	pos=pSkin->GetButtonPos(8);	//��ȡ��С����ť��ʾ���λ��
	//����رհ�ť��ʾλ��
	m_CloseRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	SetDlgZone();		//���ô�������
	Invalidate();

}

void CChangeSkinDlg::OnNcPaint() 
{
	// TODO: Add your message handler code here
	CWnd::OnNcPaint();
	OnPaint();
	// Do not call CDialog::OnNcPaint() for painting messages
}

BOOL CChangeSkinDlg::OnNcActivate(BOOL bActive) 
{
	// TODO: Add your message handler code here and/or call default
	OnPaint();
	return TRUE;
}

void CChangeSkinDlg::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLoadDll)
	{
		CRect tempIni,tempMin,tempMax,tempClose,ClientRect;
		CWindowDC WindowDC(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&WindowDC);
		BITMAPINFO bInfo;
		CBitmap LeftLine;
		int x,y;
		GetWindowRect(ClientRect);//��ȡ������������
		
		//��ȡ��С����ť����󻯰�ť�͹رհ�ť����ʾ����(��Ա߽�λ�ã�
		tempMin.CopyRect(CRect(m_MinRect.left+ ClientRect.left,
			ClientRect.top+m_MinRect.top,
			m_MinRect.right+m_MinRect.left+ ClientRect.left,
			m_MinRect.bottom+m_MinRect.top+ClientRect.top));

		tempMax.CopyRect(CRect(m_MaxRect.left+ ClientRect.left,
			ClientRect.top+m_MaxRect.top,
			m_MaxRect.right+m_MaxRect.left+ ClientRect.left,
			m_MaxRect.bottom+m_MaxRect.top+ClientRect.top));

		tempClose.CopyRect(CRect(m_CloseRect.left+ ClientRect.left,
			ClientRect.top+m_CloseRect.top,
			m_CloseRect.right+m_CloseRect.left+ ClientRect.left,
			m_CloseRect.bottom+m_CloseRect.top+ClientRect.top));

		if(tempMin.PtInRect(point))
		{
			if(m_ButtonState!=bsMin)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(9));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//������С����ť���ȵ�λͼ
				WindowDC.StretchBlt(m_MinRect.left,m_MinRect.top,
					m_MinRect.right,m_MinRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				m_ButtonState=bsMin;
				LeftLine.Detach();
			}
		}
		else if(tempMax.PtInRect(point))
		{
			//�����ť״̬������󻯻�ԭ״̬
			if(m_ButtonState!=bsMax&&m_ButtonState!=bsRes)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(10));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//������󻯰�ť���ȵ�λͼ
				WindowDC.StretchBlt(m_MaxRect.left,m_MaxRect.top,
					m_MaxRect.right,m_MaxRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				if(m_IsMax)		//��ǰ�Ƿ����״̬
				{
					m_ButtonState=bsMax;	//�������״̬
				}
				else
				{
					m_ButtonState=bsRes;	//���û�ԭ��ť״̬
				}
				LeftLine.Detach();					
			}
		}
		else if(tempClose.PtInRect(point))
		{
			if(m_ButtonState!=bsClose)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(11));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//������С����ť���ȵ�λͼ
				WindowDC.StretchBlt(m_CloseRect.left,m_CloseRect.top,
					m_CloseRect.right,m_CloseRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				m_ButtonState=bsClose;
				LeftLine.Detach();					
			}
		}
		else
		{
			if(m_IsDrawForm==FALSE)
			{
				if(m_ButtonState==bsMin)	//��ǰ��ť״��Ϊ��С����ť
					SkinDialog(fMinButton);
				else if(m_ButtonState==bsClose)
					SkinDialog(fCloseButton);
				else if(m_ButtonState==bsMax||m_ButtonState==bsRes)
					SkinDialog(fMaxButton);
			}
			m_ButtonState=bsNone;
		}
		LeftLine.DeleteObject();
		ReleaseDC(&memDC);
	}
	CDialog::OnNcMouseMove(nHitTest, point);
}

void CChangeSkinDlg::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLoadDll)
	{
		switch(m_ButtonState)	//�жϵ�ǰ��ť״̬
		{
		case bsClose:
			{
				OnCancel();
				break;
			}
		case bsMin:
			{
				ShowWindow(SW_SHOWMINIMIZED);
				break;
			}
		case bsMax:
			{
				m_ButtonState=bsMax;
				ShowWindow(SW_SHOWMAXIMIZED);
				m_IsMax=FALSE;
				break;
			}
		case bsRes:
			{
				ShowWindow(SW_RESTORE);
				m_IsMax=TRUE;
				break;
			}
		}
	}
	CDialog::OnNcLButtonDown(nHitTest, point);
}


/*********************************************
* void CChangeSkinDlg::OnWindowsskin() 
* ���ܣ����ʹ��Window����˵���ʱ����Ϣ��Ӧ��Ӧ����
**********************************************/
void CChangeSkinDlg::OnWindowsskin() 
{
	// TODO: Add your command handler code here
	if(m_bLoadDll)
	{
		((CChangeSkinApp*)AfxGetApp())->pSkin->Release();	//�ͷ�CSkin����
		FreeLibrary(((CChangeSkinApp*)AfxGetApp())->m_hInstance);//�ͷŶ�̬���ӿ�
		((CChangeSkinApp*)AfxGetApp())->m_bLoadDll=FALSE;
		m_bLoadDll=FALSE;
		SkinApplication();
		m_Menu.m_nMenuTop=m_CaptionHeight;	//�޸�
		m_Menu.m_BkColor=m_Menu.m_OrginBkColor;//����Ĭ�ϵĲ˵�������ɫ
		m_Menu.m_SelTopColor=m_Menu.m_OrginSelColor;//����Ĭ�ϵĲ˵�ѡ��ʱ����ɫ
		m_Menu.m_nMenuLeft=0;
		SetWindowPos(NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_DRAWFRAME);
		Invalidate();
		OnSize(0,0,0);
	}
}

/********************************************************
* void CChangeSkinDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
* ���ܣ����Ʋ˵�
********************************************************/
void CChangeSkinDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_Menu.DrawItem(lpDrawItemStruct);
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CChangeSkinDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_Menu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CChangeSkinDlg::OnLoadfile() 
{
	// TODO: Add your command handler code here
	CFileDialog fd(TRUE,_T("*.ski"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Ƥ��(.ski)|*.ski||"),this);
	if(fd.DoModal()==IDCANCEL)
		return;
	m_Bk.DeleteObject();
	m_CaptionFont.DeleteObject();
	((CChangeSkinApp*)AfxGetApp())->AlterSkin(fd.GetPathName());
	SkinApplication();
	fd.DestroyWindow();
	Invalidate();
	OnSize(0,0,0);


}

void CChangeSkinDlg::OnAboutbox() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}



void CChangeSkinDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CChangeSkinDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}	
//	CDialog::OnSysCommand(nID, lParam);
}

void CChangeSkinDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CChangeSkinDlg::OnOK() 
{
//	CDialog::OnOK();
}

void CChangeSkinDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_bLoadDll)
	{
		m_Bk.Detach();
		m_CaptionFont.DeleteObject();
		m_Bk.DeleteObject();
	}	
	CDialog::OnCancel();
}
