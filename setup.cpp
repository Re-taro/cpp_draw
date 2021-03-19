#include <signal.h>
#define NOMINMAX
#include <windows.h>


volatile sig_atomic_t _FLAG = 0;
static void close(int signal) { _FLAG = 1; };

int main(int argc, char* argv[]) {
	signal(SIGINT, close);

	DWORD l_mode;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hstdout, &l_mode);
	SetConsoleMode(hstdout, l_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 1;
	cfi.dwFontSize.Y = 1;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hstdout, FALSE, &cfi);

	size_t width = 300, height = 300;
	COORD dwsize = { static_cast<SHORT>(width) + 1,static_cast<SHORT>(height) + 1 };
	SetConsoleScreenBufferSize(hstdout, dwsize);
	SMALL_RECT consolewindow = { 0,0,dwsize.X - 1,dwsize.Y - 1 };
	SetConsoleWindowInfo(hstdout, TRUE, &consolewindow);

	//ï`âÊÉãÅ[Év
	for (size_t count = 0; !_FLAG; count++) {

	}
}