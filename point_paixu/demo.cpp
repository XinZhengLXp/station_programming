#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
void func(const char* str)
{
    char st[20] = { 0 };
    const char* ptr = str;
    int x = 0;
    while (*ptr != '\0') {
        char currentChar = *ptr; // 使用解引用操作符获取当前字符
        st[x] = currentChar;
        ptr++; // 指针指向下一个字符
        x++;
    }

    char* next_token;
    char* token = strtok_s(st, "-", &next_token);
    while (token != NULL) {
        const char* ptr = token;
        char st[10] = {0};
        int x = 0;
        while (*ptr != '\0')
        {
           char currentChar = *ptr; // 使用解引用操作符获取当前字符
            st[x] = currentChar;
            ptr++;
            x++;
        }
        cout << st << endl;
        token = strtok_s(NULL, "-", &next_token);
    }
}
int main()
{	
	const char* str = "524-369-777"; // 声明一个字符串指针并初始化为字符串常量
	func(str);
	system("pause");
	return 0;
}
