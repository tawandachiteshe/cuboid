
#ifndef D3G_LAYER_H
#define D3G_LAYER_H
typedef union SDL_Event SDL_Event;
//TODO WRAP IN A NAMESPACE
namespace D3G
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(SDL_Event* event) {}
		virtual void OnUnHandledEvent(SDL_Event* event){}
		virtual ~Layer();

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;
	};
}

#endif
