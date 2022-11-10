
namespace hdk
{
	template<std::size_t S>
	stack_allocator<S>::stack_allocator():
	linear_allocator(hdk::memblk{.ptr = this->data, .size = S}){}
}
