#include "zzxpch.h"
#include "IWindow.h"

#ifdef ZE_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsSystemWindow.h"
#endif

namespace ZE
{
	Scope<IWindow> IWindow::Create(const WindowProperties& props)
	{
#ifdef ZE_PLATFORM_WINDOWS
		return CreateScope<WindowsSystemWindow>(props);
#else 
		ZE_CORE_ASSERT(false, "Unknown plaftform!");
		return nullptr;
#endif
	}
}
