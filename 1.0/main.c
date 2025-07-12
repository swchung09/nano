#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>

void __clear__(void);
char __get_input_realtime__(void);
int __program_nano__(char* dir);

int main(void){
    __program_nano__("/");
    return 0;
}

void __clear__(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #else
        printf("\033[2J\033[H");
        fflush(stdout);
    #endif
}

char __get_input_realtime__(void){
    char ch;
    #if defined(_WIN32) || defined(_WIN64)
        while (1){
            if (kbhit()){
                ch = getch();
                return ch;
            }
        }
    #elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        static struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO | ISIG);
        newt.c_cc[VMIN] = 0;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        while (1){
            struct timeval tv = {0, 0};
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (0 < select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv)){
                read(STDIN_FILENO, &ch, 1);
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                return ch;
            }
        }
    #else
        ch = getchar();
    #endif
}

int __program_nano__(char* dir){
    char data[100][100] = {""};
    char temp1[200], temp2[1000] = "";
    int cur_key = 0, pre_key = 0, x = 0, y = 0, page = 0, writed = 0, use_ansi;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0) {
        printf("Getting display data failed. It can be displayed wrong.\nWish to continue?(y, c(change), n)");
        char t = 'y';//__get_input_realtime__();
        if (t == 'c' || t == 'C'){
            printf("Row, Col : ");
            scanf("%hu %hu", &w.ws_row, &w.ws_col);
        }else if (t == 'n' || t == 'N'){
            return 0;
        }else {
            w.ws_row = 12;
            w.ws_col = 40;
        }
        use_ansi = 0;
    }else {
        w.ws_col /= 2;
        use_ansi = 1;
    }
    for (int i = 0; i < w.ws_col/2; i++){
        temp1[i] = ' ';
    }
    temp1[(w.ws_col/2)+1] = '\0';
    int p = 0;
    for (int i = 0; i < 20; i++){
        if (p+15 > w.ws_col*2){
            strcat(temp2, "\n");
            p = 0;
        }
        switch (i) {
            case 0:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^G");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Help        ");
                break;
            case 1:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^O");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Write Out   ");
                break;
            case 2:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^W");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Where Is    ");
                break;
            case 3:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^K");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Cut         ");
                break;
            case 4:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^T");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Execute     ");
                break;
            case 5:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^C");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Location    ");
                break;
            case 6:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-U");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Undo       ");
                break;
            case 7:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-A");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Set Mark   ");
                break;
            case 8:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-]");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " To Bracket ");
                break;
            case 9:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-Q");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Previous   ");
                break;
            case 10:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^X");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Exit        ");
                break;
            case 11:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^R");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Read File   ");
                break;
            case 12:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^\\");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Replace     ");
                break;
            case 13:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^U");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Paste       ");
                break;
            case 14:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^J");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Justify     ");
                break;
            case 15:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^-");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Go To Line  ");
                break;
            case 16:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-E");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Redo       ");
                break;
            case 17:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-6");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Copy       ");
                break;
            case 18:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "^Q");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Where was   ");
                break;
            case 19:
                if (use_ansi){
                    strcat(temp2, "\033[30;47m");
                }
                strcat(temp2, "M-W");
                if (use_ansi){
                    strcat(temp2, "\033[37;40m");
                }
                strcat(temp2, " Next       ");
                break;
        }
        p += 15;
    }
    __clear__();
    while (1){
        if (use_ansi){
            printf("\033[30;47m");
        }
        printf("  Virt nano 1.5%s%s ", temp1, "New Buffer");
        if (writed == 1){
            printf("*");
        }
        for (int i = 0; i < (w.ws_col*2)-(20+(w.ws_col/2)+strlen("New Buffer"))-writed; i++){
            printf(" ");
        }
        if (use_ansi){
            printf("\033[37;40m");
        }
        printf("\n");
        for (int i = (w.ws_row-(200/w.ws_col))*page; i < (w.ws_row-(200/w.ws_col))*(page+1); i++){
            if (i == y){
                for (int j = 0; j <= strlen(data[i]); j++){
                    if (j == x){
                        printf("_");
                    }else {
                        printf("%c", data[i][j]);
                    }
                }
                for (int j = (int)strlen(data[i])+4; j < w.ws_col*2; j++){
                    printf(" ");
                }
                printf("\n");
            }else {
                printf("%s", data[i]);
                for (int j = (int)strlen(data[i])+3; j < w.ws_col*2; j++){
                    printf(" ");
                }
                printf("\n");
            }
        }
        printf("%s", temp2);
        if (use_ansi){
            printf("\033[37;40m");
        }
        pre_key = cur_key;
        cur_key = __get_input_realtime__();
        __clear__();
        if (cur_key == -17 && __get_input_realtime__() == -100){
            cur_key = __get_input_realtime__();
            switch (cur_key){
                case -125:
                    if (x < w.ws_col*2 && x < strlen(data[y])){
                        x++;
                    }
                    break;
                case -126:
                    if (0 < x){
                        x--;
                    }
                    break;
                case -127:
                    if (x >= strlen(data[y+1])){
                        x = (int)strlen(data[y+1]);
                    }
                    if (y+1 < (w.ws_row-(200/w.ws_col))*(page+1)){
                        y++;
                    }else if (page < 100){
                        page++;
                        y++;
                    }
                    break;
                case -128:
                    if (0 < y && x >= strlen(data[y-1])){
                        x = (int)strlen(data[y-1]);
                    }
                    if ((w.ws_row-(200/w.ws_col))*page < y){
                        y--;
                    }else if (0 < page){
                        page--;
                        y--;
                    }
                    break;
            }
        }else if (cur_key == 27 && __get_input_realtime__() == '['){
            cur_key = __get_input_realtime__();
            switch (cur_key){
                case 'C':
                    if (x < w.ws_col*2 && x < strlen(data[y])){
                        x++;
                    }
                    break;
                case 'D':
                    if (0 < x){
                        x--;
                    }
                    break;
                case 'B':
                    if (x >= strlen(data[y+1])){
                        x = (int)strlen(data[y+1]);
                    }
                    if (y+1 < (w.ws_row-(200/w.ws_col))*(page+1)){
                        y++;
                    }else if (page < 100){
                        page++;
                        y++;
                    }
                    break;
                case 'A':
                    if (0 < y && x >= strlen(data[y-1])){
                        x = (int)strlen(data[y-1]);
                    }
                    if ((w.ws_row-(200/w.ws_col))*page < y){
                        y--;
                    }else if (0 < page){
                        page--;
                        y--;
                    }
                    break;
            }
        }else if (cur_key == 127){
            if (0 < x){
                if (data[y][x] != '\0'){
                    for (int i = x-1; i < strlen(data[y]); i++){
                        data[y][i] = data[y][i+1];
                    }
                }else {
                    data[y][x-1] = '\0';
                }
                x--;
            }
        }else {
            writed = 1;
            if (data[y][x] != '\0'){
                for (int i = (int)strlen(data[y]); i >= x; i--){
                    data[y][i+1] = data[y][i];
                }
                data[y][x] = cur_key;
            }else {
                data[y][x] = cur_key;
                data[y][x+1] = '\0';
            }
            x++;
        }
    }
    return 0;
}

