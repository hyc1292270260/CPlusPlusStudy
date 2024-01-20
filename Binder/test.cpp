#include <iostream>
#include "Binder.hpp"

class BindTest
{
public:
	int p1 = 1;
	bool p2 = false;
	std::string p3 = "p33333333";

	std::string test1(void* params)
	{
		std::cout << "test1" << std::endl;
		return "test1";
	}
	static std::string test2(void* params)
	{
		std::cout << "test2" << std::endl;
		return "test2";
	}
};

int main()
{
	Binder<BindTest> binder;
	BindTest t1;
	binder.bindVar("p1", offsetof(BindTest, p1));
	binder.bindVar("p2", offsetof(BindTest, p2));
	binder.bindVar("p3", offsetof(BindTest, p3));

	std::cout << *(binder.findVar<int>(&t1, "p1")) << std::endl;
	std::cout << *(binder.findVar<bool>(&t1, "p2")) << std::endl;
	std::cout << *(binder.findVar<string>(&t1, "p3")) << std::endl;

	binder.bindFunc("test1", &BindTest::test1);
	binder.bindStaticFunc("test2", BindTest::test2);
	binder.callFunc(&t1, "test1", nullptr);
	binder.callStaticFunc("test2", nullptr);

	return 0;
}



