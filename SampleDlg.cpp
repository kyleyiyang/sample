// SampleDlg.cpp : implementation file
//

#pragma once

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"
#include "alp.h"
//#include "StdAfx.h"
#include <cmath>

#include <memory>

#include "afxdialogex.h"
#include <locale>
#include <io.h>
#include <assert.h>
////////////////////////////
#include "stdlib.h"
#include "stdio.h"
#include "wchar.h"
#include <time.h>
using namespace std;
///////////////////////////////////
#pragma comment(lib, "alp4395.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)	
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_EDIT1, &CSampleDlg::OnBnClickedButtonLoad)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
	,m_filepath(_T("C:\\Library\\Documents"))
	//,m_filepath(_T("E:\\128\\128_p\\STOne_Recon_Simulation\\test-update\\64-1024x1024"))
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CAPTURE,m_capSize);
	DDX_Control(pDX, IDC_COMBO1,m_selectValue);
	DDX_Control(pDX, IDC_COMBO2,m_PType);
	DDX_Text (pDX, IDC_EDIT1, m_filepath);
	DDX_Control(pDX, IDC_Ill_Time,m_synchPwidth);
	DDX_Control(pDX, IDC_Pic_Time,m_PicTime);
	DDX_Control(pDX, IDC_RATIO,m_SamplingRatio);
	//{{AFX_DATA_MAP(CSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SEQ_LOAD, &CSampleDlg::OnBnClickedButtonSeqLoad)
	ON_BN_CLICKED(IDC_BUTTON_SEQ_FREE, &CSampleDlg::OnBnClickedButtonSeqFree)
	//ON_EN_CHANGE(IDC_EDIT_CAPTURE, &CSampleDlg::OnEnChangeEditCapture)
	//ON_STN_CLICKED(IDC_STATIC_1, &CSampleDlg::OnStnClickedStatic1)
	ON_BN_CLICKED(IDC_BUTTON_DevAlloc, &CSampleDlg::OnBnClickedButtonDevalloc)
	ON_BN_CLICKED(IDC_BUTTON_DMDFree, &CSampleDlg::OnBnClickedButtonDmdfree)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CSampleDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSampleDlg::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT_DMDID, &CSampleDlg::OnEnChangeEditDmdid)
	ON_EN_CHANGE(IDC_EDIT_CAPTURE, &CSampleDlg::OnEnChangeEditCapture)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_capSize.ShowWindow(SW_SHOW);
	m_capSize.SetWindowTextA("1");//1
	m_selectValue.ShowWindow(SW_SHOW);
	m_selectValue.SetWindowTextA("16384");
    m_PType.ShowWindow(SW_SHOW);
	m_PType.SetWindowTextA("STOne");
	m_synchPwidth.ShowWindow(SW_SHOW);
	m_synchPwidth.SetWindowTextA("3333"); 
	m_PicTime.ShowWindow(SW_SHOW);
	m_PicTime.SetWindowTextA("500");
	m_SamplingRatio.ShowWindow(SW_SHOW);
	m_SamplingRatio.SetWindowTextA("100");
	GetDlgItem(IDC_BUTTON_SEQ_FREE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DMDFree)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEQ_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
//	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon
////	CString loop_new;
////	for(int idx=1; idx<17;idx++)
////	{
////		loop_new.Format("%d",idx );
////		m_strSize.ShowWindow(SW_SHOW);
////	    m_strSize.SetWindowTextA(loop_new);
		//GetDlgItem(IDC_EDIT_SIZE)->EnableWindow(true);
	    //GetDlgItem(IDC_EDIT_SIZE)->SetWindowTextA(loop_new);
