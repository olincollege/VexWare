#include <windows.h>

const char g_szClassName[] = "unendingWindowClass";

void happyDialog() {
    MessageBox(NULL, "I'm glad you're not leaving!", "Happy Friend Dialog",
    MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
    return;
}
int ynDialog(LPCSTR str_msg) {
    return MessageBox(NULL, str_msg, "Abandon Friend Dialog",
    MB_ICONSTOP | MB_YESNO | MB_SYSTEMMODAL);
}
int storyDialog(LPCSTR str_msg) {
    return 0;
}
void storyHandler() {

    return;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // case WM_KILLFOCUS:
        //     MessageBox(NULL, "Hey! Where are you going?", "Lost Focus Dialog",
        //     MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
        // break;
        case WM_CLOSE:
            // dont let them close me ;-;
           int first = ynDialog("Do you really want to quit?");
            if (first == IDYES) {
                int second = ynDialog("You're just going to abandon me?");
                if (second == IDYES) {
                    int third = ynDialog("Seriously!?\nYou really want to quit that bad?");
                    if (third == IDYES) {
                        int threat = ynDialog("If you quit, I'm dropping you in the woods.\nStill want to quit?");
                        if (threat == IDYES) {
                            storyHandler();
                        } else {
                            happyDialog();
                        }
                    } else {
                        happyDialog();
                    }
                } else {
                    happyDialog();
                }
            } else {
                happyDialog();
            }
            // DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX mc;
    HWND hwnd;
    MSG Msg;
    // HICON icon = (HICON)LoadImageA(NULL, "./pink.ico", IMAGE_ICON, 128, 128, LR_LOADFROMFILE);
    // if (!icon) {
    //     MessageBox(NULL, "Couldn't load our icon!", "Oh no!",
    //         MB_ICONEXCLAMATION | MB_OK);
    //     return 0;
    // }
    // register the main class
    mc.cbSize        = sizeof(WNDCLASSEX);
    mc.style         = 0;
    mc.lpfnWndProc   = WndProc;
    mc.cbClsExtra    = 0;
    mc.cbWndExtra    = 0;
    mc.hInstance     = hInstance;

    mc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    mc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    mc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    mc.lpszMenuName  = NULL;
    mc.lpszClassName = g_szClassName;
    mc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&mc))
    {
        MessageBox(NULL, "Couldn't register the main class!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // create the main window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Your New Best Friend",
        WS_TILEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 480, 420,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Couldn't create the main window!", "Error!",
            MB_ICONERROR | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // message loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}