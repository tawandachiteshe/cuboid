#pragma once

#include "Entity.h"

namespace Cuboid
{

	class ScriptableEntity
	{

	public:
		
		virtual ~ScriptableEntity() = default;

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		
	protected:

		virtual void OnCreate() {}
		virtual void OnUpdate(float ts) {}
		virtual void OnDestroy() {}

	private:
		
		Entity m_Entity;
		friend class Scene;
		
		

	};

}