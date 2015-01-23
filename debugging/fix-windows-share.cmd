reg add HKLM\SYSTEM\CurrentControlSet\Services\LanmanServer\Parameters /v Size /t REG_DWORD /d 3 /f
sc stop  LanmanServer
sc start LanmanServer