////	  OnBtnCapture();
////	}
  
	// TODO: Add extra initialization here 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);

	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSampleDlg::OnPaint() 
{
	if (IsIconic())
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

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);	
	}
	else
	{
		CDialog::OnPaint();
	}
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnBtnCapture() 
{
	
    int	nWidth = 1920;
	int	nHeight = 1080;
	int	nBitSize = 0;
	int	nFrameCount = 64;
	int RATIO;
	
	char szVersion[256] = {0};
	

	if(CaptureData(nWidth, nHeight,nFrameCount,nSizeX,nSizeY,nDevId)==FALSE)
	{
		//AlpDevFree(nDevId);
		AfxMessageBox(_T("Unable to capture data"));
		return;
	}

}
int CSampleDlg::CaptureData(int nWidth, int nHeight,int nFrameCount,long nSizeX,long nSizeY,ALP_ID nDevId )
{
	CString fileSize, loop_new, captureSize;
	CString infile;
	CString triggerWTime, PicTime, SamplingRatio;
	CString msg;
	
	DWORD	dwRetStatus = DCAM_WAITSTATUS_UNCOMPLETED;
	WORD*	pDataBuff   = NULL;
	
    long long count=0, count1=0;
    
	UCHAR *pImageData=NULL;
	UCHAR *pImageDataone=NULL;
	
	int nImageSize=0;
	int file_read_ck;
	int buf_size=256;
	int in_file_size=4*buf_size;

	file_read_ck=in_file_size/buf_size +1;
	//const long nPictureTime = 33334; //30HZ
	// const long p_width=3333;

	//const long nPictureTime = 3333;//300HZ
	//const long p_width=333;

	//const long nPictureTime = 2000; //500HZ
	//const long p_width=200;

	//const long nPictureTime = 666;//1500HZ
	//const long p_width=66;
	//const long nPictureTime = 200; //5000HZ
	 //const long p_width=50;
	 //const long nPictureTime = 500; //2000HZ
	 //const long p_width=50;
	 //
	 //m_synchPwidth.GetWindowTextA(triggerWTime);
	//if(isNumber((LPCTSTR)triggerWTime)==false)
	//{
		//AfxMessageBox(_T("The synchPulseWidth is not a number"));
		//return 0;
	//}


	m_PicTime.GetWindowTextA(PicTime);
	if(isNumber((LPCTSTR)PicTime)==false)
	{
		AfxMessageBox(_T("The DMD freq/picture time is not a number"));
		return 0;
	}

	m_SamplingRatio.GetWindowTextA(SamplingRatio);

	int RATIO = atoi((LPCTSTR)SamplingRatio);

	const long nPictureTime=1000000/atoi((LPCTSTR)PicTime);
	const long p_width=nPictureTime/10;
	
	
	// Calculation Image size and allocate buffer
	nImageSize = nWidth * nHeight; 

	m_selectValue.GetWindowTextA(fileSize);
	if(isNumber((LPCTSTR)fileSize)==false)
	{
		AfxMessageBox(_T("The file size value is not a number"));
		return 0;
	}
	int size=atoi((LPCTSTR)fileSize);

	m_capSize.GetWindowTextA(captureSize);
	if(isNumber((LPCTSTR)captureSize)==false)
	{
		AfxMessageBox(_T("The capture size value is not a number"));
		return 0;
	}
	int capsize=atoi((LPCTSTR)captureSize);
	


	AlpSeqTiming(nDevId, nSeqId, ALP_DEFAULT, nPictureTime, ALP_DEFAULT,p_width,ALP_DEFAULT);
    GetDlgItem(IDC_BUTTON_SEQ_FREE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(FALSE);
	for(int loop=0; loop<capsize; loop++)
	{
		AlpProjStart(nDevId, nSeqId);
	    AlpProjWait (nDevId);
	}
			  
	 GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	OnBnClickedButton1();
	 return 0;
}
void CSampleDlg::OnBnClickedButtonSeqLoad( )
{
	int result;
	int	nFrameCount = 64;
	long imgsize, rfilesize;
	long long count=0, count1=0;
    int loopnum;
	int file_loop_ck, file_read_ck;
	int buf_size=256;
	int in_file_size=4*buf_size;
	
	long start_poc=0;
	long end_poc=0;

	long seekd;

	CString message,infile,out_message;
	CString fileSize, loop_new, captureSize;
	CString func_name, SamplingRatio;
	CString outmsg;
	FILE *fp;

	UCHAR *pImageData=NULL;
	UCHAR *pImageDataone=NULL;
	
	file_read_ck=in_file_size/buf_size +1;
	 
	m_PType.GetWindowTextA(func_name);
	
	m_selectValue.GetWindowTextA(fileSize);
	if(isNumber((LPCTSTR)fileSize)==false)
	{
		AfxMessageBox(_T("The file size value is not a number"));
		return ;
	}
	
	long RATIO=atoi((LPCTSTR)SamplingRatio);

	int size_in=atoi((LPCTSTR)fileSize);
	int size;
	if(size_in>=16384)
	{
		size=16384;
	}
	else
	{
		size=size_in;
	}

	long rate=100/RATIO;
	//if(m_PType.IsEmpty())
	//{
	//	AfxMessageBox(_T("Please select input file type"));
	//	return ;
	//}
	if(m_filepath.IsEmpty())
	{
		AfxMessageBox(_T("Please select input file folder"));
		return ;
	}

	imgsize=sizeof(UCHAR)*nSizeX*nSizeY;
	rfilesize=buf_size*sizeof(UCHAR)*nSizeX*nSizeY;
	pImageData = (UCHAR*)malloc(rfilesize);
    if(!pImageData)
	{
		    
	    AfxMessageBox(_T("Memory alloc fails"));
		PostQuitMessage(0);
	    return ;
	 }

	 pImageDataone=(UCHAR*)malloc(imgsize);
     if(!pImageDataone)
	 {    
	    AfxMessageBox(_T("Memory alloc fails"));
		PostQuitMessage(0);
		return ;
	 }
	 
	 FillMemory(pImageDataone,nSizeX*nSizeY,0x00);
	 //file_loop_ck=size/in_file_size +1;
	 file_loop_ck=size/(rate*in_file_size) +1; 
	 loopnum=rfilesize/(nFrameCount*imgsize);
     for(int idx=1; idx<file_loop_ck;idx++)
	 {
	   	
		infile.Format("%s\\%s_pattern_%d_1024int8_%d.txt",m_filepath,func_name,size_in,idx);
		//infile.Format("%s\\STOne_pattern_%d_1024int8_%d.txt",m_filepath,size_in,idx);
	    fp=fopen(infile, "rb" );
		if(fp==NULL)
		{
			out_message.Format("Unable to read the input file: %s",infile); 
			AfxMessageBox(_T(out_message));
		    return;
		}
		seekd=fseek(fp,0,SEEK_SET);
		file_read_ck = file_read_ck;
		for(int file_r_loop=1; file_r_loop< file_read_ck; file_r_loop++)
		{
			
			 seekd=fseek(fp, (file_r_loop-1)*rfilesize, SEEK_SET);
		    result=fread(pImageData,1,rfilesize,fp);
			
	        if(result!=rfilesize)
            {
		      fclose(fp);
			  pImageData=NULL;
		      free(pImageData);
			  delete [] pImageData;
			  pImageDataone=NULL;
			  free(pImageDataone);
			  delete [] pImageDataone;
		      AfxMessageBox(_T("Error data read"));
		      return ;
	        }
	    
			if(idx==1)
			{
			   if(file_r_loop==1)
			   {  
				   if(AlpSeqAlloc(nDevId, 1,(size+1), &nSeqId)!=ALP_OK)
				   {
					   AfxMessageBox(_T("DMD sequence allocate failed in loop#1"));
						pImageData=NULL;
						free(pImageData);
			            delete [] pImageData;
						pImageDataone=NULL;
			            free(pImageDataone);
			            delete [] pImageDataone;
						return;
				   }
		    	   if(AlpSeqPut(nDevId, nSeqId,0,1,pImageDataone )!=ALP_OK)
				   {
					   AfxMessageBox(_T("DMD sequence put error in loop#1"));
						pImageData=NULL;
						free(pImageData);
			            delete [] pImageData;
						pImageDataone=NULL;
			            free(pImageDataone);
			            delete [] pImageDataone;
						return;
				   }
			   }	  
			}
			 
			start_poc=1+(file_r_loop-1)*buf_size+(idx-1)*in_file_size;
			//start_poc=(file_r_loop-1)*buf_size+(idx-1)*in_file_size;
		    if(AlpSeqPut(nDevId, nSeqId,start_poc,buf_size,pImageData )!=ALP_OK)
			{
				outmsg.Format("DMD sequence put error"); 
				AfxMessageBox(_T(outmsg));
				 pImageData=NULL;
				 free(pImageData);
			     delete [] pImageData;
				 pImageDataone=NULL;
			     free(pImageDataone);
			     delete [] pImageDataone;
				 return;
			}
			
	    }
	    fclose(fp);
	 }
	 GetDlgItem(IDC_BUTTON_SEQ_FREE)->EnableWindow(TRUE);
	 GetDlgItem(IDC_BUTTON_SEQ_LOAD)->EnableWindow(FALSE);
	 GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(TRUE);
	       
	 pImageData=NULL;
	 free(pImageData);
	 delete [] pImageData;
	 
	 pImageDataone=NULL;
	 free(pImageDataone);
	 delete [] pImageDataone;
	
	 return ;
}

void CSampleDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	//CFileDialog loadfiledlg(TRUE);
	CFolderPickerDialog dlgFolder;
	//CFileDialog loadfiledlg(FALSE);
	//IFileOpenDialog * OpenDlgPtr;
	if(dlgFolder.DoModal()==IDOK)
	{
		m_filepath = dlgFolder.GetFolderPath();
	}

	//if (loadfiledlg.DoModal() == IDOK){
	//	m_filepath = loadfiledlg.GetPathName();
		
	//}
	UpdateData(FALSE);
	//UpdateData(TRUE);
}

