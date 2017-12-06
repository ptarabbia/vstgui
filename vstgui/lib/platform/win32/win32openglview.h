// This file is part of VSTGUI. It is subject to the license terms 
// in the LICENSE file found in the top-level directory of this
// distribution and at http://github.com/steinbergmedia/vstgui/LICENSE

#ifndef __win32openglview__
#define __win32openglview__

#include "../iplatformopenglview.h"

#if VSTGUI_OPENGL_SUPPORT
#if WINDOWS

#include <windows.h>

namespace VSTGUI {
class Win32Frame;

//-----------------------------------------------------------------------------
class Win32OpenGLView : public IPlatformOpenGLView
{
public:
	Win32OpenGLView (Win32Frame* win32Frame);
	~Win32OpenGLView () noexcept;

	bool init (IOpenGLView* view, PixelFormat* pixelFormat = nullptr) override;
	void remove () override;

	void invalidRect (const CRect& rect) override;
	void viewSizeChanged (const CRect& visibleSize) override; ///< visibleSize is cframe relative

	bool makeContextCurrent () override;
	bool lockContext () override;
	bool unlockContext () override;

	void swapBuffers () override;
	double getScaleFactor () override;
protected:
	static void initWindowClass ();
	static void destroyWindowClass ();
	static LONG_PTR WINAPI WindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool createWindow ();
	bool setupPixelFormt ();

	Win32Frame* win32Frame;
	IOpenGLView* view;
	HWND windowHandle;
	PixelFormat pixelFormat;

	HDC deviceContext;
	HGLRC openGLContext;
	CRITICAL_SECTION lock;
	static int32_t instanceCount;
};

} // namespace

#endif // WINDOWS
#endif // VSTGUI_OPENGL_SUPPORT

#endif // __win32openglview__
