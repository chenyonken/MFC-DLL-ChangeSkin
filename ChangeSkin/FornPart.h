// FornPart.h: interface for the CFornPart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_)
#define AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFornPart  
{
public:
	HBITMAP m_hBitmap;	//λͼ��Դ
	CRect m_Rect;		//λͼ��Դλ�ã���λ��������ұ��ⲿ�ֵ����λ�ã�ֻ�Ա�������ť������
	
public:
	CFornPart();
	virtual ~CFornPart();

};

#endif // !defined(AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_)
