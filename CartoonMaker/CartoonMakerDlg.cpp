
// CartoonMakerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CartoonMaker.h"
#include "CartoonMakerDlg.h"
#include "afxdialogex.h"

#include<string>
#include "tool.h"
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCartoonMakerDlg 对话框

CCartoonMakerDlg::CCartoonMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CARTOONMAKER_DIALOG, pParent)
	, m_edit_times_sample(3)
	, m_edit_times_bifilter(3)
	, m_edit_size_bifilter(5)
	, m_edit_sigmacolor(50)
	, m_edit_sigmaspace(15)
	, m_edit_size_medblur(5)
	, m_edit_size_threshold(50)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCartoonMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEPATH, m_url);
	DDX_Control(pDX, IDC_SLIDER_TIMES_SAMPLE, m_slider_times_sample);
	DDX_Control(pDX, IDC_SLIDER_TIMES_BIFILTER, m_slider_times_bifilter);
	DDX_Control(pDX, IDC_SLIDER_SIZE_THRESHOLD, m_slider_size_threshold);
	DDX_Control(pDX, IDC_SLIDER_SIZE_MEDBLUR, m_slider_size_medblur);
	//  DDX_Control(pDX, IDC_SLIDER_SIZE_BIFILTER, m_slider_size_bifilter);
	DDX_Control(pDX, IDC_SLIDER_SIGMASPACE, m_slider_sigmaspace);
	DDX_Control(pDX, IDC_SLIDER_SIGMACOLOR, m_slider_sigmacolor);
	DDX_Control(pDX, IDC_SLIDER_SIZE_BIFILTER, m_slider_size_bifilter);
	DDX_Text(pDX, IDC_TIMES_SAMPLE, m_edit_times_sample);
	DDV_MinMaxInt(pDX, m_edit_times_sample, 1, 100);
	DDX_Text(pDX, IDC_TIMES_BIFILTER, m_edit_times_bifilter);
	DDV_MinMaxInt(pDX, m_edit_times_bifilter, 1, 100);
	DDX_Text(pDX, IDC_SIZE_BIFILTER, m_edit_size_bifilter);
	DDV_MinMaxInt(pDX, m_edit_size_bifilter, 1, 100);
	DDX_Text(pDX, IDC_SIGMACOLOR, m_edit_sigmacolor);
	DDV_MinMaxInt(pDX, m_edit_sigmacolor, 1, 100);
	DDX_Text(pDX, IDC_SIGMASPACE, m_edit_sigmaspace);
	DDV_MinMaxInt(pDX, m_edit_sigmaspace, 1, 100);
	DDX_Text(pDX, IDC_SIZE_MEDBLUR, m_edit_size_medblur);
	DDV_MinMaxInt(pDX, m_edit_size_medblur, 1, 100);
	DDX_Text(pDX, IDC_SIZE_THRESHOLD, m_edit_size_threshold);
	DDV_MinMaxInt(pDX, m_edit_size_threshold, 1, 100);
}

