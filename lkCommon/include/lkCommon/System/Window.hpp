#pragma once

#include "lkCommon/lkCommon.hpp"
#include "lkCommon/System/KeyCodes.hpp"
#include "lkCommon/System/WindowImage.hpp"

#ifdef WIN32
#define NOMINMAX
#include <Windows.h>
#include <windowsx.h>
#elif defined(__linux__) || defined(__LINUX__)
#include <xcb/xcb.h>
#endif


namespace lkCommon {
namespace System {

class Window
{
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mMouseDownX;
    uint32_t mMouseDownY;
    bool mOpened;
    bool mInvisible;
    bool mKeys[255];
    bool mMouseButtons[3];

#ifdef WIN32
    HINSTANCE mInstance;
    HWND mHWND;
    HDC mHDC;
    std::wstring mClassName;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#elif defined(__linux__) || defined(__LINUX__)
    xcb_window_t mWindow;
    xcb_intern_atom_reply_t* mDeleteReply;
    xcb_gcontext_t mGraphicsContext; // used for setting single pixels on screen

    void ProcessMessages();
#else
#error "Target platform not supported"
#endif

protected:
    LKCOMMON_INLINE bool IsKeyPressed(KeyCode key) const
    {
        return mKeys[static_cast<std::underlying_type<KeyCode>::type>(key)];
    }

    LKCOMMON_INLINE bool IsMouseKeyPressed(int key) const
    {
        return mMouseButtons[key];
    }

    // callbacks
    virtual void OnInit();
    virtual void OnOpen();
    virtual void OnResize(int width, int height);
    virtual void OnClose();
    virtual void OnKeyDown(KeyCode key);
    virtual void OnKeyUp(KeyCode key);
    virtual void OnUpdate(float deltaTime);
    virtual void OnMouseDown(int key);
    virtual void OnMouseMove(int x, int y, int deltaX, int deltaY);
    virtual void OnMouseUp(int key);

public:
    Window();
    ~Window();

    bool Init(const std::string& className = std::string());
    bool Open(int x, int y, int width, int height, const std::string& title);
    bool SetTitle(const std::string& title);
    void SetInvisible(bool invisible);
    bool DisplayImage(uint32_t x, uint32_t y, const WindowImage& image);
    void Update(float deltaTime);
    void MouseButtonDown(int button, int x, int y);
    void MouseButtonUp(int button);
    void MouseMove(int x, int y);
    void Close();

#ifdef WIN32
    LKCOMMON_INLINE HINSTANCE GetInstance() const
    {
        return mInstance;
    }

    LKCOMMON_INLINE HWND GetHandle() const
    {
        return mHWND;
    }
#elif defined(__linux__) || defined(__LINUX__)
    LKCOMMON_INLINE xcb_window_t GetWindow() const
    {
        return mWindow;
    }
#else
#error "Target platform not supported"
#endif

    LKCOMMON_INLINE uint32_t GetWidth() const
    {
        return mWidth;
    }

    LKCOMMON_INLINE uint32_t GetHeight() const
    {
        return mHeight;
    }

    LKCOMMON_INLINE bool IsOpen() const
    {
        return mOpened;
    }
};

} // namespace System
} // namespace lkCommon
