#pragma once

#include <memory>

template<typename T>
struct AutoZero : public T
{
	AutoZero() 
	{
		memset(this, 0, sizeof(T));
		dwSize = sizeof(T);
	}
	

};


template<typename T>
inline void SafeRelease(T& iface) 
{
	if(iface)
	{
		iface->Release();
		//iface = NULL;
	}
}