
// Restore4HDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Restore4H.h"
#include "Restore4HDlg.h"
#include "afxdialogex.h"

#include "CommonInclude.h"
#include "ListDisk.h"
#include "Detail.h"
#include "Scan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CRestore4HDlg dialog



CRestore4HDlg::CRestore4HDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RESTORE4H_DIALOG, pParent)
	, PlainButton(0)
	, HexInput(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRestore4HDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, DriveList);
	DDX_Control(pDX, IDC_EDIT1, StrInput);
	DDX_Control(pDX, IDC_EDIT2, ProcessingBytes);
	DDX_Control(pDX, IDC_EDIT5, StartPosition);
	DDX_Control(pDX, IDC_EDIT6, EndPosition);
}

BEGIN_MESSAGE_MAP(CRestore4HDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRestore4HDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRestore4HDlg::OnBnClickedButton2)
//	ON_BN_CLICKED(IDOK, &CRestore4HDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CRestore4HDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CRestore4HDlg::OnNMCustomdrawList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CRestore4HDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRestore4HDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CRestore4HDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CRestore4HDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CRestore4HDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CRestore4HDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CRestore4HDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CRestore4HDlg message handlers

BOOL CRestore4HDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//Get drive list
	unsigned char **DriveListChr;
	int nDriveList = getDriveList(&DriveListChr);
	for (int i = 0; i < nDriveList; i++)
	{
		DriveList.AddString(CA2W((char*) DriveListChr[i]));
	}

	//Set default plain text button
	CButton* InitButton = (CButton*)this->GetDlgItem(IDC_RADIO1);
	InitButton->SetCheck(1);

	CListCtrl* listctrl = (CListCtrl*)GetDlgItem(IDC_LIST2);
	listctrl->InsertColumn(0, HcharStringToLPCTSTR((unsigned char*) "Position"), -1, 100, -1);
	listctrl->InsertColumn(1, HcharStringToLPCTSTR((unsigned char*) "Data"), 0, 300, -1);
	listctrl->SetExtendedStyle(listctrl->GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	/*
	int t = listctrl->InsertItem(0, HcharStringToLPCTSTR((unsigned char*) "donno"));
	listctrl->SetItemText(t, 1, HcharStringToLPCTSTR((unsigned char*) "which number now..."));
	listctrl->DeleteAllItems();
	t = listctrl->InsertItem(0, HcharStringToLPCTSTR((unsigned char*) "donno2"));
	listctrl->SetItemText(t, 1, HcharStringToLPCTSTR((unsigned char*) "which number now...2"));
	*/

	listctrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	listctrl->InsertColumn(0, HcharStringToLPCTSTR((unsigned char*) "Position"), 0, 75, -1);
	for (int i = 0; i < DETAIL_SIZE; i++)
	{
		listctrl->InsertColumn(i+1, HcharStringToLPCTSTR(Hitoa(i)), 0, 25, -1); //
	}
	listctrl->InsertColumn(DETAIL_SIZE + 1, HcharStringToLPCTSTR((unsigned char*) "Plain"), 0, 50, -1);
	for (int i = 0; i < DETAIL_SIZE; i++)
	{
		listctrl->InsertColumn(i + DETAIL_SIZE + 2, HcharStringToLPCTSTR(Hitoa(i)), 0, 21, -1); //
	}

	//Init start position and end position to 0
	CEdit *CEdittemp;
	CEdittemp = (CEdit*)GetDlgItem(IDC_EDIT5);
	CEdittemp->SetWindowTextW(HcharStringToLPCTSTR(Hitoa(bufferstart)));
	CEdittemp = (CEdit*)GetDlgItem(IDC_EDIT6);
	CEdittemp->SetWindowTextW(HcharStringToLPCTSTR(Hitoa(bufferend)));

	//Create mycontrol struct which contains pointer to controller
	mycontrol.detailOutputField = (CListCtrl*)GetDlgItem(IDC_LIST1);
	mycontrol.startPosition = (CEdit*)GetDlgItem(IDC_EDIT5);
	mycontrol.endPosition = (CEdit*)GetDlgItem(IDC_EDIT6);

	//Set running state is 0 (not running) and default input mode is plain text
	isRunning = 0;
	inputMode = PLAIN;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRestore4HDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRestore4HDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRestore4HDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int HisHexString(unsigned char *s)
{
	int n = Hstrlen(s);
	if (n % 2) return 0;
	for (int i = 0; i < n; i++)
	{
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'));
		else return 0;
	}
	return 99;
}

unsigned char HHexToDec(unsigned char t)
{
	if (t >= '0' && t <= '9') return t - '0';
	else if (t >= 'a' && t <= 'f') return t - 'a' + 10;
	else if (t >= 'A' && t <= 'F') return t - 'A' + 10;
	else return 0;
}

unsigned char *HConvertHexStr(unsigned char *s)
{
	int n = Hstrlen(s);
	n = n / 2;
	unsigned char *res = (unsigned char *)malloc(n + 1);
	for (int i = 0; i < n; i++)
	{
		res[i] = HHexToDec(s[i * 2]) * 16 + HHexToDec(s[i * 2 + 1]);
	}
	res[n] = 0;
	return res;
}

/*
void OnBnClickedRadio1()
{
	inputMode = PLAIN;
}

void OnBnClickedRadio2()
{
	inputMode = HEX;
}
*/

void CRestore4HDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	FILE *f = fopen("debug.txt", "w");

	// Get chosen drive from combo box
	CString temp_CString;
	DriveList.GetLBText(DriveList.GetCurSel(), temp_CString);
	CT2A temp_ascii(temp_CString);
	drive = (unsigned char*) temp_ascii.m_psz;
	int n = Hstrlen(drive);
	drive = Hstrndup(drive, n);
	fprintf(f, "Chosen drive: %s\n", drive);

	// Get chosen mode (plain text or hex)
	//CButton* InitButton = (CButton*)this->GetDlgItem(IDC_RADIO1);
	//InitButton->SetCheck(1);

	// Get pattern input
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	patternInput = (unsigned char*) temp_ascii2.m_psz;
	n = Hstrlen(patternInput);
	patternInput = Hstrndup(patternInput, n);
	fprintf(f, "Input pattern: %s\n", patternInput);
	fprintf(f, "Input length:  %d\n", Hstrlen(patternInput));

	// Get input mode: PLAIN or HEX
	inputMode = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
	if (inputMode == IDC_RADIO1) inputMode = PLAIN; else
		if (inputMode == IDC_RADIO2) inputMode = HEX;

	if (inputMode == HEX)
	{
		fprintf(f, "Input mode: HEX\n");
		if (HisHexString(patternInput))
		{
			unsigned char *temp = patternInput;
			patternInput = HConvertHexStr(patternInput);
			fprintf(f, "True input: %s\n", (char*)patternInput);
			n = Hstrlen(patternInput);
			free(temp);
		}
		else {
			fprintf(f, "Not a valid hex string\n");
			fclose(f);
			MessageBox(
				HcharStringToLPCTSTR((unsigned char*)"Input not a valid hexa string"),
				HcharStringToLPCTSTR((unsigned char*)"Error"),
				MB_OK
			);
			return;
		}
	}
	else fprintf(f, "Input mode: PLAIN\n");
	// Scan drive for pattern text
	//std::thread scanthread (scan, (drive, patternInput, &ProcessingBytes));

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	isRunning = 2000;

	HANDLE scanthread;
	MYDATA scanparam;
	scanparam.drive = drive;
	scanparam.patternInput = patternInput;
	scanparam.processedResult = (CEdit*)GetDlgItem(IDC_EDIT2);
	scanparam.scanResult = (CListCtrl*)GetDlgItem(IDC_LIST2);
	scanparam.isRunning = &isRunning;
	
	scanthread = CreateThread(NULL, 0, scan, &scanparam, 0, NULL);
	fclose(f);
}

