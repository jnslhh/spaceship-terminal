#include <ncurses.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <clocale>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

// Spaceship frame definitions using raw string UTF-8 literals
const std::string FRAME_0 = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶
⠀⠀⠀⠀⠀⠀⠈⠛⠛⢃⣀⣀⠀⠀⠀⠉⠰⢶⣶⣶⣶⣶⠶⠶
⠀⠀⠀⠀⠉⠀⠀⠀⠀⠈⠉⠉⠰⠶⠆⣤⠀⠀⢸⣿⣿⣷⣽⣢⣄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⢹⣿⣿⣿⣷⣯⣖⣤⣀⣀⣀⣀⣀⣀⡀
⠀⠀⠶⠆⠶⠶⠶⠰⠶⠶⠆⠶⠶⠰⢶⣼⣿⣿⡟⡏⢿⣿⣿⣿⢻⣧⣶⣴⣶⣴⣶⣴⣦⠉⠱⣦⣤⣤⣤
⠀⠀⠀⠐⠒⠐⠒⠒⠀⠒⠒⠒⠐⠚⠈⠙⢻⣿⣷⣧⣿⣿⣿⣿⣾⣧⣿⣿⣿⣿⣿⣿⣿⠶⠞⠋
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣿⣻⣟⣛⣻⣿⣿⣷⣾⣷⣶⣾⣽⢖⣶⣭⠭⣛⢖⣒⡦⠤⣀⡀
⠀⠀⠤⠈⣁⠈⣉⣁⣈⠉⣉⣁⠉⣉⢸⣿⣿⣿⣿⡇⣿⣿⣟⡯⣻⣿⣿⣾⣿⣿⢹⣿⣟⠉⠀⠹⡏⢿⣿⣿⠿⣟⠆
⠀⠀⠀⠀⠉⠀⠉⠉⠉⠀⠉⠉⠈⠉⠀⠈⠙⠛⣿⣵⣯⣭⣽⣿⣿⣭⣿⣯⣭⣽⣿⣮⣿⣿⣶⣯⣮⣭⠷⠶⠉⠁
⠀⠀⠀⢠⣤⢠⣤⣤⠀⣤⣤⣤⢠⣤⢀⣠⣴⣶⣯⡝⣯⣭⣭⣭⣽⡗⣚⣓⣒⣒⣛⣒⣒⠭⢍⠉
⠀⠀⠤⠄⠤⠤⠄⠠⠤⠤⠄⠤⠤⠠⠼⢿⣿⣿⣧⡇⣿⣿⣿⣿⣼⡓⠿⠻⣿⠻⠿⢻⡟⣀⣠⠿⠒⠒⠒⠂
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⢹⣷⣶⣶⣶⡾⣿⠟⠛⠛⠛⠛⠛⠛⠉⠁
⠀⠀⠀⠀⣀⠀⠀⠀⠀⢀⢀⢀⠠⠤⠔⠛⠀⠀⢰⣿⣿⣿⣻⡕⠋
⠀⠀⠀⠀⠉⠀⢀⣀⣀⡈⠉⠉⠀⠀⠀⠤⠠⠼⠿⠿⠯⠷⠭⠤
⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠤⠀
)";

