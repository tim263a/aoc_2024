#pragma once

#include <cstdint>

#include <string>
#include <vector>

void read_stdio_into_buffer(std::vector<uint8_t>& buffer, bool verbose = true);
std::string read_stdin();
std::vector<std::string> read_stdin_lines();
