reg add HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Run /v SysResourceMonitorAutoRun /t REG_SZ /d "\"%~dp0SysResourceMonitor.exe\" AutoRun" /f