const std::string FRAME_1 = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂
⠀⠀⠀⠀⠀⠀⠀⠘⠓⢄⣀⡀⠀⠀⠀⠉⠰⢶⣶⣶⣶⣶⠶⠶
⠀⠀⠀⠀⠡⠀⠀⠀⠀⠀⠉⠉⠰⠤⠂⣤⠀⠀⢸⣿⣿⣷⣽⣢⣄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⢹⣿⣿⣿⣷⣯⣖⣤⣀⣀⣀⣀⣀⣀⡀
⠀⠀⠀⠀⠒⠐⠒⠒⠐⠒⠒⠐⠒⠒⠰⢶⣼⣿⣿⡟⡏⢿⣿⣿⣿⢻⣧⣶⣴⣶⣴⣶⣴⣦⠉⠱⣦⣤⣤⣤
⠀⠀⠀⠀⠀⠤⠀⠤⠤⠀⠤⠤⠤⠐⠚⠈⠙⢻⣿⣷⣧⣿⣿⣿⣿⣾⣧⣿⣿⣿⣿⣿⣿⣿⠶⠞⠋
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣿⣻⣟⣛⣻⣿⣿⣷⣾⣷⣶⣾⣽⢖⣶⣭⠭⣛⢖⣒⡦⠤⣀⡀
⠀⠀⠀⠡⠈⢁⠈⢉⢁⣈⠉⢉⢁⠉⢉⢸⣿⣿⣿⣿⡇⣿⣿⣟⡯⣻⣿⣿⣾⣿⣿⢹⣿⣟⠉⠀⠹⡏⢿⣿⣿⠿⣟⠆
⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠉⠉⠈⠉⠀⠈⠙⠛⣿⣵⣯⣭⣽⣿⣿⣭⣿⣯⣭⣽⣿⣮⣿⣿⣶⣯⣮⣭⠷⠶⠉⠁
⠀⠀⠀⠀⢠⣀⢠⣀⣀⠀⣀⣀⣀⢠⣀⢀⣠⣴⣶⣯⡝⣯⣭⣭⣭⣽⡗⣚⣓⣒⣒⣛⣒⣒⠭⢍⠉
⠀⠀⠀⠡⠀⠠⠠⠀⠠⠠⠠⠀⠠⠠⠠⠼⢿⣿⣿⣧⡇⣿⣿⣿⣿⣼⡓⠿⠻⣿⠻⠿⢻⡟⣀⣠⠿⠒⠒⠒⠂
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⢹⣷⣶⣶⣶⡾⣿⠟⠛⠛⠛⠛⠛⠛⠉⠁
⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⢀⠠⠤⠔⠛⠀⠀⢰⣿⣿⣿⣻⡕⠋
⠀⠀⠀⠀⠀⠀⠀⣀⣀⡈⠉⠉⠀⠀⠀⠤⠠⠼⠿⠿⠯⠷⠭⠤
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠤⠀
)";

const std::string FRAME_2 = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠉⠰⢶⣶⣶⣶⣶⠶⠶
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠤⠆⣤⠀⠀⢸⣿⣿⣷⣽⣢⣄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⢹⣿⣿⣿⣷⣯⣖⣤⣀⣀⣀⣀⣀⣀⡀
⠀⠀⠀⠀⠀⠀⠤⠤⠤⠤⠤⠤⠤⠤⠤⠰⢶⣼⣿⣿⡟⡏⢿⣿⣿⣿⢻⣧⣶⣴⣶⣴⣶⣴⣦⠉⠱⣦⣤⣤⣤
⠀⠀⠀⠀⠀⠀⠀⠐⠒⠐⠒⠒⠒⠐⠚⠈⠙⢻⣿⣷⣧⣿⣿⣿⣿⣾⣧⣿⣿⣿⣿⣿⣿⣿⠶⠞⠋
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣿⣻⣟⣛⣻⣿⣿⣷⣾⣷⣶⣾⣽⢖⣶⣭⠭⣛⢖⣒⡦⠤⣀⡀
⠀⠀⠀⠀⠀⠀⠀⠀⣈⠉⣉⣁⠉⣉⢸⣿⣿⣿⣿⡇⣿⣿⣟⡯⣻⣿⣿⣾⣿⣿⢹⣿⣟⠉⠀⠹⡏⢿⣿⣿⠿⣟⠆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠈⠉⠀⠈⠙⠛⣿⣵⣯⣭⣽⣿⣿⣭⣿⣯⣭⣽⣿⣮⣿⣿⣶⣯⣮⣭⠷⠶⠉⠁
⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⣤⣤⣤⢠⣤⢀⣠⣴⣶⣯⡝⣯⣭⣭⣭⣽⡗⣚⣓⣒⣒⣛⣒⣒⠭⢍⠉
⠀⠀⠀⠀⠀⠀⠠⠤⠤⠄⠤⠤⠄⠤⠤⠠⠼⢿⣿⣿⣧⡇⣿⣿⣿⣿⣼⡓⠿⠻⣿⠻⠿⢻⡟⣀⣠⠿⠒⠒⠒⠂
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⢹⣷⣶⣶⣶⡾⣿⠟⠛⠛⠛⠛⠛⠛⠉⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠤⠔⠛⠀⠀⢰⣿⣿⣿⣻⡕⠋
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡈⠉⠉⠀⠀⠀⠤⠠⠼⠿⠿⠯⠷⠭⠤
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⠀
)";

