#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/select.h>

int __program_nano__(void);

int main(void) {
    __program_nano__();
    return 0;
}

int __program_nano__(void){
    struct termios oldt, newt;
    struct timeval tv = {0, 0};
    fd_set fds;
    struct winsize w;
    char data[100][100] = {""}, file_name[100] = "New Buffer";
    int x = 0, y = 0, print_cursor = 1, use_ansi = 0, writed = 0, page = 0, key = 0;
    int reload_body = 0, page_type = -1, next_page_type = 0;
    const char* page0_keys[] = {
        "^G", "^O", "^W", "^K", "^T", "^C", "M-U", "M-A", "M-]", "M-Q",
        "^X", "^R", "^\\", "^U", "^J", "^-", "M-E", "M-6", "^Q", "M-W"
    };
    const char* page0_labels[] = {
        " Help        ", " Write Out   ", " Where Is    ", " Cut         ", " Execute     ",
        " Location    ", " Undo       ", " Set Mark   ", " To Bracket ", " Previous   ",
        " Exit        ", " Read File   ", " Replace     ", " Paste       ", " Justify     ",
        " Go To Line  ", " Redo       ", " Copy       ", " Where was   ", " Next       "
    };
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO | ISIG);
    newt.c_iflag &= ~(IXON | ICRNL);
    newt.c_oflag &= ~(OPOST | ONLCR);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (1){
        if (!use_ansi || reload_body){
            if (!reload_body){
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                #if defined(_WIN32) || defined(_WIN64)
                    system("cls");
                #elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
                    system("clear");
                #endif
                if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0){
                    w.ws_row = 12;
                    w.ws_col = 40;
                    use_ansi = 0;
                    page_type = -1;
                }else {
                    w.ws_col /= 2;
                    use_ansi = 1;
                    write(STDOUT_FILENO, "\x1b[?25l", 6);
                }
                write(STDOUT_FILENO, "  Virt nano 2.0 ", 16);
                for (int i = 0; i < (w.ws_col/2)-4; i++){
                    write(STDOUT_FILENO, " ", 1);
                }
                write(STDOUT_FILENO, file_name, strlen(file_name));
                if (writed){
                    write(STDOUT_FILENO, " *", 2);
                }else {
                    write(STDOUT_FILENO, "  ", 2);
                }
                
                for (int i = (w.ws_col/2)+(int)strlen(file_name)+14; i < w.ws_col*2; i++){
                    write(STDOUT_FILENO, " ", 1);
                }
                write(STDOUT_FILENO, "#\n", 2);
            }else {
                reload_body = 0;
                printf("asdf");
            }
            for (int i = (w.ws_row-(200/w.ws_col))*page; i < (w.ws_row-(200/w.ws_col))*(page+1); i++){
                int len = (int)strlen(data[i]), temp = 0;
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;1H", i+2);
                }
                for (int j = 0; j <= len; j++){
                    if (i == y && j == x){
                        temp = 1;
                        write(STDOUT_FILENO, "_", 1);
                    }else {
                        dprintf(STDOUT_FILENO, "%c", data[i][j]);
                    }
                }
                for (int i = len+temp; i < w.ws_col * 2; i++){
                    write(STDOUT_FILENO, " ", 1);
                }
                write(STDOUT_FILENO, "#\n", 2);
            }
        }
        if (next_page_type != page_type){
            switch (next_page_type) {
                case 0:{
                    int temp = 0, ansi_temp = 1;
                    if (use_ansi){
                        dprintf(STDOUT_FILENO, "\x1b[%d;1H", ansi_temp+(w.ws_row-(200/w.ws_col)));
                    }
                    for (int i = 0; i < 20; i++){
                        if (temp + 15 > w.ws_col*2){
                            for (int j = temp; j < w.ws_col*2; j++){
                                write(STDOUT_FILENO, " ", 1);
                            }
                            write(STDOUT_FILENO, "#\n", 2);
                            if (use_ansi){
                                ansi_temp++;
                                dprintf(STDOUT_FILENO, "\x1b[%d;1H", ansi_temp+(w.ws_row-(200/w.ws_col)));
                            }
                            temp = 0;
                        }
                        dprintf(STDOUT_FILENO, "%s", page0_keys[i]);
                        dprintf(STDOUT_FILENO, "%s", page0_labels[i]);
                        temp += 15;
                    }
                    for (int j = temp; j < w.ws_col*2; j++){
                        write(STDOUT_FILENO, " ", 1);
                    }
                    if (!use_ansi){
                        write(STDOUT_FILENO, "#", 1);
                    }
                    break;
                }
            }
            page_type = next_page_type;
        }
        key = 0;
        tv.tv_usec = 350000;
        while (1){
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (0 < select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv)){
                read(STDIN_FILENO, &key, 1);
                break;
            }else if (0 == 1){
                break;
            }
        }
        if (key == -17 || key == 27 || key == 239){
            read(STDIN_FILENO, &key, 1);
            read(STDIN_FILENO, &key, 1);
            printf("%d", key);
            switch (key) {
                case -125: case 'C': case 131:
                    if (x < w.ws_col*2 && x < strlen(data[y])) {
                        if (use_ansi){
                            dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c_", y+2, x+1, data[y][x]);
                        }
                        x++;
                        break;
                    }
                case -127: case 'B': case 129:
                    if (use_ansi){
                        if (data[y][x] != '\0'){
                            dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, data[y][x]);
                        }else {
                            dprintf(STDOUT_FILENO, "\x1b[%d;%dH ", y+2, x+1);
                        }
                    }
                    if (x > strlen(data[y+1])){
                        x = (int)strlen(data[y+1]);
                    }
                    if (use_ansi){
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+3, x+1);
                    }
                    y++;
                    if (y >= (w.ws_row-(200/w.ws_col))*(page+1) && page < 100){
                        page++;
                        reload_body = 1;
                    }
                    break;
                case -126: case 'D': case 130:
                    if (0 < x){
                        if (use_ansi){
                            if (data[y][x] != '\0'){
                                dprintf(STDOUT_FILENO, "\x1b[%d;%dH_%c", y+2, x, data[y][x]);
                            }else {
                                dprintf(STDOUT_FILENO, "\x1b[%d;%dH_ ", y+2, x);
                            }
                        }
                        x--;
                        break;
                    }
                case -128: case 'A': case 128:
                    if (y < 1){
                        break;
                    }
                    if (use_ansi){
                        if (data[y][x] != '\0'){
                            dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, data[y][x]);
                        }else {
                            dprintf(STDOUT_FILENO, "\x1b[%d;%dH ", y+2, x+1);
                        }
                    }
                    if (x > strlen(data[y-1]) || (key == -126 || key == 'D' || key == 130)){
                        x = (int)strlen(data[y-1]);
                    }
                    if (use_ansi){
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+1, x+1);
                    }
                    y--;
                    if (y <= (w.ws_row-(200/w.ws_col))*page && 0 < page){
                        page--;
                        reload_body = 1;
                    }
                    break;
            }
            print_cursor = 0;
        }else if (key == 0){
            print_cursor = !print_cursor;
            if (print_cursor){
                dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+2, x+1);
            }else if (data[y][x] != '\0'){
                dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, data[y][x]);
            }else {
                dprintf(STDOUT_FILENO, "\x1b[%d;%dH ", y+2, x+1);
            }
        }else if (key == 9){
            if (use_ansi && writed == 0){
                dprintf(STDOUT_FILENO, "\x1b[1;%dH", 14+(w.ws_col/2)+(int)strlen(file_name));
                write(STDOUT_FILENO, "*", 1);
            }
            writed = 1;
            if (data[y][x] != '\0'){
                for (int i = (int)strlen(data[y]); x <= i; i--){
                    data[y][i+4] = data[y][i];
                }
            }else {
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH    _", y+2, x+1);
                }
                data[y][x+1] = '\0';
            }
            for (int i = 0; i < 4; i++){
                data[y][x+i] = ' ';
            }
            x += 4;
        }else if (key == 10 || key == 13){
            if (use_ansi){
                if (data[y][x] != '\0'){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, data[y][x]);
                }else {
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH ", y+2, x+1);
                }
            }
            if (x > strlen(data[y+1])){
                x = (int)strlen(data[y+1]);
            }
            if (use_ansi){
                dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+3, x+1);
            }
            y++;
            if (y+2 >= (w.ws_row-(200/w.ws_col))*(page+1) && page < 100){
                page++;
                reload_body = 1;
            }
        }else if (key == 24){
            break;
        }else if (key == 127){
            if (0 < x){
                if (data[y][x] != '\0'){
                    if (use_ansi){
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+2, x);
                    }
                    for (int i = x-1; i < strlen(data[y]); i++){
                        data[y][i] = data[y][i+1];
                        if (use_ansi && x-1 < i){
                            dprintf(STDOUT_FILENO, "%c", data[y][i+1]);
                        }
                    }
                    if (use_ansi){
                        write(STDOUT_FILENO, " ", 1);
                    }
                }else {
                    data[y][x-1] = '\0';
                    if (use_ansi){
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH_ ", y+2, x);
                    }
                }
                x--;
            }else if (0 < y){
                if (use_ansi){
                    if (data[y][x] != '\0'){
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, data[y][x]);
                    }else {
                        dprintf(STDOUT_FILENO, "\x1b[%d;%dH ", y+2, x+1);
                    }
                }
                x = (int)strlen(data[y-1]);
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+1, x+1);
                }
                y--;
                if (y <= (w.ws_row-(200/w.ws_col))*page && 0 < page){
                    page--;
                    reload_body = 1;
                }
            }
        }else {
            if (use_ansi && writed == 0){
                dprintf(STDOUT_FILENO, "\x1b[1;%dH", 14+(w.ws_col/2)+(int)strlen(file_name));
                write(STDOUT_FILENO, "*", 1);
            }
            writed = 1;
            if (data[y][x] != '\0'){
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c", y+2, x+1, key);
                }
                for (int i = (int)strlen(data[y]); x <= i; i--){
                    data[y][i+1] = data[y][i];
                    if (use_ansi && i < (int)strlen(data[y])){
                        dprintf(STDOUT_FILENO, "%c", data[y][(int)strlen(data[y])-i]);
                    }
                }
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH_", y+2, x+2);
                }
            }else {
                if (use_ansi){
                    dprintf(STDOUT_FILENO, "\x1b[%d;%dH%c_", y+2, x+1, key);
                }
                data[y][x+1] = '\0';
            }
            data[y][x] = key;
            x++;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}


