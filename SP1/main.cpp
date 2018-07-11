#define  _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <Windows.h>
#include <clocale>
#include <iostream>
#include <string>
#include <lm.h>
#pragma comment(lib, "netapi32.lib")
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")


std::string bioss = "";
std::string  or_usname = "Alexandra";
std::string or_bioss = "ACRSYS - 0 V1.07 INSYDE Corp. - 55340107 ";
                        

LPSTR GetSystemBiosVersion()
{
	HKEY hKey;
	LONG Res1, Res2;
	DWORD cData = 255;
	TCHAR SystemBiosVersion[255] = { '\0' };
	Res1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", NULL, KEY_QUERY_VALUE, &hKey);
	if (Res1 == ERROR_SUCCESS)
	{
		Res2 = RegQueryValueEx(hKey, "SystemBiosVersion", NULL, NULL,(LPBYTE)SystemBiosVersion, &cData);
		if (Res2 == ERROR_SUCCESS)
		{
			for (const char* p = SystemBiosVersion; *p; p += strlen(p) + 1)
			{
			//	printf("%s\n", p);
				bioss += p;
				bioss += " ";
			}

			return SystemBiosVersion;
		}
		else
		{
			MessageBox(NULL, "RegQueryValueEx: SystemBiosVesion", "ERROR", MB_OK);
			return NULL;
		}
	}
	else
	{
		MessageBox(NULL, "RegOpenKeyEx: SystemBiosVersion", "ERROR", MB_OK);
		return NULL;
	}
	RegCloseKey(hKey);
}



int main(void)
{
	
	setlocale(LC_CTYPE, "rus");
	char buffer[UNLEN + 1];
	DWORD size;
	size = sizeof(buffer);
	GetUserName(buffer, &size);
	GetSystemBiosVersion();
	if ((or_usname.compare(buffer) == 0) && (or_bioss.compare(bioss) == 0) )
	{
		printf("My Name is %s\n", buffer);
		std::cout << bioss << std::endl;
	}
	else {
		exit(EXIT_FAILURE);
	}
	getchar();
	return 0;
}



