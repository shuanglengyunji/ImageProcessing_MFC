
// image1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Cimage1Dlg 对话框
class Cimage1Dlg : public CDialogEx
{
// 构造
public:
	Cimage1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	void Display(int HWND,BITMAPINFO* pDisBmpInfo,BYTE* pDisBmpData);

// 对话框数据
	enum { IDD = IDD_IMAGE1_DIALOG };

protected:
	CWinThread* pThread1;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedFix1();
	
	CProgressCtrl m_process1;
};

UINT ThreadFunc1(LPVOID lpParam);

