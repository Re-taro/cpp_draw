#include <string>

std::string colorSpace(const auto col) {
	return "\033[48;2;" +
		std::to_string(col[0]) + ";" +
		std::to_string(col[1]) + ";" +
		std::to_string(col[2]) + "m \033[0m";
}