
// injectdllDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "injectdll.h"
#include "injectdllDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <TlHelp32.h>

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


// CinjectdllDlg 对话框



CinjectdllDlg::CinjectdllDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INJECTDLL_DIALOG, pParent)
	, dllpath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CinjectdllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, dllpath);
	DDX_Control(pDX, IDC_COMBO1, combo1);
}

BEGIN_MESSAGE_MAP(CinjectdllDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	
	ON_BN_CLICKED(IDC_BUTTON5, &CinjectdllDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT2, &CinjectdllDlg::OnEnChangeEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CinjectdllDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CinjectdllDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CinjectdllDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CinjectdllDlg 消息处理程序

BOOL CinjectdllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 显示当前所有进程信息
	CString pid;//进程信息
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//TH32CS_SNAPPROCESS： 快照当前系统中所有进程；
	if (hProcessSnap == FALSE)
	{
		printf("CreateToolhelp32Snapshot error");

	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);//初始化dwSize

	BOOL bRet = Process32First(hProcessSnap, &pe32);//此函数检索有关系统快照中遇到的第一个进程的信息。
	while (bRet)
	{
		pid.Format(_T("[PID]:%d--%ws"), pe32.th32ProcessID, pe32.szExeFile);		
		combo1.AddString(pid);//添加到下拉控件combo1中
		bRet = Process32Next(hProcessSnap, &pe32);//获取下一进程的信息，并送给bRect。
	}
	CloseHandle(hProcessSnap);

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CinjectdllDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CinjectdllDlg::OnPaint()
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
HCURSOR CinjectdllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CinjectdllDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}



void CinjectdllDlg::OnBnClickedButton5()
{
	// TODO: 文件选择功能
	CString filename;
	CFileDialog  dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.dll)|*.dll|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal())
	{
		filename = dlgFile.GetPathName();
	}
	SetDlgItemText(IDC_EDIT2, filename);//在编辑控件中显示选择的dll的文件路径
	
}


void CinjectdllDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CinjectdllDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL InjectDll(DWORD dwPID, LPCTSTR szDllPath)
{
	HANDLE hProcess = NULL, hThread = NULL;
	HMODULE hMod = NULL;
	LPVOID pRemoteBuf = NULL;
	DWORD dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE pThreadProc;

	// #1. 使用dwPID获取目标进程句柄.
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)))
	{
		
		return FALSE;
	}

	// #2.在目标进程内存中分配 szDllName 大小的内存.
	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);
	if (!pRemoteBuf)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
	// #3. 将dll路径写入分配的内存
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllPath, dwBufSize, NULL);

	// #4. 获取LoadLibraryW()API的地址.
	hMod = GetModuleHandle(L"kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");

	// #5. 在进程中运行线程
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
	if (!hThread)
	{
		VirtualFreeEx(hProcess, pRemoteBuf, sizeof(szDllPath), MEM_DECOMMIT);
		CloseHandle(hProcess);
		return FALSE;
	}
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}

void CinjectdllDlg::OnBnClickedButton2()
{
	// TODO: 注入dll
	CString strpid,dllname;
	int id,pos;
	HMODULE  hDll = NULL;
	DWORD dwpid;

	id = combo1.GetCurSel();
	combo1.GetLBText(id, strpid);
	//获取显示的进程信息中的进程值
	pos = strpid.Find(_T("-"));
	strpid = strpid.Left(strpid.GetLength() - pos - 3);
	int index = strpid.Find(_T(":"));
	strpid = strpid.Right(strpid.GetLength() - index - 1);
	//转换为dword类型
	dwpid = _ttoi(strpid);
	//获取dll路径值
	GetDlgItemText(IDC_EDIT2, dllname);
	//转换为LPCTSTR类型
	LPCTSTR dllpath = (LPCTSTR)dllname;

	if (!InjectDll(dwpid, dllpath))//调用InjectDll方法
	{
		MessageBoxA(NULL, ("注入DLL失败！"), ("注入失败"), MB_OK);
		
	}
	else {
		MessageBoxA(NULL, ("注入DLL成功！"), ("注入成功"), MB_OK);
	}

}

BOOL UnjectDll(DWORD dwPID, LPCTSTR szDllPath) {

	LPTHREAD_START_ROUTINE lpFreeLibAddr;
	BOOL bmore = FALSE,bfound = FALSE;
	HANDLE hSnapshot;
	MODULEENTRY32 me = { sizeof(me) };//MODULEENTRY32结构体

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);//获取进程加载的dll的信息
	//modBaseAddr是相应dll被加载的地址
	//szModule是dll的名称
	bmore = Module32First(hSnapshot, &me);
	for (; bmore; bmore = Module32Next(hSnapshot, &me)) {//循环
		if (!_tcsicmp((LPCTSTR)me.szModule, szDllPath) | !_tcsicmp((LPCTSTR)me.szExePath, szDllPath)) {//比较要卸载的dll的名字
			bfound = TRUE;
			break;
		}
	}
	if (!bfound){
		CloseHandle(hSnapshot);
		return FALSE;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);//获取目标进程的句柄
	if (!hProcess)
	{
		return FALSE;
	}

	HMODULE hModule = GetModuleHandle(_T("Kernel32.dll"));
	lpFreeLibAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "FreeLibraryAndExitThread");//获取FreeLibraryAndExitThread的地址

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, lpFreeLibAddr, me.modBaseAddr, 0, 0);//运行线程

	if (!hThread)
	{
		CloseHandle(hProcess);
		return FALSE;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}

void CinjectdllDlg::OnBnClickedButton3()
{
	// TODO: 卸载dll
	CString strpid, dllname;
	int id, pos;
	HMODULE  hDll = NULL;
	DWORD dwpid;

	id = combo1.GetCurSel();
	combo1.GetLBText(id, strpid);
	pos = strpid.Find(_T("-"));
	strpid = strpid.Left(strpid.GetLength() - pos - 3);
	int index = strpid.Find(_T(":"));
	strpid = strpid.Right(strpid.GetLength() - index - 1);
	dwpid = _ttoi(strpid);
	GetDlgItemText(IDC_EDIT2, dllname);
	LPCTSTR dllpath = (LPCTSTR)dllname;
	if (!UnjectDll(dwpid, dllpath))
	{
		MessageBoxA(NULL, ("卸载DLL失败！"), ("卸载失败"), MB_OK);

	}
	else {
		MessageBoxA(NULL, ("卸载DLL成功！"), ("卸载成功"), MB_OK);
	}
}
