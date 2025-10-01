#pragma once

namespace Core
{

	class Scene
	{
	public:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnImGuiRender() = 0;
	};

}