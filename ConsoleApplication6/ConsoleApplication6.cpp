// ConsoleApplication6.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include <functional>
using namespace std;
typedef void(*fun)(int);
void Fun12(int i)
{
	printf("Fun1 Run");
}
class abc{
public:
	void Fun1(int i)
	{
		printf("Fun1 Run"+i);
	}
	function<void(int)> f2 = Fun12;
	void Fun2()
	{
		printf("Fun2 Run\n");
	}
};
int main()
{
	abc a;
	function<void(int)> f1 = Fun12;
	Fun12(3);
	a.f2(3);
	a.Fun2();
	//p = a.Fun1; //两者类型匹配。
	//p(); //
	//p = a.Fun2;
	//(*p)();//这两种p的表示方法是等价的
	system("pause");
	return 0;
}
