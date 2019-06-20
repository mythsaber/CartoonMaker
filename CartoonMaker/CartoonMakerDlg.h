
// CartoonMakerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<opencv.hpp>


// CCartoonMakerDlg �Ի���
class CCartoonMakerDlg : public CDialogEx
{
// ����
public:
	CCartoonMakerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARTOONMAKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedOpen();
private:
	CEdit m_url;
private:
	CSliderCtrl m_slider_times_sample;
	CSliderCtrl m_slider_times_bifilter;
	CSliderCtrl m_slider_size_bifilter;
	CSliderCtrl m_slider_sigmaspace;
	CSliderCtrl m_slider_sigmacolor;
	CSliderCtrl m_slider_size_medblur;
	CSliderCtrl m_slider_size_threshold;
	int m_edit_times_sample;
	int m_edit_times_bifilter;
	int m_edit_size_bifilter;
	int m_edit_sigmacolor;
	int m_edit_sigmaspace;
	int m_edit_size_medblur;
	int m_edit_size_threshold;
public:
	afx_msg void OnNMCustomdrawSliderTimesSample(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderTimesBifilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSizeBifilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSigmacolor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSigmaspace(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSizeMedblur(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSizeThreshold(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeTimesSample();
	afx_msg void OnEnChangeTimesBifilter();
	afx_msg void OnEnChangeSizeBifilter();
	afx_msg void OnEnChangeSigmacolor();
	afx_msg void OnEnChangeSigmaspace();
	afx_msg void OnEnChangeSizeMedblur();
	afx_msg void OnEnChangeSizeThreshold();
public:
	void  CCartoonMakerDlg::show_mat(const cv::Mat& mat, int pcid); //pcidΪpicture�ؼ�ID
private:
	cv::Mat m_srcimg;
public:
	afx_msg void OnBnClickedStartprocess();
	afx_msg void OnStnClickedDisplay();
};
