// MathAttackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MathAttack.h"
#include "MathAttackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CMathAttackDlg::CMathAttackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMathAttackDlg::IDD, pParent)
	, m_pogodeni(0)
	, m_sobiranje(FALSE)
	, m_odzemanje(FALSE)
	, m_mnozenje(FALSE)
	, m_delenje(FALSE)
	, m_rez(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathAttackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, txt_correct, m_pogodeni);
	DDX_Check(pDX, chk_addition, m_sobiranje);
	DDX_Check(pDX, chk_subtraction, m_odzemanje);
	DDX_Check(pDX, chk_multiplication, m_mnozenje);
	DDX_Check(pDX, chk_division, m_delenje);
	DDX_Text(pDX, txt_result, m_rez);
}

BEGIN_MESSAGE_MAP(CMathAttackDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(btn_start, &CMathAttackDlg::start)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CMathAttackDlg::OnBnClickedCancel)
	ON_BN_CLICKED(btn_speed_inc, &CMathAttackDlg::incSpeed)
	ON_BN_CLICKED(btn_speed_dec, &CMathAttackDlg::decSpeed)
	ON_BN_CLICKED(chk_addition, &CMathAttackDlg::updateOperations)
	ON_BN_CLICKED(chk_subtraction, &CMathAttackDlg::updateOperations)
	ON_BN_CLICKED(chk_multiplication, &CMathAttackDlg::updateOperations)
	ON_BN_CLICKED(chk_division, &CMathAttackDlg::updateOperations)
	ON_BN_CLICKED(btn_freq_inc, &CMathAttackDlg::incFreq)
	ON_BN_CLICKED(btn_freq_dec, &CMathAttackDlg::decFreq)
//	ON_WM_KEYUP()
END_MESSAGE_MAP()


// CMathAttackDlg message handlers

BOOL CMathAttackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	srand(time(NULL));
	for ( int i = 0 ; i < 5 ; ++i ) postoi[i] = false;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(true);
	m_sobiranje = true;
	m_odzemanje = true;
	m_mnozenje = true;
	m_delenje = true;
	UpdateData(false);
	brzina = 2;
	vreme = 1500;
	izlez = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMathAttackDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMathAttackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMathAttackDlg::start()
{
	SetTimer(IDD_TIMER,30,NULL);
	SetTimer(IDD_TIMER_DODAJ,500,NULL);
	GetDlgItem(txt_result)->SetFocus();
}

