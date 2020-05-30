#include <stdio.h>

class info
{
public:
	info(int s) { state = s; };
	static void do_fun(int a, int b, int c);

	void setState()
	{
		m_instance = this;
	}

	void printInfo(int a, int b, int c)
	{
		printf("instance:%d, show %d %d %d\n", state, a, b, c);
	}
private:
	int state = 0;
	static info* m_instance;

};
void info::do_fun(int a, int b, int c)
{
	if (m_instance)
		m_instance->printInfo(a, b, c);
}

info* info::m_instance = nullptr;


typedef void(*FUN)(int a, int b, int c);

class showInfo
{
public:
	showInfo(FUN f)
	{
		fun = f;
	}
	void do_fun(int a, int b, int c)
	{
		fun(a, b, c);
	}

private:
	FUN fun;

};


int main()
{
	info info_a(10);
	info_a.setState();
	showInfo show_a(&info::do_fun);
	show_a.do_fun(20, 21, 22);
	getchar();
}