BEGIN_MESSAGE_MAP(CCartoonMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, &CCartoonMakerDlg::OnBnClickedAbout)
ON_BN_CLICKED(IDC_OPEN, &CCartoonMakerDlg::OnBnClickedOpen)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TIMES_SAMPLE, &CCartoonMakerDlg::OnNMCustomdrawSliderTimesSample)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TIMES_BIFILTER, &CCartoonMakerDlg::OnNMCustomdrawSliderTimesBifilter)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIZE_BIFILTER, &CCartoonMakerDlg::OnNMCustomdrawSliderSizeBifilter)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIGMACOLOR, &CCartoonMakerDlg::OnNMCustomdrawSliderSigmacolor)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIGMASPACE, &CCartoonMakerDlg::OnNMCustomdrawSliderSigmaspace)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIZE_MEDBLUR, &CCartoonMakerDlg::OnNMCustomdrawSliderSizeMedblur)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIZE_THRESHOLD, &CCartoonMakerDlg::OnNMCustomdrawSliderSizeThreshold)
ON_WM_HSCROLL()
ON_EN_CHANGE(IDC_TIMES_SAMPLE, &CCartoonMakerDlg::OnEnChangeTimesSample)
ON_EN_CHANGE(IDC_TIMES_BIFILTER, &CCartoonMakerDlg::OnEnChangeTimesBifilter)
ON_EN_CHANGE(IDC_SIZE_BIFILTER, &CCartoonMakerDlg::OnEnChangeSizeBifilter)
ON_EN_CHANGE(IDC_SIGMACOLOR, &CCartoonMakerDlg::OnEnChangeSigmacolor)
ON_EN_CHANGE(IDC_SIGMASPACE, &CCartoonMakerDlg::OnEnChangeSigmaspace)
ON_EN_CHANGE(IDC_SIZE_MEDBLUR, &CCartoonMakerDlg::OnEnChangeSizeMedblur)
ON_EN_CHANGE(IDC_SIZE_THRESHOLD, &CCartoonMakerDlg::OnEnChangeSizeThreshold)
ON_BN_CLICKED(IDC_STARTPROCESS, &CCartoonMakerDlg::OnBnClickedStartprocess)
ON_STN_CLICKED(IDC_DISPLAY, &CCartoonMakerDlg::OnStnClickedDisplay)
END_MESSAGE_MAP()


// CCartoonMakerDlg 消息处理程序

BOOL CCartoonMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_slider_times_sample.SetRange(1,10); //设置滑动范围
	m_slider_times_bifilter.SetRange(1, 10);
	m_slider_size_bifilter.SetRange(1, 10);
	m_slider_sigmaspace.SetRange(1, 100);
	m_slider_sigmacolor.SetRange(1, 100);
	m_slider_size_medblur.SetRange(1, 10);
	m_slider_size_threshold.SetRange(1, 100);

	m_slider_times_sample.SetTicFreq(1);//每1个单位画一刻度
	m_slider_times_bifilter.SetTicFreq(1);
	m_slider_size_bifilter.SetTicFreq(1);
	m_slider_sigmaspace.SetTicFreq(10);
	m_slider_sigmacolor.SetTicFreq(10);
	m_slider_size_medblur.SetTicFreq(1);
	m_slider_size_threshold.SetTicFreq(10);

	//设置edit control控件的显示初始值
	((CEdit *)GetDlgItem(IDC_TIMES_SAMPLE))->SetWindowText(CString(std::to_string(m_edit_times_sample).c_str()));
	((CEdit *)GetDlgItem(IDC_TIMES_BIFILTER))->SetWindowText(CString(std::to_string(m_edit_times_bifilter).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_BIFILTER))->SetWindowText(CString(std::to_string(m_edit_size_bifilter).c_str()));
	((CEdit *)GetDlgItem(IDC_SIGMACOLOR))->SetWindowText(CString(std::to_string(m_edit_sigmacolor).c_str()));
	((CEdit *)GetDlgItem(IDC_SIGMASPACE))->SetWindowText(CString(std::to_string(m_edit_sigmaspace).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_MEDBLUR))->SetWindowText(CString(std::to_string(m_edit_size_medblur).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_THRESHOLD))->SetWindowText(CString(std::to_string(m_edit_size_threshold).c_str()));

	m_slider_times_sample.SetPos(m_edit_times_sample);//设置滑动条滑块初始位置
	m_slider_times_bifilter.SetPos(m_edit_times_bifilter);
	m_slider_size_bifilter.SetPos(m_edit_size_bifilter);
	m_slider_sigmacolor.SetPos(m_edit_sigmacolor);
	m_slider_sigmaspace.SetPos(m_edit_sigmaspace);
	m_slider_size_medblur.SetPos(m_edit_size_medblur);
	m_slider_size_threshold.SetPos(m_edit_size_threshold);

	//设置文件路径对话框为只读
	m_url.SetReadOnly(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCartoonMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCartoonMakerDlg::OnPaint()
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
HCURSOR CCartoonMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCartoonMakerDlg::OnBnClickedAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
	//"Modal"表示CAboutDlg是一个模式对话框，
	//即弹出后，窗口其他位置不能在接收响应，
	//除非确定、叉掉后，才可以再点击敞口其他
	//位置
}

