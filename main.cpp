#include <ncurses.h>
#include <locale.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

struct Star {
    int y;
    int x;
    int speed;
};

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

    std::vector<Star> stars;
    adjust_stars(stars, max_y, max_x);

    int frame_count = 0;

    while (true) {
        int key = getch();
        if (key == 'q') {
            break;
        } else if (key == KEY_RESIZE) {
            getmaxyx(stdscr, max_y, max_x);
            adjust_stars(stars, max_y, max_x);
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

        // refresh screen
        refresh();

        // ~60 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    endwin();
    return 0;
}
