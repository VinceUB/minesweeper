#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "minesweeper.h"

int main(){
    srand(time(NULL));

    const int width = 10;
    const int height = 8;
    const int mines = 10;

    Board* b = create_board(width, height, mines);

    char* field = malloc(((width+1)*height+1) * sizeof(char));
    for(int i = 0; i < (width+1)*height+1; i++){
        int x = i % (width+1);
        int y = i / (width+1);

        if      (i == (width+1)*height)
            field[i] = '\0';
        else if (x == width)
            field[i] = '\n';
        else
            field[i] =  '#';
    }

    bool alive = true;
    while(alive){
        int x, y;
        scanf("%d %d", &x, &y);
        Tile t = reveal(b, x, y);
        printf("Got %d %d\n", x, y);
        switch(t){
            case FREE:
                field[y*(width+1) + x] = ' ';
                break;
            case MINE:
                field[y*(width+1) + x] = 'B';
                alive = false;
                break;
            default:
                field[y*(width+1) + x] = t+'0';
                break;
        }
        printf("%s", field);
    }

    destroy_board(b);
    free(b);
}