void CCartoonMakerDlg::OnBnClickedOpen()
{
	CString path;
	//TRUE为open对话框，FALSE为save as对话框
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		m_url.SetWindowTextW(path);
	}

	CString src_path;
	m_url.GetWindowTextW(src_path);
	std::string temp = CW2A(src_path.GetString());
	m_srcimg = imread(temp);
	show_mat(m_srcimg, IDC_DISPLAY);
}



void CCartoonMakerDlg::OnNMCustomdrawSliderTimesSample(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderTimesBifilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeBifilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSigmacolor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSigmaspace(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeMedblur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeThreshold(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//拖动滑动块的事件响应函数
void CCartoonMakerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);//接收编辑框中的数据，把控件内容装入控件变量。

	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER_TIMES_SAMPLE:
		m_edit_times_sample = pSlider->GetPos(); //编辑框获取滑动条当前位置的值
		break;
	case IDC_SLIDER_TIMES_BIFILTER:
		m_edit_times_bifilter = pSlider->GetPos();
		break;
	case IDC_SLIDER_SIZE_BIFILTER:
		m_edit_size_bifilter = pSlider->GetPos();
		break;
	case IDC_SLIDER_SIGMACOLOR:
		m_edit_sigmacolor = pSlider->GetPos();
		break;
	case IDC_SLIDER_SIGMASPACE:
		m_edit_sigmaspace = pSlider->GetPos();
		break;
	case IDC_SLIDER_SIZE_MEDBLUR:
		m_edit_size_medblur = pSlider->GetPos();
		break;
	case IDC_SLIDER_SIZE_THRESHOLD:
		m_edit_size_threshold = pSlider->GetPos();
		break;
	}

	UpdateData(FALSE);//更新数据到编辑框，用控件变量的值更新控件

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//修改edit control内容的事件响应函数
void CCartoonMakerDlg::OnEnChangeTimesSample()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);//接收编辑框中的数据，把控件内容装入控件变量
	m_slider_times_sample.SetPos(m_edit_times_sample); //修改滑块位置
}


void CCartoonMakerDlg::OnEnChangeTimesBifilter()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_times_bifilter.SetPos(m_edit_times_bifilter);
}


void CCartoonMakerDlg::OnEnChangeSizeBifilter()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_size_bifilter.SetPos(m_edit_size_bifilter);
}


void CCartoonMakerDlg::OnEnChangeSigmacolor()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_sigmacolor.SetPos(m_edit_sigmacolor);
}


void CCartoonMakerDlg::OnEnChangeSigmaspace()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_sigmaspace.SetPos(m_edit_sigmaspace);
}


void CCartoonMakerDlg::OnEnChangeSizeMedblur()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_size_medblur.SetPos(m_edit_size_medblur);
}


void CCartoonMakerDlg::OnEnChangeSizeThreshold()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_slider_size_threshold.SetPos(m_edit_size_threshold);
}

