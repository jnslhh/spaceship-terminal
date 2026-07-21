import curses
import random
import time

# spaceship
FRAME_0 = r"""
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
"""
FRAME_1 = r"""
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
"""

FRAME_2 = r"""
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
"""

FRAME_3 = r"""
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
"""
SHIP_FRAMES = [
    [line for line in FRAME_0.splitlines() if line],
    [line for line in FRAME_1.splitlines() if line],
    [line for line in FRAME_2.splitlines() if line],
    [line for line in FRAME_3.splitlines() if line]
]

for frame in SHIP_FRAMES:
    for i in range(len(frame)):
        target_len = len(SHIP_FRAMES[0][i])
        current_len = len(frame[i])
        
        if current_len < target_len:
            frame[i] = " " * (target_len - current_len) + frame[i]
        elif current_len > target_len:
            frame[i] = frame[i][current_len - target_len:]

# Dynamic change in the number of stars for the current screen area
def adjust_stars(stars, max_y, max_x):
    # new density
    targetNumStars = int((max_y * max_x) * 0.025) # 100*24=2400(+-default value) 60(stars)/2400=0.0025

    targetNumStars = max(10, targetNumStars)

    while len(stars) < targetNumStars:
        stars.append([
            random.randint(1, max_y - 2),
            random.randint(1, max_x - 2),
            random.choice([1, 2, 3])
        ])

    while len(stars) > targetNumStars:
        stars.pop()

def main(stdscr):
    # hide cursor
    curses.curs_set(0)
    # unblock the program
    stdscr.nodelay(True)
    
    # get screen size
    max_y, max_x = stdscr.getmaxyx()
    
    # star: [y, x, speed]
    stars = []
    adjust_stars(stars, max_y, max_x)
        
    # spaceship position
    ship_y = max_y // 2 - (len(SHIP_FRAMES[0]) // 2)
    ship_x = 2
    
    frame_count = 0

    shipDirection = 1 # -1 - up, 1 - down
    shipSpeed = 30

    while True:
        key = stdscr.getch()
        if key == ord('q'):  # exit 'q'
            break

        # if the user resizes the window
        elif key == curses.KEY_RESIZE:
            curses.update_lines_cols() #update curses size

            max_y, max_x = stdscr.getmaxyx() # update screen size

            ship_y = max_y // 2 - (len(SHIP_FRAMES[0]) // 2) # update the spaceship position

            adjust_stars(stars, max_y, max_x)

        if frame_count % shipSpeed == 0:
            ship_y += shipDirection

            # check upper limit
            if ship_y <= 1:
                ship_y = 1
                shipDirection = 1
            
            # check lower limit
            elif ship_y >= max_y - len(SHIP_FRAMES[0]) - 1:
                ship_y = max_y - len(SHIP_FRAMES[0]) - 1
                shipDirection = -1

        # 1. update star coordinates
        frame_count += 1
        for star in stars:
            if frame_count % star[2] == 0:
                star[1] -= 1
                
            # if the star is behind the left edge
            if star[1] <= 0 or star[1] >= max_x or star[0] >= max_y:
                star[1] = max_x - 2
                star[0] = random.randint(1, max_y - 2)
                star[2] = random.choice([1, 2, 3])

        # 2. clear the frame
        stdscr.erase()

        # 3. drawing stars
        for star in stars:
            star_char = '.' if star[2] == 3 else ('*' if star[2] == 2 else '+')
            try:
                stdscr.addch(star[0], star[1], star_char)
            except curses.error:
                pass 

        # 4. drawing spaceship
        current_frame_index = (frame_count // 4) % 4
        
        current_ship_art = SHIP_FRAMES[current_frame_index]

        for i, line in enumerate(current_ship_art):
            try:
                stdscr.addstr(ship_y + i, ship_x, line)    
            except curses.error:
                pass

        # on display
        stdscr.refresh()

        # 60 fps = 1 sec / 60 frames  
        time.sleep(0.016)

if __name__ == "__main__":
    import locale
    locale.setlocale(locale.LC_ALL, '')
    curses.wrapper(main)