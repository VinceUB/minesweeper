#include <stdlib.h>
#include <stdbool.h>

#include "minesweeper.h"

struct Board{
    bool** cells;
    int width;
    int height;
};

int generate_random_number(int upper_bound){
    return rand() % upper_bound; //TODO: Use a more secure function
}

Board* create_board(int width, int height, int mines){
    if(mines > width*height)
        return NULL;

    Board* b = malloc(sizeof(b));
    b->width = width;
    b->height = height;

    b->cells = malloc(width * sizeof(bool*));
    for(int x = 0; x < width; x++)
        b->cells[x] = calloc(height, sizeof(bool));
    
    //Populate
    for(int i = 0; i < mines; i++){
        int x,y;
        do{
            x = generate_random_number(width);
            y = generate_random_number(height);
        } while (b->cells[x][y]);
        b->cells[x][y]=true;
    }

    return b;
}

void destroy_board(Board* b){
    for(int x = 0; x < b->width; x++){
        free(b->cells[x]);
    }
    free(b->cells);
}

Tile reveal(Board* b, int x, int y){
    int adjacent_mines = 0;
    if(x>0         && y>0          && b->cells[x-1][y-1]) adjacent_mines++;
    if(               y>0          && b->cells[x  ][y-1]) adjacent_mines++;
    if(x<=b->width && y>0          && b->cells[x+1][y-1]) adjacent_mines++;
    if(x>0                         && b->cells[x-1][y  ]) adjacent_mines++;
    if(                               b->cells[x  ][y  ]) return MINE;
    if(x<=b->width                 && b->cells[x+1][y  ]) adjacent_mines++;
    if(x>0         && y<=b->height && b->cells[x-1][y+1]) adjacent_mines++;
    if(               y<=b->height && b->cells[x  ][y+1]) adjacent_mines++;
    if(x<=b->width && y<=b->height && b->cells[x+1][y+1]) adjacent_mines++;

    return adjacent_mines;
}