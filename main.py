import curses
import random
import time

# spaceship
RAW_BRAILLE_ART = r"""
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

SHIP_ART = [line for line in RAW_BRAILLE_ART.splitlines() if line]

def main(stdscr):
    # hide cursor
    curses.curs_set(0)
    # unblock the program
    stdscr.nodelay(True)
    
    # get screen size
    max_y, max_x = stdscr.getmaxyx()
    
    # star: [y, x, speed]
    stars = []
    num_stars = 60
    for star in range(num_stars):
        stars.append([
            random.randint(1, max_y - 2),  # x
            random.randint(1, max_x - 2),  # y
            random.choice([1, 2, 3])       # speed
        ])
        
    # spaceship position
    ship_y = max_y // 2 - (len(SHIP_ART) // 2)
    ship_x = 5
    
    frame_count = 0

    while True:
        key = stdscr.getch()
        if key == ord('q'):  # exit 'q'
            break
            
        # 1. update star coordinates
        frame_count += 1
        for star in stars:
            if frame_count % star[2] == 0:
                star[1] -= 1
                
            # if the star is behind the left edge
            if star[1] <= 0:
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
        for i, line in enumerate(SHIP_ART):
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