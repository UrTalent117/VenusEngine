#pragma once
#include <windows.h>

class Graphics {
private:
    HWND hwnd;
    HDC hdc;
    int width;
    int height;

public:
    Graphics(int w, int h) : width(w), height(h) {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "VenusEngineWindow";
        RegisterClass(&wc);

        hwnd = CreateWindow(
            "VenusEngineWindow",
            "Venus Engine",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            w,
            h,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
        );

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        hdc = GetDC(hwnd);
        clear();
    }

    ~Graphics() {
        ReleaseDC(hwnd, hdc);
        DestroyWindow(hwnd);
    }

    void clear() {
        RECT rect = {0, 0, width, height};
        FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    }

    void drawLine(int x1, int y1, int x2, int y2) {
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }

    void drawCircle(int x, int y, int radius) {
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(pen);
        DeleteObject(brush);
    }

    void present() {
    }

    bool processEvents() {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return true;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
