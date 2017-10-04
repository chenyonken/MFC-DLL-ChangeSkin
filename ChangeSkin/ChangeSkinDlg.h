// ChangeSkinDlg.h : header file
//

#if !defined(AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_)
#define AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg dialog

#define WM_ICONALT WM_USER + 1		//���ƶ���ͼ��

typedef CSkinManage* (__stdcall* fCreateSkinObj)();
#define fLeftBand     1				//���ƴ��ڸ����ֱ�ʶ
#define fLeftTitle    2
#define fRightTitle   4
#define fMidTitle     8
#define fRightBand    16
#define fBottomBand   32
#define fLeftBottom   64
#define fRightBottom  128
#define fMinButton    256
#define fMaxButton    512
#define fCloseButton  1024
#define fAll          2047



//class CSkinManage;
#include "CustomMenu.h"
#include "SkinManage.h"
class CChangeSkinDlg : public CDialog
{
public:
	enum CButtonState{bsNone,bsIni,bsMin,bsMax,bsRes,bsClose};
public:
	enum{ICONNUM=2};
	HICON m_icon[ICONNUM];
public:
	CCustomMenu m_Menu;		//�Զ���˵�
	CSkinManage* pSkin;		//����Ƥ������
	HINSTANCE m_hInstance;	//��̬���ӿ�ʵ�����
	CBitmap m_Bk;			//����λͼ
	BOOL m_bLoadDll;		//�Ƿ����DLL
	int m_TitleDrawHeight;	//������ʵ�ʵĻ��Ƹ߶�
	BOOL m_IsMax;			//�Ƿ������״̬
	int m_BorderWidth;		//�߿���
	int m_BorderHeight;		//�߿�߶�
	int m_FrameWidth;		//����3D���
	int m_FrameHeight;		//����3D�߶�
	int m_CaptionHeight;	//�������ĸ߶�(��ʵ��)
	CString m_szCaption;	//���ڱ���
	COLORREF m_CaptionColor;//����������ɫ
	CFont m_CaptionFont;	//��������
	int m_ButtonWidth;		//��ťλͼ���
	int m_ButtonHeight;		//��ťλͼ�߶�
	BOOL m_FirstShow;		//�����״α���ʾ
	CRect m_OriginRect;		//ԭʼ��������
	//��������ť����ʾ����
	CRect m_IniRect,m_MinRect,m_MaxRect,m_CloseRect;
	//����⣬�м���⣬�ұ�����ʾ����
	CRect m_LTitleRc,m_MTitleRc,m_RTitleRc;
	CButtonState m_ButtonState;
	BOOL m_IsDrawForm;		//�Ƿ���Ҫ���ƴ���
	CRgn m_WndRgn,m_ClipRgn;	//��������ʾ��������
	int m_leftwidth;		//�����Ŀ��
	int m_rightwidth;		//�ұ���Ŀ��
	int m_leftlinewidth;		//���ڱ߿��3D��ȣ���߿�Ŀ��
	int m_rLineWidth;			//�ұ߿�Ŀ��
	int m_bLineHeight;			//�ױ߿�Ŀ��


// Construction
public:
	void SetDlgZone();
	void SkinApplication();
	void SkinDialog(UINT Flags=fAll);
	void DrawDialogText();
	CChangeSkinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeSkinDlg)
	enum { IDD = IDD_CHANGESKIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChangeSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnWindowsskin();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLoadfile();
	afx_msg void OnAboutbox();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_)
