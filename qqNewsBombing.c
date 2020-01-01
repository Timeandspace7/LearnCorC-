//main.c    环境：VS2015
// 来源：https://mp.weixin.qq.com/s?__biz=MzU5NjI2NzM5OA==&mid=2247484062&idx=1&sn=8c835fead8e731b195efaa7cb379e8fa&chksm=fe641a77c9139361f00a5b093efad4abb5901c838448ac6a7d5f8f78f7b7b34a4fa372c40de8&mpshare=1&scene=23&srcid=&sharer_sharetime=1577878462727&sharer_shareid=092d2b28bf48376ec50b158745d7741a#rd
// 来自公众号：编程学习基地
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam);
int main()
{
  int times;  //轰炸次数
  HWND hWnd = FindWindow(L"TXGuiFoundation", L"QQ");  //TXGuiFoundation QQ类名
  if (!hWnd)  //没有找到QQ
  {
    printf("没有找到轰炸对象...\n");
    exit(0);
  }
  ShowWindow(hWnd, SW_SHOW);  //显示窗口
  do
  {
    printf("请输入要轰炸的好友次数 >");
    scanf("%d", &times);
    //发送
    if (MessageBox(0, L"是否进行轰炸", L"提示", MB_YESNO) == IDYES)
    {
      for (int i = 0; i < times; i++)
        EnumWindows(EnumWindowProc, NULL);  //枚举屏幕上所有的顶级窗口，调用EnumWindowProc函数
    }
  } while (MessageBox(0, L"是否继续轰炸", L"提示", MB_YESNO) == IDYES);
  system("pause");
  return 0;
}

BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam)
{
  //判断是否是QQ聊天窗口 ，是 就轰炸
  char strClassName[MAXBYTE] = { 0 };
  GetClassNameA(hWnd, strClassName, MAXBYTE);      //检索指定窗口所属的类的名称
  if (0 == strcmp("TXGuiFoundation", strClassName))  //判断是否是QQ聊天窗口
  {
    ::SendMessage(hWnd, WM_PASTE, 0, 0);      //粘贴
    ::SendMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0);  //发送   VK_RETURN：虚拟键值回车
  }
  return true;
}