//cai j ghe vay e :'(
// mai den em ke cho :'(
void CRestore4HDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	isRunning = 0;
}

void CRestore4HDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CListCtrl* listctrl = (CListCtrl*)GetDlgItem(IDC_LIST2);
	CString temp_CString = listctrl->GetItemText(listctrl->GetSelectionMark(), 0);
	CT2A temp_ascii(temp_CString);
	position = Hatoi((unsigned char*) (char*) temp_ascii);
	listctrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	position = Hmax(position - BLOCK_LEN, 0);
	bufferstart = 0;
	nRead = ReadMemory(position, buf, BLOCK_LEN + BLOCK_LEN, drive);
	bufferend = nRead;
	PrintDetail(drive, patternInput, &mycontrol, position);
	*pResult = 0;
}


void CRestore4HDlg::OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	// Take the default processing unless we 
	// set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here.
		// We'll cycle the colors through red, green, and light blue.

		COLORREF crText;

		if ((pLVCD->nmcd.dwItemSpec % 3) == 0)
			crText = RGB(255, 0, 0);
		else if ((pLVCD->nmcd.dwItemSpec % 3) == 1)
			crText = RGB(0, 255, 0);
		else
			crText = RGB(128, 128, 255);

		// Store the color back in the NMLVCUSTOMDRAW struct.
		pLVCD->clrText = crText;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
	*pResult = 0;
}


