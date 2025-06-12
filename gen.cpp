#include <windows.h>
#include <time.h>
 
int main(int argc, _TCHAR* argv[])
{
    char path[MAX_PATH];
    printf("请输入一个文件的路径:");
    scanf("%s", path, MAX_PATH);
 
    // 打开这个文件，并将文件内容读取到内存中。
    HANDLE  hFile = INVALID_HANDLE_VALUE;
    hFile = CreateFileA(path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("无法打开文件");
        return 0;
    }
 
    // 获取文件的字节数
    DWORD dwFileSize = GetFileSize(hFile, NULL);
 
    // 申请对应大小的缓存区来保存文件内容
    BYTE  *pFileData = new BYTE[dwFileSize];
 
    // 将文件的全部内容读取到缓冲区
    DWORD  dwReadSize = 0;
    ReadFile(hFile, pFileData, dwFileSize, &dwReadSize, NULL);
    if (dwReadSize != dwFileSize) {
        printf("文件读取失败\n");
        // CloseHandle( hFile );
        // delete[ ] pFileData;
        return 0;
    }
 
    // PE文件所有的结构体都是以 IMAGE_ 开头
    //PIMAGE_DOS_HEADER => IMAGE_DOS_HEADER*
    IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)pFileData;
 
    // 判断第一个字段是否MZ
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        printf("不是一个有效的DOS头\n");
        return 0;
    }
 
    // 判断是否是有效的NT头
    IMAGE_NT_HEADERS* pNtHeader =
        (IMAGE_NT_HEADERS*)(pDosHeader->e_lfanew + (DWORD)pDosHeader);
 
    if (pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
        printf("不是一个有效的NT头\n");
        return 0;
    }
 
    printf("文件是一个有效的PE程序\n");
 
 
 
 
    //显示文件头
    IMAGE_FILE_HEADER *pFileHeader = &pNtHeader->FileHeader;
 
    //gmtime_s显示文件创建时间，年数需要加上1900，月数要加上1，小时要加上8
    struct tm test_gmtime_s;
    errno_t err = gmtime_s(&test_gmtime_s, (time_t *)&pFileHeader->TimeDateStamp);
    printf("TimeDateStamp: %d年 %d月 %d日 ", test_gmtime_s.tm_year + 1900, test_gmtime_s.tm_mon + 1, test_gmtime_s.tm_mday);
    printf("周%d %02d时 %02d分 %02d秒\n", test_gmtime_s.tm_wday, test_gmtime_s.tm_hour + 8, test_gmtime_s.tm_min, test_gmtime_s.tm_sec);
 
 
    //strftime格式化时间显示
    struct tm p;
    errno_t err1;
    err1 = gmtime_s(&p,(time_t*)&pFileHeader->TimeDateStamp);
    char s[100];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &p);
    printf("%d: %s\n", (int)pFileHeader->TimeDateStamp, s);
 
    //原来的数据
    printf("TimeDateStamp:      0x%08d\n", pFileHeader->TimeDateStamp);
 
 
    system("pause");
    return 0;
}
 