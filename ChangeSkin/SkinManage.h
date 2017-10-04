// SkinManage.h: interface for the CSkinManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_)
#define AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CFormPart;


//�������ı����ͺ���һ��Ҫ���ն�̬�������˳���д
class CSkinManage  
{
protected:
	UINT m_PartCount;    //�����ɼ��������
	/******************���������λͼ��Դ********************
	0,1,2			�ֱ�Ϊ����������\��\��3����
	3,4,5			�ֱ�Ϊ��,��,�ұ߿�
	6,7,8,9,10,11	Ϊ��������ͨ��ť���ȵ㰴ť
	*********************************************************/
	CFormPart* m_pParts;


public:
	//����λͼ��Դ 
	virtual HBITMAP GetBitmapRes(UINT Index) = 0;
	virtual Release() = 0;
	virtual CPoint GetButtonPos(UINT Index) = 0;
	virtual BOOL GetDrawRound() = 0;
	virtual COLORREF GetMenuBKColor() = 0;
	virtual COLORREF GetMenuSelColor() = 0;

public:
	CSkinManage();
	virtual ~CSkinManage();
};

#endif // !defined(AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_)
