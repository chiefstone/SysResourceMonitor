#include <QtWidgets/QApplication>
#include <windows.h>
#include "SysResourceMonitor.h"
#include "SRMError.h"
#include <QMessageBox>
#include <QDir>

// 判断程序之间的互斥, 只能打开一个软件
bool checkUnique()
{
	std::wstring sTitle = L"提示";
	std::wstring sMessage = L"SysResourceMonitor 已经在运行中";
	std::wstring sMutex = L"VS_SysResourceMonitor";
	HANDLE hMutex = CreateMutex(NULL, TRUE, sMutex.c_str());
	if (!hMutex){
		MessageBox(NULL, sMessage.c_str(), sTitle.c_str(), S_OK);
		return false;
	}
		
	if (GetLastError() == ERROR_ALREADY_EXISTS){
		MessageBox(NULL, sMessage.c_str(), sTitle.c_str(), S_OK);
		CloseHandle(hMutex);
		return false;
	};

	return true;
}

int main(int argc, char* argv[])
{
	if (!checkUnique()){
		return 0;
	}

	QApplication a(argc, argv);
	QDir::setCurrent(qApp->applicationDirPath());
	try{
		SysResourceMonitor w;
		w.setWindowIcon(QIcon(":/Images/SysResourceMonitor.png"));
		w.hide();
		w.doWork();
		return a.exec();
	}
	catch (SRMError & e){
		QMessageBox::critical(nullptr, QString::fromStdWString(L"运行错误"), QString::fromStdWString(L"错误码:%1").arg(e.errorCode()), QMessageBox::Ok);
		return -1;
	}
}