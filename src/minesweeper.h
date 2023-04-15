typedef enum Tile{
    FREE=0,
    MINE=9
} Tile;

typedef struct Board Board;

Board* create_board(int width, int height, int mines);

void destroy_board(Board*);

Tile reveal(Board*, int x, int y);