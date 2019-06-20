
// CartoonMakerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCartoonMakerDlg �Ի���

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


// CCartoonMakerDlg ��Ϣ�������

BOOL CCartoonMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_slider_times_sample.SetRange(1,10); //���û�����Χ
	m_slider_times_bifilter.SetRange(1, 10);
	m_slider_size_bifilter.SetRange(1, 10);
	m_slider_sigmaspace.SetRange(1, 100);
	m_slider_sigmacolor.SetRange(1, 100);
	m_slider_size_medblur.SetRange(1, 10);
	m_slider_size_threshold.SetRange(1, 100);

	m_slider_times_sample.SetTicFreq(1);//ÿ1����λ��һ�̶�
	m_slider_times_bifilter.SetTicFreq(1);
	m_slider_size_bifilter.SetTicFreq(1);
	m_slider_sigmaspace.SetTicFreq(10);
	m_slider_sigmacolor.SetTicFreq(10);
	m_slider_size_medblur.SetTicFreq(1);
	m_slider_size_threshold.SetTicFreq(10);

	//����edit control�ؼ�����ʾ��ʼֵ
	((CEdit *)GetDlgItem(IDC_TIMES_SAMPLE))->SetWindowText(CString(std::to_string(m_edit_times_sample).c_str()));
	((CEdit *)GetDlgItem(IDC_TIMES_BIFILTER))->SetWindowText(CString(std::to_string(m_edit_times_bifilter).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_BIFILTER))->SetWindowText(CString(std::to_string(m_edit_size_bifilter).c_str()));
	((CEdit *)GetDlgItem(IDC_SIGMACOLOR))->SetWindowText(CString(std::to_string(m_edit_sigmacolor).c_str()));
	((CEdit *)GetDlgItem(IDC_SIGMASPACE))->SetWindowText(CString(std::to_string(m_edit_sigmaspace).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_MEDBLUR))->SetWindowText(CString(std::to_string(m_edit_size_medblur).c_str()));
	((CEdit *)GetDlgItem(IDC_SIZE_THRESHOLD))->SetWindowText(CString(std::to_string(m_edit_size_threshold).c_str()));

	m_slider_times_sample.SetPos(m_edit_times_sample);//���û����������ʼλ��
	m_slider_times_bifilter.SetPos(m_edit_times_bifilter);
	m_slider_size_bifilter.SetPos(m_edit_size_bifilter);
	m_slider_sigmacolor.SetPos(m_edit_sigmacolor);
	m_slider_sigmaspace.SetPos(m_edit_sigmaspace);
	m_slider_size_medblur.SetPos(m_edit_size_medblur);
	m_slider_size_threshold.SetPos(m_edit_size_threshold);

	//�����ļ�·���Ի���Ϊֻ��
	m_url.SetReadOnly(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCartoonMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCartoonMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCartoonMakerDlg::OnBnClickedAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
	//"Modal"��ʾCAboutDlg��һ��ģʽ�Ի���
	//�������󣬴�������λ�ò����ڽ�����Ӧ��
	//����ȷ��������󣬲ſ����ٵ����������
	//λ��
}

void CCartoonMakerDlg::OnBnClickedOpen()
{
	CString path;
	//TRUEΪopen�Ի���FALSEΪsave as�Ի���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderTimesBifilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeBifilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSigmacolor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSigmaspace(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeMedblur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCartoonMakerDlg::OnNMCustomdrawSliderSizeThreshold(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

//�϶���������¼���Ӧ����
void CCartoonMakerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);//���ձ༭���е����ݣ��ѿؼ�����װ��ؼ�������

	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER_TIMES_SAMPLE:
		m_edit_times_sample = pSlider->GetPos(); //�༭���ȡ��������ǰλ�õ�ֵ
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

	UpdateData(FALSE);//�������ݵ��༭���ÿؼ�������ֵ���¿ؼ�

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//�޸�edit control���ݵ��¼���Ӧ����
void CCartoonMakerDlg::OnEnChangeTimesSample()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���ձ༭���е����ݣ��ѿؼ�����װ��ؼ�����
	m_slider_times_sample.SetPos(m_edit_times_sample); //�޸Ļ���λ��
}