BOOL CMathAttackDlg::PreTranslateMessage(MSG* pMsg)
{
	// ENTER key
	if ((pMsg->message == WM_KEYDOWN) &&
		(pMsg->wParam == VK_RETURN))
	{
		// Enter key was hit -> do whatever you want
		OnBnClickedButton4();
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMathAttackDlg::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == IDD_TIMER ) {
		for ( int i = 0 ; i < 5 ; i++ ) {
			if ( postoi[i] ) {
				y[i] += brzina;
				if ( y[i] > 430 ) {
					postoi[i] = false;
				}
			}
		}
		CDC* l_DC_pics;

		l_DC_pics = GetDlgItem(Canvas)->GetDC();
		CRect rc;
		GetDlgItem(Canvas)->GetClientRect(rc);

		CDC dcMem;//Virtual screen
		dcMem.CreateCompatibleDC(l_DC_pics);
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(l_DC_pics, rc.Width(), rc.Height());
		dcMem.SelectObject(&bmp);

		CBrush background_brush(RGB(210, 210, 210));
		dcMem.SelectObject(&background_brush);
		dcMem.Rectangle(rc);
		CBrush brush(RGB(120, 120, 240));
		dcMem.SelectObject(&brush);
		CPen pen(1, 1, RGB(20, 20, 240));
		LOGFONT logFont;
		logFont.lfHeight = 20;
		logFont.lfWidth = 0;
		logFont.lfEscapement = 0;
		logFont.lfOrientation = 0;
		logFont.lfWeight = FW_NORMAL;
		logFont.lfItalic = 0;
		logFont.lfUnderline = 0;
		logFont.lfStrikeOut = 0;
		logFont.lfCharSet = ANSI_CHARSET;
		logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logFont.lfQuality = PROOF_QUALITY;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		strcpy((LPSTR)&logFont.lfFaceName, "Times New Roman");
		CFont font;
		font.CreateFontIndirect(&logFont);
		dcMem.SelectObject(&font);
		for (int i = 0; i < 5; i++) {
			if (postoi[i]) {
				char op = '+';
				if (operacija[i] == 1) op = '-';
				if (operacija[i] == 2) op = '*';
				if (operacija[i] == 3) op = '/';
				CString all;
				all.Format(_T("%d%c%d"), broj1[i], op, broj2[i]);
				CRect rect(x[i], y[i] + 20, x[i] + 60, y[i] + 50);
				dcMem.Ellipse(x[i], y[i], x[i] + 60, y[i] + 60);
				dcMem.SetBkMode(NULL);
				dcMem.DrawText(all, all.GetLength(), rect, DT_CENTER);
			}
		}
		l_DC_pics->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
	}	
	if (nIDEvent == IDD_TIMER_DODAJ) {

		int indeks = -1;
		int i = 0;
		while (true) {
			if (!postoi[i]) break;
			++i;
			if (i >= 5) return;
		}
		for (int k = 0; k < 20; ++k) {
			int temp = rand() % 5;
			if (!postoi[temp]) {
				indeks = temp;
				break;
			}
		}
		if ( indeks != -1 ) {
			postoi[indeks] = true;
			
			int op = rand()%4;
			UpdateData(true);
			int stop = 0;
			while ( true ) {
				++stop;
				if ( op == 0 && m_sobiranje ) break;
				if ( op == 1 && m_odzemanje ) break;
				if ( op == 2 && m_mnozenje ) break;
				if ( op == 3 && m_delenje ) break;
				int op = rand()%4;
				if ( stop > 100 ) break;
			}
			if ( stop > 100 ) {
				if ( m_sobiranje ) op = 0;
				else if ( m_odzemanje ) op = 1;
				else if ( m_mnozenje ) op = 2;
				else if ( m_delenje ) op = 3;
			}
			int p1 = rand() % 20 + 1;
			int p2 = rand() % 20 + 1;
			int r = p1+p2;
			if ( op == 1 ) {
				p1 = (rand() % 20 ) + 15;
				p2 = rand() % 15 + 1;
				r = p1-p2;
			}
			if ( op == 2 ) {
				p1 = rand() % 10 + 1;
				p2 = rand() % 10 + 1;
				r = p1*p2;
			}
			if ( op == 3 ) {
				r = rand() % 15;
				p2 = rand() % 10 + 1;
				p1 = r*p2;
			}
			broj1[indeks] = p1;
			broj2[indeks] = p2;
			rezultat[indeks] = r;
			operacija[indeks] = op;
			y[indeks] = -20;
			x[indeks] = indeks*80+50;
			postoi[indeks] = true;
			KillTimer(IDD_TIMER_DODAJ);
			int delay = vreme / 2 + (rand() % vreme);
			SetTimer(IDD_TIMER_DODAJ, delay, NULL);
		}
//		int nNumber = _tstoi(tmp.GetBuffer(tmp.GetLength())); 
	}
	//CDialog::OnTimer(nIDEvent);
}

void CMathAttackDlg::OnBnClickedCancel()
{
	izlez = true;
	OnCancel();
	izlez = false;
}

void CMathAttackDlg::OnOK()
{
	if ( izlez )
		CDialog::OnOK();
}

void CMathAttackDlg::OnCancel()
{
	if ( izlez ) 
		CDialog::OnCancel();
}

void CMathAttackDlg::OnBnClickedButton4()
{
	UpdateData(true);
	bool t = false;
	int rezultat1 = _tstoi(m_rez.GetBuffer(m_rez.GetLength())); 
	for ( int i = 0 ; i < 5 ; ++i ) {
		if ( postoi[i] ) {
			if ( rezultat1 == rezultat[i] ) {
				t = true;
				postoi[i] = false;
			}
		}
	}
	if ( t ) ++m_pogodeni;
	m_rez = _T("");
	UpdateData(false);
}

void CMathAttackDlg::incSpeed()
{
	if (brzina < 5) ++brzina;
	GetDlgItem(txt_result)->SetFocus();
}

void CMathAttackDlg::decSpeed()
{
	if (brzina > 1) --brzina;
	GetDlgItem(txt_result)->SetFocus();
}

void CMathAttackDlg::updateOperations()
{
	UpdateData(true);
	if (!(m_odzemanje || m_mnozenje || m_delenje)) {
		m_sobiranje = true;
	}
	UpdateData(false);
	GetDlgItem(txt_result)->SetFocus();
}


void CMathAttackDlg::incFreq()
{
	if ( vreme < 7000 )  {
		vreme += 500;
	}
	GetDlgItem(txt_result)->SetFocus();
}


void CMathAttackDlg::decFreq()
{
	if (vreme > 500)  {
		vreme -= 500;
	}
	GetDlgItem(txt_result)->SetFocus();
}




