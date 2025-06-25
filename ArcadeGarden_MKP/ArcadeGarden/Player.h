#pragma once
#include <string>
#include <optional>

struct Player {
	int player_id;
	std::string name;
	std::optional<std::string> email;
	std::optional<uint8_t> age;
	float currency;
	bool musicOn;
	uint8_t volume;
};