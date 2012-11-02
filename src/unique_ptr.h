#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

template<typename T> struct Deleter {
	void operator()(T *p)
	{
		delete p;
	}
};

#define unique_ptr(C) boost::interprocess::unique_ptr<C, Deleter<C> >

#endif // UNIQUE_PTR_H
