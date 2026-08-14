#include "logger.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

std::vector<LogEntry> Logger::messages;

std::string GetCurrentTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now_time));
	return output;
}

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = INFO;
	logEntry.message = "LOG: [" + GetCurrentTime() + "]: " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = ERROR;
	logEntry.message = "ERR: [" + GetCurrentTime() + "]: " + message;
	messages.push_back(logEntry);
	std::cerr << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;
}