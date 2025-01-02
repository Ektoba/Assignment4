#include "pch.h"
#include "App.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(237);
	int retValue = NULL;
	// Start the Dear ImGui frame
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();
	//bool show_demo_window = true;
	//ImGui::ShowDemoWindow(&show_demo_window);

	if (CApp::GetInst()->Init())
	{
		retValue = CApp::GetInst()->Run();
	}

	return NULL;
}
//void configureConsoleForRawInput(HANDLE hInput) {
//    DWORD mode;
//    if (!GetConsoleMode(hInput, &mode)) {
//        std::cerr << "Error: Could not get console mode." << std::endl;
//        return;
//    }
//
//    // Disable line buffering and echo
//    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
//    if (!SetConsoleMode(hInput, mode)) {
//        std::cerr << "Error: Could not set console mode." << std::endl;
//    }
//}
//void renderScreen(HANDLE hOutput, const std::string& buffer) {
//    DWORD bytesWritten;
//    WriteFile(hOutput, buffer.c_str(), buffer.size(), &bytesWritten, NULL);
//}
//
//int main() {
//    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    if (hInput == INVALID_HANDLE_VALUE || hOutput == INVALID_HANDLE_VALUE) {
//        std::cerr << "Error: Invalid console handle." << std::endl;
//        return 1;
//    }
//
//    configureConsoleForRawInput(hInput);
//
//    char inputBuffer[256];
//    DWORD bytesRead;
//    std::string screenBuffer = "Double buffering in action!\nPress Enter to update...";
//
//    while (true) {
//        renderScreen(hOutput, screenBuffer);
//
//        // Read input
//        if (ReadFile(hInput, inputBuffer, sizeof(inputBuffer) - 1, &bytesRead, NULL)) {
//            inputBuffer[bytesRead] = '\0'; // Null-terminate input
//            screenBuffer += std::string(inputBuffer);
//        }
//        else {
//            std::cerr << "Error: ReadFile failed." << std::endl;
//            break;
//        }
//    }
//
//    return 0;
//}