const std::string FRAME_3 = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢
⠀⠀⠀⠀⠀⠐⠈⠛⢃⢀⡀⠀⠀⠀⠉⠰⢶⣶⣶⣶⣶⠶⠶
⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠉⠰⠢⠔⣤⠀⠀⢸⣿⣿⣷⣽⣢⣄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⢹⣿⣿⣿⣷⣯⣖⣤⣀⣀⣀⣀⣀⣀⡀
⠀⠀⠤⠢⠤⠤⠤⠠⠤⠤⠢⠤⠤⠠⢶⣼⣿⣿⡟⡏⢿⣿⣿⣿⢻⣧⣶⣴⣶⣴⣶⣴⣦⠉⠱⣦⣤⣤⣤
⠀⠀⠀⠡⠐⠡⠐⠡⠀⠡⠐⠂⠐⠚⠈⠙⢻⣿⣷⣧⣿⣿⣿⣿⣾⣧⣿⣿⣿⣿⣿⣿⣿⠶⠞⠋
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣿⣻⣟⣛⣻⣿⣿⣷⣾⣷⣶⣾⣽⢖⣶⣭⠭⣛⢖⣒⡦⠤⣀⡀
⠀⠀⠡⠈⢄⠈⢄⡈⠉⢄⡈⠉⢄⢸⣿⣿⣿⣿⡇⣿⣿⣟⡯⣻⣿⣿⣾⣿⣿⢹⣿⣟⠉⠀⠹⡏⢿⣿⣿⠿⣟⠆
⠀⠀⠀⠀⠁⠀⠈⠉⠁⠀⠉⠁⠈⠁⠀⠈⠙⠛⣿⣵⣯⣭⣽⣿⣿⣭⣿⣯⣭⣽⣿⣮⣿⣿⣶⣯⣮⣭⠷⠶⠉⠁
⠀⠀⠀⢀⣠⢀⣠⣄⠀⣠⣄⣄⢀⣄⢀⣠⣴⣶⣯⡝⣯⣭⣭⣭⣽⡗⣚⣓⣒⣒⣛⣒⣒⠭⢍⠉
⠀⠀⠡⢀⠡⠡⢀⠠⠡⠡⢀⠡⠡⢀⠼⢿⣿⣿⣧⡇⣿⣿⣿⣿⣼⡓⠿⠻⣿⠻⠿⢻⡟⣀⣠⠿⠒⠒⠒⠂
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⢹⣷⣶⣶⣶⡾⣿⠟⠛⠛⠛⠛⠛⠛⠉⠁
⠀⠀⠀⠀⢀⠀⠀⠀⠀⢀⢀⠀⠠⠤⠔⠛⠀⠀⢰⣿⣿⣿⣻⡕⠋
⠀⠀⠀⠀⠁⠀⢀⢀⢀⡈⠉⠁⠀⠀⠀⠤⠠⠼⠿⠿⠯⠷⠭⠤
⠀⠀⠀⠀⠀⠀⠀⠈⠉⠁⠤⠀
)";