void  CCartoonMakerDlg::show_mat(const Mat& mat, int pcid) //pcid为picture控件ID
{
	if (mat.empty()) {
		return;
	}

	//获取图片的宽 高度
	int pic_width = mat.cols;
	int pic_height = mat.rows;

	//获取Picture Control控件的大小
	CRect rect;
	GetDlgItem(pcid)->GetWindowRect(&rect); //GetDlgItem()在afxwin,h头文件中
	//将客户区选中到控件表示的矩形区域内
	//ScreenToClient(&rect);

	CString msg;
	msg.Format(_T("tImgWidth=%d,tImgHeight=%d, rect：w=%d, h=%d"), pic_width, pic_height, rect.Width(), rect.Height());
	//MessageBox(msg, _T("showMat"), MB_OK); 

	int new_width, new_height;

	int left = 0, top = 0, right = rect.Width(), bottom = rect.Height();
	if (pic_width/ (double)pic_height>rect.Width()/(double)rect.Height()) {
		//如果图像相对控件是横的
		new_width = rect.Width();
		new_height = rect.Width() * pic_height / pic_width;
		top = (new_width - new_height) / 2;
		bottom = rect.Height() - top;
	}
	else {
		//如果图像相对控件是竖的
		new_height = rect.Height();
		new_width = rect.Height() * pic_width / pic_height;
		left = (new_height - new_width) / 2;
		right = rect.Width() - left;
	}

	Mat zoom_img;
	cv::resize(mat, zoom_img, Size(new_width - 1, new_height - 1));

	//把opencv的图转为CImage,才能显示在图像控件上
	CImage cimg;
	tool::mat_to_cimage(zoom_img, cimg);

	msg.Format(_T("neww=%d, newh=%d"), cimg.GetWidth(), cimg.GetHeight());
	//MessageBox(msg, _T("mm"), MB_OK); 

	//以下是显示
	CWnd *pwnd = GetDlgItem(pcid);//获取控件句柄 

	CDC *pdc = pwnd->GetDC();//获取picture的DC
			
	CBrush brush(RGB(255, 255, 255));//白色背景填充,保留边框

	CRect temp = CRect(1, 1, rect.Width() - 2, rect.Height() - 2);
	pdc->FillRect(temp, &brush);
	cimg.Draw(pdc->m_hDC, CRect(left + 1, top + 1, right - 1, bottom - 1));

	ReleaseDC(pdc);
	//msg.Format(_T("left=%d,top=%d, right=%d,bottom=%d"), left, top, right, bottom);
	//MessageBox(msg, _T("showMat"), MB_OK);
}

void CCartoonMakerDlg::OnBnClickedStartprocess()
{
	//多次下采样-->多次双边滤波-->多次上采样-->中值滤波-->边缘检测
	//-->中值滤波结果+边缘检测结果
	Mat down;
	m_srcimg.copyTo(down);
	for (int i = 0; i < m_edit_times_sample; i++)
	{
		pyrDown(down, down);
	}
	show_mat(down, IDC_DISPLAY);

	Mat temp;
	for (int i = 0; i < m_edit_times_bifilter; i++)
	{
		//函数bilateralFilter()要求src.data != dst.data
		bilateralFilter(down,temp,m_edit_size_bifilter,m_edit_sigmacolor,m_edit_sigmaspace);
		Mat help = temp;
		temp = down;
		down = help;
	}
	show_mat(down, IDC_DISPLAY);


	for (int i = 0; i < m_edit_times_sample; i++)
	{
		pyrUp(down, down);
	}
	show_mat(down, IDC_DISPLAY);

	medianBlur(down,down, m_edit_size_medblur/2*2+1); //ksize必须是奇数
	show_mat(down, IDC_DISPLAY);

	//Mat gray, smooth, edge, result(down.size(), down.type(), Scalar(0));
	//cvtColor(down, gray, CV_RGB2GRAY);
	//GaussianBlur(gray, gray, Size(3, 3), 1.5);
	//show_mat(gray, IDC_DISPLAY);
	//Canny(gray, edge, m_edit_size_threshold, m_edit_size_threshold / 2 * 3);
	//show_mat(edge, IDC_DISPLAY);
	//down.copyTo(result, edge);
	
	//Mat edge;
	//Canny(down, edge, m_edit_size_threshold / 2 * 3, m_edit_size_threshold);
	////Canny输出单通道图
	//Mat rgbedge;
	//cvtColor(edge,rgbedge,COLOR_GRAY2BGR);
	//show_mat(rgbedge, IDC_DISPLAY);
	//Mat result;
	//addWeighted(down,0.5,rgbedge,0.5,0,result);

	Mat gray;
	cvtColor(down, gray, CV_RGB2GRAY);
	show_mat(gray, IDC_DISPLAY);
	Mat edge;
	adaptiveThreshold(gray,edge,255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,
		m_edit_size_threshold/2*2+1,10);
	show_mat(edge, IDC_DISPLAY);

	Mat coloredg;
	down.copyTo(coloredg,edge);
	show_mat(coloredg, IDC_DISPLAY);

	Mat result;
	addWeighted(down,0.9,coloredg,0.1,0,result);

	show_mat(result, IDC_DISPLAY);
}


void CCartoonMakerDlg::OnStnClickedDisplay()
{
	// TODO: 在此添加控件通知处理程序代码
}
