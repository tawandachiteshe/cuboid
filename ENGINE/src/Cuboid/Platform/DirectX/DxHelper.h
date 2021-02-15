#pragma once

#include <memory>

namespace Cuboid
{
	template<typename T>
	struct AutoZero : public T
	{
		AutoZero()
		{
			memset(this, 0, sizeof(T));
			uint32_t dwSize = sizeof(T);
		}


	};


	template<typename T>
	inline void SafeRelease(T& iface)
	{
		if (iface)
		{
			iface->Release();
		}
	}

}