void CCartoonMakerDlg::OnEnChangeTimesBifilter()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_times_bifilter.SetPos(m_edit_times_bifilter);
}


void CCartoonMakerDlg::OnEnChangeSizeBifilter()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_size_bifilter.SetPos(m_edit_size_bifilter);
}


void CCartoonMakerDlg::OnEnChangeSigmacolor()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_sigmacolor.SetPos(m_edit_sigmacolor);
}


void CCartoonMakerDlg::OnEnChangeSigmaspace()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_sigmaspace.SetPos(m_edit_sigmaspace);
}


void CCartoonMakerDlg::OnEnChangeSizeMedblur()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_size_medblur.SetPos(m_edit_size_medblur);
}


void CCartoonMakerDlg::OnEnChangeSizeThreshold()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_slider_size_threshold.SetPos(m_edit_size_threshold);
}

void  CCartoonMakerDlg::show_mat(const Mat& mat, int pcid) //pcidΪpicture�ؼ�ID
{
	if (mat.empty()) {
		return;
	}

	//��ȡͼƬ�Ŀ� �߶�
	int pic_width = mat.cols;
	int pic_height = mat.rows;

	//��ȡPicture Control�ؼ��Ĵ�С
	CRect rect;
	GetDlgItem(pcid)->GetWindowRect(&rect); //GetDlgItem()��afxwin,hͷ�ļ���
	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������
	//ScreenToClient(&rect);

	CString msg;
	msg.Format(_T("tImgWidth=%d,tImgHeight=%d, rect��w=%d, h=%d"), pic_width, pic_height, rect.Width(), rect.Height());
	//MessageBox(msg, _T("showMat"), MB_OK); 

	int new_width, new_height;

	int left = 0, top = 0, right = rect.Width(), bottom = rect.Height();
	if (pic_width/ (double)pic_height>rect.Width()/(double)rect.Height()) {
		//���ͼ����Կؼ��Ǻ��
		new_width = rect.Width();
		new_height = rect.Width() * pic_height / pic_width;
		top = (new_width - new_height) / 2;
		bottom = rect.Height() - top;
	}
	else {
		//���ͼ����Կؼ�������
		new_height = rect.Height();
		new_width = rect.Height() * pic_width / pic_height;
		left = (new_height - new_width) / 2;
		right = rect.Width() - left;
	}

	Mat zoom_img;
	cv::resize(mat, zoom_img, Size(new_width - 1, new_height - 1));

	//��opencv��ͼתΪCImage,������ʾ��ͼ��ؼ���
	CImage cimg;
	tool::mat_to_cimage(zoom_img, cimg);

	msg.Format(_T("neww=%d, newh=%d"), cimg.GetWidth(), cimg.GetHeight());
	//MessageBox(msg, _T("mm"), MB_OK); 

	//��������ʾ
	CWnd *pwnd = GetDlgItem(pcid);//��ȡ�ؼ���� 

	CDC *pdc = pwnd->GetDC();//��ȡpicture��DC
			
	CBrush brush(RGB(255, 255, 255));//��ɫ�������,�����߿�

	CRect temp = CRect(1, 1, rect.Width() - 2, rect.Height() - 2);
	pdc->FillRect(temp, &brush);
	cimg.Draw(pdc->m_hDC, CRect(left + 1, top + 1, right - 1, bottom - 1));

	ReleaseDC(pdc);
	//msg.Format(_T("left=%d,top=%d, right=%d,bottom=%d"), left, top, right, bottom);
	//MessageBox(msg, _T("showMat"), MB_OK);
}

void CCartoonMakerDlg::OnBnClickedStartprocess()
{
	//����²���-->���˫���˲�-->����ϲ���-->��ֵ�˲�-->��Ե���
	//-->��ֵ�˲����+��Ե�����
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
		//����bilateralFilter()Ҫ��src.data != dst.data
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

	medianBlur(down,down, m_edit_size_medblur/2*2+1); //ksize����������
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
	////Canny�����ͨ��ͼ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
