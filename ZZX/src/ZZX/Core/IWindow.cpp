#include "zzxpch.h"
#include "IWindow.h"

#ifdef ZZX_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsSystemWindow.h"
#endif

namespace ZZX
{
	Scope<IWindow> IWindow::Create(const WindowProperties& props)
	{
#ifdef ZZX_PLATFORM_WINDOWS
		return CreateScope<WindowsSystemWindow>(props);
#else 
		ZZX_CORE_ASSERT(false, "Unknown plaftform!");
		return nullptr;
#endif
	}
}
