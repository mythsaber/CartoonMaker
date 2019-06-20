
// CartoonMakerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<opencv.hpp>


// CCartoonMakerDlg 对话框
class CCartoonMakerDlg : public CDialogEx
{
// 构造
public:
	CCartoonMakerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARTOONMAKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	void  CCartoonMakerDlg::show_mat(const cv::Mat& mat, int pcid); //pcid为picture控件ID
private:
	cv::Mat m_srcimg;
public:
	afx_msg void OnBnClickedStartprocess();
	afx_msg void OnStnClickedDisplay();
};