bool CSampleDlg::isNumber(const std::string& s)
{
	if (s.length() == 0)
		return false;
	bool hasdot = false;
	std::locale loc;
	std::string::const_iterator it = s.begin();
	if (*it == '-'){
		if (++it == s.end())
			return false;
	} 
	while (it != s.end()){
		if (std::isdigit(*it, loc))
			++it;
		else if (*it == '.' && !hasdot){
			hasdot = true; ++it;
		}else
			return false;
	}
	return true;
}


void CSampleDlg::OnBnClickedButtonSeqFree()
{
	int rc;
	rc=AlpSeqFree(nDevId,nSeqId);
	if(rc!=ALP_OK)
	{
		 AfxMessageBox(_T("Error data read"));
		 return ;
	}
	else
	{
		nSeqId=0;
		GetDlgItem(IDC_BUTTON_SEQ_FREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEQ_LOAD)->EnableWindow(TRUE);
	}
}


void CSampleDlg::OnBnClickedButtonDevalloc()
{
	CString dmd_id;
	//Allocate the device
	if(ALP_OK!=AlpDevAlloc(ALP_DEFAULT, ALP_DEFAULT, &nDevId))
	{
		AfxMessageBox(_T("Unable to alloc the DMD device"));
		return;
	}
	 if(ALP_OK!=AlpDevInquire(nDevId, ALP_DEV_DISPLAY_HEIGHT, &nSizeY) ||ALP_OK!=AlpDevInquire(nDevId, ALP_DEV_DISPLAY_WIDTH, &nSizeX))
	{
		AlpDevFree(nDevId);
        AfxMessageBox(_T("Unable to get the DMD device size"));
		return;
	}
	 if( ALP_OK!=AlpDevInquire(nDevId, ALP_DEVICE_NUMBER, &DMD_num) )
 	{
		AfxMessageBox(_T("Unable to get the DMD device ID"));
		return;
	}
	GetDlgItem(IDC_EDIT_DMDID)->EnableWindow(true);
	dmd_id.Format("%d",DMD_num);
	GetDlgItem(IDC_EDIT_DMDID)->SetWindowTextA(dmd_id);	
	GetDlgItem(IDC_BUTTON_DMDFree)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEQ_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DevAlloc) -> EnableWindow(FALSE);
}