namespace {

constexpr int kShipX = 2;
constexpr int kVerticalMargin = 1;
constexpr int kTargetFrameDelayMs = 16;
constexpr int kShipDriftInterval = 30;
constexpr int kShipFrameInterval = 4;
constexpr double kStarDensity = 0.025;
constexpr int kMinimumStars = 10;

const std::array<std::string, 4> SHIP_FRAME_TEXT = {
    FRAME_0,
    FRAME_1,
    FRAME_2,
    FRAME_3,
};

struct Star {
    int y;
    int x;
    int speed;
};

using Frame = std::vector<std::string>;
using ShipFrames = std::array<Frame, 4>;

size_t utf8_length(const std::string& str) {
    size_t len = 0;
    for (char c : str) {
        if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) {
            len++;
        }
    }
    return len;
}

std::string utf8_substr(const std::string& str, size_t start_code_point) {
    size_t current_cp = 0;
    size_t byte_index = 0;
    while (byte_index < str.size()) {
        if (current_cp >= start_code_point) {
            return str.substr(byte_index);
        }
        unsigned char c = static_cast<unsigned char>(str[byte_index]);
        if (c < 0x80) byte_index += 1;
        else if ((c & 0xE0) == 0xC0) byte_index += 2;
        else if ((c & 0xE0) == 0xE0) byte_index += 3;
        else if ((c & 0xF0) == 0xF0) byte_index += 4;
        else byte_index += 1;
        current_cp++;
    }
    return "";
}

Frame split_frame(const std::string& str) {
    Frame lines;
    std::string current_line;
    for (char c : str) {
        if (c == '\n') {
            if (!current_line.empty()) {
                lines.push_back(current_line);
                current_line.clear();
            }
        } else {
            current_line.push_back(c);
        }
    }
    if (!current_line.empty()) {
        lines.push_back(current_line);
    }
    return lines;
}

ShipFrames load_ship_frames() {
    ShipFrames frames;
    for (size_t i = 0; i < frames.size(); ++i) {
        frames[i] = split_frame(SHIP_FRAME_TEXT[i]);
    }

    const size_t line_count = frames.front().size();
    if (line_count == 0) {
        throw std::runtime_error("spaceship art has no drawable lines");
    }

    for (const auto& frame : frames) {
        if (frame.size() != line_count) {
            throw std::runtime_error("spaceship animation frames must have matching line counts");
        }
    }

    for (auto& frame : frames) {
        for (size_t i = 0; i < frame.size(); ++i) {
            const size_t target_len = utf8_length(frames.front()[i]);
            const size_t current_len = utf8_length(frame[i]);

            if (current_len < target_len) {
                frame[i] = std::string(target_len - current_len, ' ') + frame[i];
            } else if (current_len > target_len) {
                frame[i] = utf8_substr(frame[i], current_len - target_len);
            }
        }
    }

    return frames;
}

int random_between(std::mt19937& rng, int min_value, int max_value) {
    std::uniform_int_distribution<int> distribution(min_value, max_value);
    return distribution(rng);
}

int ship_height(const ShipFrames& frames) {
    return static_cast<int>(frames.front().size());
}

int ship_width(const ShipFrames& frames) {
    size_t width = 0;
    for (const auto& line : frames.front()) {
        width = std::max(width, utf8_length(line));
    }
    return static_cast<int>(width);
}

bool terminal_can_draw_ship(int max_y, int max_x, const ShipFrames& frames) {
    return max_y >= ship_height(frames) + (kVerticalMargin * 2) &&
           max_x >= ship_width(frames) + kShipX + 1;
}

int centered_ship_y(int max_y, const ShipFrames& frames) {
    return std::max(kVerticalMargin, (max_y - ship_height(frames)) / 2);
}

void draw_too_small_message(int max_y, int max_x) {
    static const std::string message = "Terminal too small";
    erase();
    const int y = std::max(0, max_y / 2);
    const int x = std::max(0, (max_x - static_cast<int>(message.size())) / 2);
    mvaddnstr(y, x, message.c_str(), max_x);
    refresh();
}

Star create_star(std::mt19937& rng, int max_y, int max_x) {
    return {
        random_between(rng, 1, max_y - 2),
        random_between(rng, 1, max_x - 2),
        random_between(rng, 1, 3),
    };
}

