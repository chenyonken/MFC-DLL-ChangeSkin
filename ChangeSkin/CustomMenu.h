// CustomMenu.h: interface for the CCustomMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_)
#define AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CCustomMenu : public CMenu
{
public:
//����һ���ṹ����¼�˵������ϸ��Ϣ
	struct CMenuItem
	{
		CString m_MenuText;//�˵�����ı�
		UINT m_ImageIndex;	//�˵���ͼ������
		int m_MenuType;		//�˵������ͣ�-2����˵���-1����ʽ�˵���-0�ָ�����������ͨ�˵�
	};
public:
	int m_ItemCount;		//��¼�˵��������
	CMenuItem* m_MenuList;	//��¼ÿ���˵������Ϣ
	int m_Index;			//�����˵�ʱʹ�õ�����
	COLORREF m_BkColor;		//�˵�������ɫ
	COLORREF m_SelTopColor;	//����˵�ѡ��ʱ����ɫ
	COLORREF m_OrginBkColor;
	COLORREF m_OrginSelColor;
	BOOL m_RandColor;		//�˵����Ƿ����������ɫ
	int m_nMenuLeft;
	int m_nMenuTop;			//�˵���Ķ�����ʼλ��
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpStruct);
	BOOL AttatchMenu(HMENU hMenu);
	static void GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind=TRUE);
	BOOL SetMenuItemInfo(CMenu* pMenu,BOOL Toped=TRUE);
	void SetMenuItemText(CDC* pDC,LPSTR strMenuText,CRect Rect);
	void DrawTopMenuBk(CDC* pDC,CRect Rect,BOOL State);
	void DrawSepMenu(CDC* pDC,CRect Rect);
	void DrawMenuBk(CDC* pDC,CRect Rect,COLORREF SrcColor,COLORREF DesColor,BOOL State=FALSE);
	int GetTopMenuWidth();
	HRGN GetClientMenuRgn();
	CCustomMenu();
	virtual ~CCustomMenu();

};

#endif // !defined(AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_)
