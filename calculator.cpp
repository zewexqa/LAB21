#include <windows.h>

#include <stdio.h>



#define ID_INPUT1 1

#define ID_INPUT2 2

#define ID_ADD 3

#define ID_SUBTRACT 4

#define ID_MULTIPLY 5

#define ID_DIVIDE 6



HWND hInput1, hInput2;



// ฟังก์ชันคำนวณและแสดงผลลัพธ์

void Calculate(HWND hwnd, char op) {

    char buffer1[50], buffer2[50];

    double num1, num2, result;



    GetWindowText(hInput1, buffer1, 50);

    GetWindowText(hInput2, buffer2, 50);



    num1 = atof(buffer1);

    num2 = atof(buffer2);



    switch (op) {

        case '+': result = num1 + num2; break;

        case '-': result = num1 - num2; break;

        case '*': result = num1 * num2; break;

        case '/':

            if (num2 == 0) {

                MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_ICONERROR);

                return;

            }

            result = num1 / num2;

            break;

    }



    char resultText[100];

    sprintf(resultText, "%.6f", result);

    MessageBox(hwnd, resultText, "Result", MB_OK);

}



// ฟังก์ชันหลักของ Window

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

        case WM_CREATE:

            // ข้อความบนหน้าต่าง

            CreateWindow("STATIC", "Please input two numbers",

                         WS_CHILD | WS_VISIBLE | WS_BORDER,

                         30, 10, 180, 20, hwnd, NULL, NULL, NULL);



            // ช่องกรอกตัวเลข

            hInput1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,

                                   40, 40, 160, 25, hwnd, (HMENU) ID_INPUT1, NULL, NULL);

            hInput2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,

                                   40, 70, 160, 25, hwnd, (HMENU) ID_INPUT2, NULL, NULL);



            // ปุ่มคำนวณ

            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,

                         40, 110, 30, 30, hwnd, (HMENU) ID_ADD, NULL, NULL);

            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,

                         80, 110, 30, 30, hwnd, (HMENU) ID_SUBTRACT, NULL, NULL);

            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,

                         120, 110, 30, 30, hwnd, (HMENU) ID_MULTIPLY, NULL, NULL);

            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,

                         160, 110, 30, 30, hwnd, (HMENU) ID_DIVIDE, NULL, NULL);

            break;



        case WM_COMMAND:

            switch (LOWORD(wParam)) {

                case ID_ADD: Calculate(hwnd, '+'); break;

                case ID_SUBTRACT: Calculate(hwnd, '-'); break;

                case ID_MULTIPLY: Calculate(hwnd, '*'); break;

                case ID_DIVIDE: Calculate(hwnd, '/'); break;

            }

            break;



        case WM_CTLCOLORSTATIC:  // เปลี่ยนสีพื้นหลังของ Static Text

            SetBkMode((HDC) wParam, TRANSPARENT);

            return (LRESULT) CreateSolidBrush(RGB(255, 255, 255));



        case WM_CLOSE:

            DestroyWindow(hwnd);

            break;



        case WM_DESTROY:

            PostQuitMessage(0);

            break;



        default:

            return DefWindowProc(hwnd, msg, wParam, lParam);

    }

    return 0;

}



// ฟังก์ชัน WinMain (เริ่มโปรแกรม)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WndProc;

    wc.hInstance = hInstance;

    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 96)); // พื้นหลังสีชมพูเข้ม

    wc.lpszClassName = "CalculatorClass";



    RegisterClass(&wc);



    HWND hwnd = CreateWindow("CalculatorClass", "My Calculator",

                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,

                             CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,

                             NULL, NULL, hInstance, NULL);



    ShowWindow(hwnd, nCmdShow);

    UpdateWindow(hwnd);



    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);

        DispatchMessage(&msg);

    }



    return msg.wParam;

}
