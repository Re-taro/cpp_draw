#include <signal.h>
#include <windows.h>
#include "color_space.cpp"
#include <iostream>
#include <vector>
#define NOMINMAX


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
		std::string buf{};

		for (size_t i = 0; i < height; i++) {
			for (size_t t = 0; i < width; t++) {
				buf += colorSpace(color[i][t]);
			}
			buf += "\n";
		}
		std::cout << "\033[H";
		std::cout << buf;
	}
	std::vector<glm::vec2> heart(const size_t n) {
		std::vector<glm::vec2> pts(n);
		for (size_t i = 0; i < n; i++) {
			double t = (double)i / n * std::numbers::pi * 2.0;
			double x = 16 * pow(sin(t), 3);
			double y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
			pts[i] = { x / 16.0, -((y + 2.5) / 14.5) };
		}
		return pts;
	}

	void drawHeart(const size_t n, const size_t count, const size_t width, const size_t height) {
		std::vector<std::vector<glm::ivec3>> color(height, std::vector<glm::ivec3>(width, { 0, 0, 0 }));
		std::vector<glm::vec2> pts = heart(n);
		auto rot = glm::toMat4(glm::quat(glm::vec3(0.0, count * 0.1, 0.0)));

		for (auto& p : pts) {
			auto v = rot * glm::vec4(p, 0.0, 1.0);
			v *= (width / 2.0) * 0.9;
			v += (width / 2.0);
			if (v.y < 0 || v.y >= height || v.x < 0 || v.x >= width) continue;
			color[(size_t)v.y][(size_t)v.x] = { 255, 255, 255 };
		}
	}
}