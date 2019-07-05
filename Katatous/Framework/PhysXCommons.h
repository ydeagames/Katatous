#pragma once

template<typename T>
struct px_deleter
{
	void operator()(T* t)
	{
		if (t)
			t->release();
	}
};

template<typename T>
using px_unique_ptr = std::unique_ptr<T, px_deleter<T>>;

template<typename T>
struct px_shared_ptr : public std::shared_ptr<T>
{
	px_shared_ptr(T* _Px)
		: std::shared_ptr(_Px, px_deleter<T>)
	{
	}
};