void CRestore4HDlg::OnBnClickedButton3() // save to file button
{
	// TODO: Add your control notification handler code here
	CString temp_CString;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	unsigned char *filename = (unsigned char*)temp_ascii2.m_psz;
	//unsigned long long startpoint =  0x234567890abcdef;
	//unsigned long long temp = startpoint >> 32;
	//FILE *f = fopen("result.txt", "w");
	//fprintf(f, "%u\n%u\n", Hhighbit(startpoint), Hlowbit(startpoint));
	//fclose(f);
	int result = SaveResult(filename);
	if (result == 0)
	{
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)"Save to file sucessfully!"),
			HcharStringToLPCTSTR((unsigned char*)"Successful"),
			MB_OK
		);
	}
	else if (result == ERROR_FILE_EXISTS) {
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)"Error file exists"),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
	}
	else if (result == ERROR_CANT_ACCESS_FILE) {
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)"Writing error"),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
	}
	else if (result == ERROR_EMPTY) {
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)"File name cannot be empty"),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
	}
}

int HcheckInt(unsigned char *s)
{
	int n = Hstrlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] < '0' || s[i] > '9') return 0;
	return 93;
}

void CRestore4HDlg::OnBnClickedButton4() //add previous 
{
	// TODO: Add your control notification handler code here
	CString temp_CString;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	unsigned char *n_ = (unsigned char*)temp_ascii2.m_psz;
	if (!HcheckInt(n_))
	{
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)NOT_NUMBER_ERROR_MSG),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
		return;
	}
	int n = GetValue(n_);
	if (n > 0)
	{
		AddPrevious(n, position, &mycontrol);
		PrintDetail(NULL, NULL, &mycontrol, position);
	}
}


void CRestore4HDlg::OnBnClickedButton6() // <<
{
	// TODO: Add your control notification handler code here
	AddPrevious(BLOCK_LEN, position, &mycontrol);
	PrintDetail(NULL, NULL, &mycontrol, position);
}


void CRestore4HDlg::OnBnClickedButton7() // >>
{
	// TODO: Add your control notification handler code here
	AddAfter(BLOCK_LEN, position, &mycontrol);
	PrintDetail(NULL, NULL, &mycontrol, position);
}


void CRestore4HDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CString temp_CString;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	unsigned char *n_ = (unsigned char*)temp_ascii2.m_psz;
	if (!HcheckInt(n_))
	{
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)NOT_NUMBER_ERROR_MSG),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
		return;
	}
	int n = GetValue(n_);
	if (n > 0)
	{
		AddAfter(n, position, &mycontrol);
		PrintDetail(NULL, NULL, &mycontrol, position);
	}
}


void CRestore4HDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	CString temp_CString;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	unsigned char *n_ = (unsigned char*)temp_ascii2.m_psz;
	if (!HcheckInt(n_))
	{
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)NOT_NUMBER_ERROR_MSG),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
		return;
	}
	int n = GetValue(n_);
	if (n > 0)
	{
		DeletePrevious(n, position, &mycontrol);
		PrintDetail(NULL, NULL, &mycontrol, position);
	}
}


void CRestore4HDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	CString temp_CString;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->GetWindowTextW(temp_CString);
	CT2A temp_ascii2(temp_CString);
	unsigned char *n_ = (unsigned char*)temp_ascii2.m_psz;
	if (!HcheckInt(n_))
	{
		MessageBox(
			HcharStringToLPCTSTR((unsigned char*)NOT_NUMBER_ERROR_MSG),
			HcharStringToLPCTSTR((unsigned char*)"Error"),
			MB_OK
		);
		return;
	}
	int n = GetValue(n_);
	if (n > 0)
	{
		DeleteAfter(n, position, &mycontrol);
		PrintDetail(NULL, NULL, &mycontrol, position);
	}
}
