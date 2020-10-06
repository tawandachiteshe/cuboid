#include <Cuboid/Core/Cuboid.h>
#include <Cuboid/Core/EntryPoint.h>
#include "CuboidEditor.h"

namespace Cuboid
{

	class CuboidEditorApp : public Application
	{
	public:

		CuboidEditorApp() :
			Application("Cuboid-Editor")
		{
			PushLayer(new CuboidEditor("CuboidEditor Layer"));
		}

	};



	Application* CreateApplication()
	{
		return new CuboidEditorApp();
	}

}