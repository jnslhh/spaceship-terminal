#include <ncurses.h>
#include <locale.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

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

struct Star {
    int y;
    int x;
    int speed;
};

// Helper function to count UTF-8 code points
size_t utf8_length(const std::string& str) {
    size_t len = 0;
    for (char c : str) {
        if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) {
            len++;
        }
    }
    return len;
}

// Helper function to slice UTF-8 string by code point index
std::string utf8_substr(const std::string& str, size_t start_code_point) {
    size_t current_cp = 0;
    size_t byte_index = 0;
    while (byte_index < str.size()) {
        if (current_cp >= start_code_point) {
            return str.substr(byte_index);
        }
        unsigned char c = str[byte_index];
        if (c < 0x80) byte_index += 1;
        else if ((c & 0xE0) == 0xC0) byte_index += 2;
        else if ((c & 0xE0) == 0xE0) byte_index += 3;
        else if ((c & 0xF0) == 0xF0) byte_index += 4;
        else byte_index += 1;
        current_cp++;
    }
    return "";
}

// Splits a string by newline and removes empty lines
std::vector<std::string> split_frame(const std::string& str) {
    std::vector<std::string> lines;
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

void adjust_stars(std::vector<Star>& stars, int max_y, int max_x) {
    int targetNumStars = static_cast<int>((max_y * max_x) * 0.025);
    if (targetNumStars < 10) targetNumStars = 10;

    while (stars.size() < static_cast<size_t>(targetNumStars)) {
        stars.push_back({
            rand() % (max_y - 2) + 1,
            rand() % (max_x - 2) + 1,
            rand() % 3 + 1
        });
    }
    while (stars.size() > static_cast<size_t>(targetNumStars)) {
        stars.pop_back();
    }
}

int main() {
    // wide-character support initialization
    setlocale(LC_ALL, "");
    
    // ncurses initialization
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    srand(time(nullptr));

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Setup ship frames
    std::vector<std::vector<std::string>> ship_frames = {
        split_frame(FRAME_0),
        split_frame(FRAME_1),
        split_frame(FRAME_2),
        split_frame(FRAME_3)
    };

    // Align frame lines to matches sizes (using UTF-8 character length logic)
    for (auto& frame : ship_frames) {
        for (size_t i = 0; i < frame.size(); ++i) {
            size_t target_len = utf8_length(ship_frames[0][i]);
            size_t current_len = utf8_length(frame[i]);
            
            if (current_len < target_len) {
                frame[i] = std::string(target_len - current_len, ' ') + frame[i];
            } else if (current_len > target_len) {
                frame[i] = utf8_substr(frame[i], current_len - target_len);
            }
        }
    }

    std::vector<Star> stars;
    adjust_stars(stars, max_y, max_x);

    int ship_y = max_y / 2 - (ship_frames[0].size() / 2);
    int ship_x = 2;
    int ship_direction = 1; // -1 - up, 1 - down
    int ship_speed = 30;

    int frame_count = 0;

    while (true) {
        int key = getch();
        if (key == 'q') {
            break;
        } else if (key == KEY_RESIZE) {
            getmaxyx(stdscr, max_y, max_x);
            ship_y = max_y / 2 - (ship_frames[0].size() / 2);
            adjust_stars(stars, max_y, max_x);
        }

        if (frame_count % ship_speed == 0) {
            ship_y += ship_direction;

            // check upper limit
            if (ship_y <= 1) {
                ship_y = 1;
                ship_direction = 1;
            }
            // check lower limit
            else if (ship_y >= max_y - static_cast<int>(ship_frames[0].size()) - 1) {
                ship_y = max_y - static_cast<int>(ship_frames[0].size()) - 1;
                ship_direction = -1;
            }
        }

        frame_count++;

        // 1. update star coordinates
        for (auto& star : stars) {
            if (frame_count % star.speed == 0) {
                star.x -= 1;
            }
            if (star.x <= 0 || star.x >= max_x || star.y >= max_y) {
                star.x = max_x - 2;
                star.y = rand() % (max_y - 2) + 1;
                star.speed = rand() % 3 + 1;
            }
        }

        // 2. clear frame
        erase();

        // 3. drawing stars
        for (const auto& star : stars) {
            char star_char = (star.speed == 3) ? '.' : ((star.speed == 2) ? '*' : '+');
            mvaddch(star.y, star.x, star_char);
        }

        // 4. drawing spaceship
        int current_frame_index = (frame_count / 4) % 4;
        const auto& current_ship_art = ship_frames[current_frame_index];

        for (size_t i = 0; i < current_ship_art.size(); ++i) {
            mvaddstr(ship_y + i, ship_x, current_ship_art[i].c_str());
        }

        // refresh screen
        refresh();

        // ~60 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    endwin();
    return 0;
}
