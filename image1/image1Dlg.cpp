
// image1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "image1.h"
#include "image1Dlg.h"
#include "afxdialogex.h"
#include "function.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cimage1Dlg 对话框

Cimage1Dlg::Cimage1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cimage1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(Cimage1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &Cimage1Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_FIX1, &Cimage1Dlg::OnBnClickedFix1)
END_MESSAGE_MAP()


// Cimage1Dlg 消息处理程序

BOOL Cimage1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	GetDlgItem(IDC_FIX1)->EnableWindow(FALSE);

	//调整图像控件大小
	CRect rect;

	GetDlgItem(IDC_IMAGE_1OUT)->GetWindowRect(&rect);           //IDC_WAVE_DRAW为Picture Control的ID  
	ScreenToClient(&rect);
	GetDlgItem(IDC_IMAGE_1OUT)->MoveWindow(rect.left, rect.top, 200, 120, true);

	GetDlgItem(IDC_IMAGE)->GetWindowRect(&rect);           //IDC_WAVE_DRAW为Picture Control的ID  
	ScreenToClient(&rect);
	GetDlgItem(IDC_IMAGE)->MoveWindow(rect.left, rect.top, 200, 120, true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cimage1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cimage1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cimage1Dlg::Display(int HWND,BITMAPINFO* pDisBmpInfo,BYTE* pDisBmpData)
{
	//获得pictrue控件窗口的句柄
	CWnd *pWnd;
	pWnd=GetDlgItem(HWND);
	//获取矩形
	CRect rect;
	pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域
	//获取DC(设备描述表，跟窗口有关)
	CDC *pDC;
	pDC = pWnd->GetDC();//获得pictrue控件的DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),0,0,rect.Width(),rect.Height(),0,0,  pDisBmpInfo->bmiHeader.biWidth,pDisBmpInfo->bmiHeader.biHeight,pDisBmpData,pDisBmpInfo,DIB_RGB_COLORS,SRCCOPY);
	
}

//全局图像指针

BITMAPINFO* pBmpInfo = NULL;     //记录图像细节
BYTE* pBmpData = NULL;           //图像数据
DWORD dataBytes;				 //图像字节数

//打开文件按钮
int button_flag = 0;	//0:显示为打开图片，1：显示为关闭图片
void Cimage1Dlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码

//	ID_OPEN

	if(button_flag == 0)
	{
		//打开图片按钮功能

		//记录选择文件路径
		CString strFileName;	

		//记录打开文件
		CFile bmpFile;			

		BITMAPFILEHEADER bmpHeader;	//文件头
		BITMAPINFOHEADER bmpInfo;	//信息头

		//打开文件
		//CFileDialog为VC中打开文件对话框类
		CFileDialog dlg(TRUE, "*.BMP", NULL, NULL,"位图文件(*.BMP)|*.bmp;*.BMP|",this);	
		if (!dlg.DoModal() == IDOK)
			return;	

		//获取文件路径
		strFileName = dlg.GetPathName();	

		//以只读的方式打开文件

		//打开文件到bmpFile
		if(!bmpFile.Open(strFileName, CFile::modeRead|CFile::typeBinary))	
			return;

		//读取文件头
		if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))	
		{
			AfxMessageBox("read bmp header failed!");
			return;
		}

		//检测文件类型是否为BMP
		//0x424D = "BM"
		if (bmpHeader.bfType != 0x4d42) 
		{
			AfxMessageBox("invalid file type!");
			return;
		}

		//读取信息头
		if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		{
			AfxMessageBox("read bmp infor header failed!");
			return;
		}

		//检测是否是24位真彩图
		if (bmpInfo.biBitCount != 24)
		{
			AfxMessageBox("File is not 24 bit.Application doesn't support this kind of file!");
			return;
		}

		//========================================================================

		//动态开辟内存空间，存放信息头bmpInfo
		pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];	
		if (!pBmpInfo)
		{
			AfxMessageBox("memory error!");
			return;
		}

		//把bmpInfo中的信息拷贝到pBmpInfo所指向的空间中
		memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));		

		//计算图像内容字节数
		dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;

		//动态开辟内存空间，存放图像内容
		pBmpData = (BYTE*)new char[dataBytes];
		if (!pBmpData)
		{
			AfxMessageBox("memory error!");
			delete pBmpData;
			return;
		}

		//把bmpFile里的内容读取并写入*pBmpData
		if (bmpFile.Read(pBmpData,dataBytes) != dataBytes)
		{
			AfxMessageBox("Read bmp data failed!");
			delete pBmpInfo;
			delete pBmpData;
			return;
		}
		bmpFile.Close();

		//至此，文件内容已经被存入pBmpInfo和pBmpData

		Display(IDC_IMAGE,pBmpInfo,pBmpData);
		
		//切换为关闭图片按钮
		button_flag = 1;
		SetDlgItemText(ID_OPEN,"关闭图片");
		GetDlgItem(IDC_FIX1)->EnableWindow(TRUE);
	}
	else
	{
		//关闭图片按钮功能

		delete[] pBmpInfo;
		delete[] pBmpData;

		dataBytes = 0;

		pBmpInfo = NULL;
		pBmpData = NULL;

		this->RedrawWindow();

		//切换为打开图片按钮
		button_flag = 0;
		SetDlgItemText(ID_OPEN,"打开图片");
		GetDlgItem(IDC_FIX1)->EnableWindow(FALSE);

	}
}

void Cimage1Dlg::OnBnClickedFix1()	//图像处理按钮
{
	// TODO: 在此添加控件通知处理程序代码

	pThread1 = AfxBeginThread(ThreadFunc1,this);

}

UINT ThreadFunc1(LPVOID lpParam)
{
	Cimage1Dlg * dlg = (Cimage1Dlg *)lpParam;
	//图像处理1

	BYTE* pBmpData1;           //图像数据
	pBmpData1 = (BYTE*)new char[dataBytes];
	memcpy(pBmpData1,pBmpData,dataBytes);

	double d1 = 0, d2 = 0;

	//图像数组指针（c是三维图像矩阵指针）
	unsigned char * c;

	BMP_To_GrayMatrix(pBmpInfo,pBmpData1,&c);
	Fix1(c, &d1, &d2);
	GrayMatrix_To_BMP(pBmpInfo,pBmpData1,&c);

	dlg->Display(IDC_IMAGE_1OUT,pBmpInfo,pBmpData1);
	
	//输出double数值
	char buffer1[30] = {0};
	sprintf_s(buffer1, "%lf", d1);
	dlg->GetDlgItem(IDC_NUM1)->SetWindowText(buffer1);

	char buffer2[30] = { 0 };
	sprintf_s(buffer2, "%lf", d2);
	dlg->GetDlgItem(IDC_NUM2)->SetWindowText(buffer2);

	//dlg->SetDlgItemInt(IDC_NUM1, -465, 1);		//显示int（有符号）
	//dlg->SetDlgItemInt(IDC_NUM1, -465, 0);		//显示int（无符号）

	delete[] pBmpData1;

	return 0;  
}

//	
//========================================================================================

/*

	//按像素点输出

	CDC *pDC0;
	pDC0 = GetDlgItem(IDC_IMAGE)->GetDC();//获得pictrue控件的DC

	for(int y=0;y<bmpInfo.biHeight;y++)
	{
		for(int x=0;x<bmpInfo.biWidth;x++)
		{
			char r,g,b;

			b = c[y][x][0];
			g = c[y][x][1];
			r = c[y][x][2];

			pDC0->SetPixel(x,y,RGB(r,g,b));
		}
	}



*/