void CSampleDlg::OnBnClickedButtonDmdfree()
{
	CString dmd_id;
	if(ALP_OK!= AlpDevHalt(nDevId))
	{
		AfxMessageBox(_T("Unable to stop DMD"));
		return;
	}
	if(ALP_OK!=AlpDevFree(nDevId))
	{
		AfxMessageBox(_T("Unable to free the DMD device"));
		return;
	}
	GetDlgItem(IDC_EDIT_DMDID)->EnableWindow(true);
	dmd_id.Format(_T(" "));
	GetDlgItem(IDC_EDIT_DMDID)->SetWindowTextA(dmd_id);
	GetDlgItem(IDC_EDIT1)->EnableWindow(true);
	GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T("C:\\Libraries\\Documents"));
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);
	GetDlgItem(IDC_COMBO1)->SetWindowTextA(_T("16384"));
	GetDlgItem(IDC_COMBO2)->EnableWindow(true);
	GetDlgItem(IDC_COMBO2)->SetWindowTextA(_T("STOne"));
	GetDlgItem(IDC_BUTTON_DevAlloc) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DMDFree)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEQ_LOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DMDFree)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
}


void CSampleDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AlpProjHalt(nDevId);
    GetDlgItem(IDC_BUTTON_SEQ_FREE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CAPTURE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	
}

void CSampleDlg::OnEnChangeEditCapture()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
