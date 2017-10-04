// Skin.h: interface for the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_)
#define AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormPart.h"
class CSkin
{
protected:
	UINT m_PartCount;  //�����ɼ��������
	/******************���������λͼ��Դ����: *******************
 
	0,1,2:         �ֱ�Ϊ����������\��\��3����
	3,4,5:         �ֱ�Ϊ��,��,�ұ߿�
	6,7,8,9,10,11: Ϊ��������ͨ��ť���ȵ㰴ť
	12,13:         ��ʾ���½Ǻ����½�λͼ
	14:            ��ʾ����λͼ
	*************************************************************/
	CFormPart* m_pParts;
	COLORREF m_MenuBkColor;		//�˵�������ɫ
	COLORREF m_MenuSelColor;	//�˵�ѡ��ʱ����ɫ
	BOOL DrawRound;				//�Ƿ����Բ��

public:


	//��ȡλͼ��Դ
	virtual HBITMAP GetBitmapRes(UINT Index)
	{
		return m_pParts[Index].m_hBitmap;
	}
	//�ͷŶ���
	virtual Release()
	{	
		delete this;
	}
	//��ȡ��ť��λ��
	virtual CPoint GetButtonPos(UINT Index)
	{
		return  m_pParts[Index].m_Pos;
	}
	
	virtual BOOL GetDrawRound()
	{
		return DrawRound;
	}
	virtual COLORREF GetMenuBKColor()
	{
		return m_MenuBkColor;
	}
	virtual COLORREF GetMenuSelColor()
	{
		return m_MenuSelColor;
	}

	void LoadBitmapRes();		//����λͼ��Դ
	void SetButtonPos()	;		//���ñ�������ť�����λ��
public:
	CSkin();
	CSkin(UINT PartCount);
	~CSkin();

};


#endif // !defined(AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_)
