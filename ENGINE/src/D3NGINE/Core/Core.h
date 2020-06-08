

#include <memory>
#include <D3NGINE/utils/Logger.h>


#ifndef D3G_CORE_H
#define D3G_CORE_H


#define D3G_ASSERT(x, ...) { if(!(x)) { D3G_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define D3G_CORE_ASSERT(x, ...) { if(!(x)) { D3G_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

namespace D3G
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}
#endif
