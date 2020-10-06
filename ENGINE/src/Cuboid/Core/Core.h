

#include <memory>
#include <Cuboid/utils/Logger.h>


#ifndef CUBOID_CORE_H
#define CUBOID_CORE_H


#define CUBOID_ASSERT(x, ...) { if(!(x)) { CUBOID_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CUBOID_CORE_ASSERT(x, ...) { if(!(x)) { CUBOID_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define BIT(x) (1 << x)

#define CUBOID_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Cuboid
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
