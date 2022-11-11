#include "hdk/hdk.hpp"
#include "hdk/debug.hpp"
#include "hdk/memory/clone.hpp"

class A1 : public hdk::unique_cloneable<A1>
{
public:
	virtual int foo() const = 0;
};

class A2 : public A1
{
public:
	A2() = default;
	virtual int foo() const final{return 1;}
	HDK_COPY_UNIQUE_CLONEABLE(A1);
};

void copy_unique_clone()
{
	A2 x;
	auto a1_clone = x.unique_clone();
	hdk::assert(x.foo() == a1_clone->foo());
}

int main()
{
	hdk::initialise();
	copy_unique_clone();
	hdk::terminate();
}
