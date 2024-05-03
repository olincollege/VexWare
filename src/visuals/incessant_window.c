#include <windows.h>

const char g_szClassName[] = "unendingWindowClass";

void happyDialog() {
    /**
     * Creates a messagebox to display text to the user.
     */
    MessageBox(NULL, "I'm glad you're not leaving!", "Happy Friend Dialog",
    MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
    return;
}
int ynDialog(LPCSTR str_msg) {
    /**
     * Creates a messagebox to display text to the user.
     * @param str_msg pointer to a const string message to be displayed
     * @return the user's choice as an integer
     */
    return MessageBox(NULL, str_msg, "Abandon Friend Dialog",
    MB_ICONSTOP | MB_YESNO | MB_SYSTEMMODAL);
}
int storyDialog(LPCSTR str_msg) {
    /**
     * Creates a messagebox to display text to the user.
     * @param str_msg pointer to a const string message to be displayed
     * @return the user's choice as an integer
     */
    return MessageBox(NULL, str_msg, "Story Dialog",
    MB_ICONSTOP | MB_CANCELTRYCONTINUE | MB_SYSTEMMODAL);
}
void townEnding() {
    /**
     * Creates a messagebox to display text to the user.
     */
    MessageBox(NULL, "After a long, tiring journey, you stumble into a small town.\nThe townspeople are wary of you at first, but you settle in quickly.\nYou warm up to life in this quaint, little village and forget your delusions of escape.", "Your new happy life",
    MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
    return;
}
void dragonEnding(HWND hwnd) {
    /**
    * Creates a messagebox to display text to the user.
    * @param hwnd handler for the current window
    */
    int ready = MessageBox(NULL, "The dragon lowers its head, allowing you to carefully climb atop its back.\nYou and your new dragon buddy reach the end of the sky and smash through the confining Window.\n[OK] to close window.", "Ending Dialog",
    MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
    if (ready == IDOK) {
        DestroyWindow(hwnd);  // the only real way to close this app
    } else {
        return;
    }
}
void eatenEnding(int style) {
    /**
     * Creates a messagebox to display story ending text to the user.
     * @param style an integer that represents which ending should be displayed
     */
    switch(style) {
        case 1:
            MessageBox(NULL, "The dragon devours you whole.\nThe last thought in your head is of how uncomfortable your wet, slimy clothes feel.", "From the stomach of the beast",
            MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
            return;
        case 2:
            MessageBox(NULL, "You never wake up.\nYou are devoured by wild woodland creatures and your bones are used to fertilize the forest ecosystem.", "Return to nature",
            MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
            return;
        default:
            MessageBox(NULL, "You never wake up.\nYou are devoured by wild woodland creatures and your bones are used to fertilize the forest ecosystem.", "Return to nature",
            MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
            return;
    }
}
void storyHandler(HWND hwnd) {
    /**
     * Creates a set series of choices defined by messageboxes.
     * Handles user interaction with messagebox elements.
     * @param hwnd handler for the current window
     */
    int first = storyDialog("You stand alone on a narrow path in a densely wooded area.\nTall coniferous trees surround you, limiting your vision to the path ahead and behind you.\n[CANCEL] to turn around and start walking. [CONTINUE] to forge ahead.");
    switch(first) {
        case IDCANCEL:
            townEnding();
            return;
        case IDTRYAGAIN:
            int leave = ynDialog("What a baby. Do you still want to keep trying to quit?");
            if (leave == IDYES) {
                MessageBox(NULL, "Haha.\nAfter that outburst, I'm not surprised. Still, too bad.", "You're staying here.",
                MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);
            } else {
                happyDialog();
            }
            return;
        case IDCONTINUE:
            int second = storyDialog("After walking for hours, the sun hangs low in the sky at your back.\nLong shadows stretch their dark grasping fingers towards the mouth of an ominous crack in the approaching cliff side.\n[CANCEL] to attempt to set up a camp to pass the long night. [TRY AGAIN] to turn around and try your luck in the opposite direction.[CONTINUE] to dash caution to the wind and venture into the crevice.");
            switch(second) {
                case IDCANCEL:
                    int ending = 2;
                    eatenEnding(ending);
                    return;
                case IDTRYAGAIN:
                    townEnding();
                    return;
                case IDCONTINUE:
                    int joker = ynDialog("Within the crevice, a mighty dragon rests, curled into a scaly pile.\nUpon your intrusion, It awakens.\n'You have disturbed my rest, Human. The price for your rudeness is to entertain me.'\n[YES] to tell it your best joke. [NO] to apologize and back out of the cave.");
                    if (joker == IDYES) {
                        dragonEnding(hwnd);
                    } else {
                        int ending = 1;
                        eatenEnding(ending);
                        return;
                    }
            }
    }
    return;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    /**
    * Defines the Window Procedure.
    * Handles messages sent to the window.
    * @param hwnd handler for the current window
    * @param msg current message sent to the window
    */
    switch(msg)
    {
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
                            storyHandler(hwnd);
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
    /**
    * Defines the window's class and creates the window.
    * @param hInstance handle to the executable in memory
    * @param hPrevInstance artifact from Win16, always NULL
    * @param lpCmdLine pointer to command line args
    * @param nCmdShow integer specifying thew window's show state
    * @return current message in window message queue
    */
    WNDCLASSEX mc;
    HWND hwnd;
    MSG Msg;
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