void adjust_stars(std::vector<Star>& stars, int max_y, int max_x, std::mt19937& rng) {
    if (max_y < 3 || max_x < 3) {
        stars.clear();
        return;
    }

    const int screen_area = max_y * max_x;
    int target_num_stars = static_cast<int>(static_cast<double>(screen_area) * kStarDensity);
    target_num_stars = std::max(target_num_stars, kMinimumStars);

    while (stars.size() < static_cast<size_t>(target_num_stars)) {
        stars.push_back(create_star(rng, max_y, max_x));
    }
    while (stars.size() > static_cast<size_t>(target_num_stars)) {
        stars.pop_back();
    }
}

void update_stars(std::vector<Star>& stars, int frame_count, int max_y, int max_x, std::mt19937& rng) {
    if (max_y < 3 || max_x < 3) {
        stars.clear();
        return;
    }

    for (auto& star : stars) {
        if (frame_count % star.speed == 0) {
            star.x -= 1;
        }

        if (star.x <= 0 || star.x >= max_x || star.y >= max_y) {
            star = create_star(rng, max_y, max_x);
            star.x = max_x - 2;
        }
    }
}

void update_ship_position(int& ship_y, int& ship_direction, int frame_count, int max_y, const ShipFrames& frames) {
    if (frame_count % kShipDriftInterval != 0) {
        return;
    }

    ship_y += ship_direction;

    const int upper_limit = kVerticalMargin;
    const int lower_limit = std::max(upper_limit, max_y - ship_height(frames) - kVerticalMargin);

    if (ship_y <= upper_limit) {
        ship_y = upper_limit;
        ship_direction = 1;
    } else if (ship_y >= lower_limit) {
        ship_y = lower_limit;
        ship_direction = -1;
    }
}

void draw_stars(const std::vector<Star>& stars) {
    for (const auto& star : stars) {
        const char star_char = (star.speed == 3) ? '.' : ((star.speed == 2) ? '*' : '+');
        mvaddch(star.y, star.x, static_cast<chtype>(star_char));
    }
}

void draw_ship(const ShipFrames& frames, int frame_count, int ship_y) {
    const size_t frame_index =
        (static_cast<size_t>(frame_count) / static_cast<size_t>(kShipFrameInterval)) % frames.size();
    const auto& current_ship_art = frames[frame_index];

    for (size_t i = 0; i < current_ship_art.size(); ++i) {
        mvaddstr(ship_y + static_cast<int>(i), kShipX, current_ship_art[i].c_str());
    }
}

} // namespace

int main() {
    setlocale(LC_ALL, "");

    const ShipFrames ship_frames = load_ship_frames();

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    std::random_device random_device;
    std::mt19937 rng(random_device());

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    std::vector<Star> stars;
    adjust_stars(stars, max_y, max_x, rng);

    int ship_y = centered_ship_y(max_y, ship_frames);
    int ship_direction = 1; // -1 - up, 1 - down
    int frame_count = 0;

    while (true) {
        int key = getch();
        if (key == 'q') {
            break;
        } else if (key == KEY_RESIZE) {
            getmaxyx(stdscr, max_y, max_x);
            ship_y = centered_ship_y(max_y, ship_frames);
            adjust_stars(stars, max_y, max_x, rng);
        }

        frame_count++;

        if (!terminal_can_draw_ship(max_y, max_x, ship_frames)) {
            draw_too_small_message(max_y, max_x);
            std::this_thread::sleep_for(std::chrono::milliseconds(kTargetFrameDelayMs));
            continue;
        }

        update_ship_position(ship_y, ship_direction, frame_count, max_y, ship_frames);
        update_stars(stars, frame_count, max_y, max_x, rng);

        erase();
        draw_stars(stars);
        draw_ship(ship_frames, frame_count, ship_y);
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(kTargetFrameDelayMs));
    }

    endwin();
    return 0;
}
