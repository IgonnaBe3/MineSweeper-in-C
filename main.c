#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


char** create_map(int length_x_of_array, int length_y_of_array)
{
    char** map;
    map = malloc(sizeof(*map) * length_x_of_array);
    for(int i=0;i<length_x_of_array;i++)
    {
        map[i]=malloc(sizeof(map) * length_y_of_array);
    }
    for(int i=0;i<length_x_of_array;i++)
    {
        for(int j=0;j<length_y_of_array;j++)
        {
            map[i][j]='0';
        }
    }
    return map;
}

bool** create_view_grid(int length_x_of_array, int length_y_of_array)
{
    bool** grid;
    grid = malloc(sizeof(*grid) * length_x_of_array);
    for(int i=0;i<length_x_of_array;i++)
    {
        grid[i]=malloc(sizeof(grid) * length_y_of_array);
    }
    for(int i=0;i<length_x_of_array;i++)
    {
        for(int j=0;j<length_y_of_array;j++)
        {
            grid[i][j]=0;
        }
    }
    return grid;
}

void fill_map(char** map, int length_x_of_array, int length_y_of_array, int number_of_bombs)
{
    srand(time(NULL));
    for(int i=0;i<number_of_bombs;i++)
    {
        int rand_x=rand()%length_x_of_array;
        int rand_y=rand()%length_y_of_array;
        if(map[rand_x][rand_y]=='B')
        {
            i--;
        }
        else
        {
            map[rand_x][rand_y]='B';
        }
    }
    for(int i = 0; i < length_x_of_array; i++)
    {
        for(int j = 0; j < length_y_of_array; j++)
        {

            if(map[i][j]=='B')
            {

            }
            else
            {
                if(i > 0 && j > 0 && map[i-1][j-1]=='B')
                {
                    map[i][j]++;
                }
                if(i > 0 && map[i-1][j]=='B' )
                {
                    map[i][j]++;
                }
                if( i > 0 && j < length_y_of_array - 1 && map[i-1][j+1]=='B')
                {
                    map[i][j]++;
                }
                if( j < length_y_of_array - 1 && map[i][j+1]=='B' )
                {
                    map[i][j]++;
                }
                if(i < length_x_of_array - 1 && j < length_y_of_array - 1 && map[i+1][j+1]=='B')
                {
                    map[i][j]++;
                }
                if( i < length_x_of_array - 1 && map[i+1][j]=='B')
                {
                    map[i][j]++;
                }
                if( i < length_x_of_array - 1 && j > 0 && map[i+1][j-1]=='B')
                {
                    map[i][j]++;
                }
                if( j > 0&&map[i][j-1]=='B' )
                {
                    map[i][j]++;
                }

            }
        }
    }
}

void draw(char** map, bool** grid, int length_x_of_array, int length_y_of_array)
{
    printf("  ");
    for(int i=0;i<length_x_of_array;i++)
    {
        printf("%2d",i);
    }
    printf("\n");
    for(int i=0;i<length_x_of_array;i++)
    {
        printf("%2d",i);
        for(int j=0;j<length_y_of_array;j++)
        {
            if(grid[i][j]==1)
            {
                printf("%2c", map[i][j]);
            }
            else
            {
                printf("%2c",'#');
            }
        }
        printf("\n");
    }
}

int reveal(bool** grid, char** map, int coordinate_x_row, int coordinate_y_collumn, int length_x_of_array, int length_y_of_array, int* revealed_squares)
{
    grid[coordinate_x_row][coordinate_y_collumn]=1;
    if(map[coordinate_x_row][coordinate_y_collumn]=='B')
    {
        return -1;
    }
    ++*(revealed_squares);
    if(map[coordinate_x_row][coordinate_y_collumn]=='0')
    {
        if(coordinate_x_row > 0 && coordinate_y_collumn > 0 && grid[coordinate_x_row-1][coordinate_y_collumn-1]==0)
        {
            grid[coordinate_x_row-1][coordinate_y_collumn-1]=1;
            reveal(grid,map,coordinate_x_row-1,coordinate_y_collumn-1,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if(coordinate_x_row > 0 && grid[coordinate_x_row-1][coordinate_y_collumn]==0)
        {
            grid[coordinate_x_row-1][coordinate_y_collumn]=1;
            reveal(grid,map,coordinate_x_row-1,coordinate_y_collumn,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if( coordinate_x_row > 0 && coordinate_y_collumn < length_y_of_array - 1 && grid[coordinate_x_row-1][coordinate_y_collumn+1]==0)
        {
            grid[coordinate_x_row-1][coordinate_y_collumn+1]=1;
            reveal(grid,map,coordinate_x_row-1,coordinate_y_collumn+1,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if( coordinate_y_collumn < length_y_of_array - 1 &&grid[coordinate_x_row][coordinate_y_collumn+1]==0)
        {
            grid[coordinate_x_row][coordinate_y_collumn+1]=1;
            reveal(grid,map,coordinate_x_row,coordinate_y_collumn+1,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if(coordinate_x_row < length_x_of_array - 1 && coordinate_y_collumn < length_y_of_array - 1 &&grid[coordinate_x_row+1][coordinate_y_collumn+1]==0)
        {
            grid[coordinate_x_row+1][coordinate_y_collumn+1]=1;
            reveal(grid,map,coordinate_x_row+1,coordinate_y_collumn+1,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if( coordinate_x_row < length_x_of_array - 1 && grid[coordinate_x_row+1][coordinate_y_collumn]==0)
        {
            grid[coordinate_x_row+1][coordinate_y_collumn]=1;
            reveal(grid,map,coordinate_x_row+1,coordinate_y_collumn,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if( coordinate_x_row < length_x_of_array - 1 && coordinate_y_collumn > 0 && grid[coordinate_x_row+1][coordinate_y_collumn-1]==0)
        {
            grid[coordinate_x_row+1][coordinate_y_collumn-1]=1;
            reveal(grid,map,coordinate_x_row+1,coordinate_y_collumn-1,length_x_of_array,length_y_of_array,revealed_squares);
        }
        if( coordinate_y_collumn > 0&& grid[coordinate_x_row][coordinate_y_collumn-1]==0)
        {
            grid[coordinate_x_row][coordinate_y_collumn-1]=1;
            reveal(grid,map,coordinate_x_row,coordinate_y_collumn-1,length_x_of_array,length_y_of_array,revealed_squares);
        }
    }
    return 0;
}

void gameloop()
{
    int continue_game=0;
    int length_x_of_array;
    int length_y_of_array;
    int number_of_bombs;
    int revealed_squares=0;
    printf("Type in the size of the minesweeper grid in the \"[row] [collumn]\" format: ");
    scanf("%d %d", &length_x_of_array, &length_y_of_array);
    printf("Type in the number of the bombs in the grid: ");
    char** map;
    bool** grid;
    scanf("%d",&number_of_bombs);
    map=create_map(length_x_of_array, length_y_of_array);
    grid=create_view_grid(length_x_of_array, length_y_of_array);
    fill_map(map, length_x_of_array, length_y_of_array, number_of_bombs);
    while(continue_game==0)
    {

        system("cls");
        printf("\n");
        draw(map, grid, length_x_of_array, length_y_of_array);
        int x;
        int y;
        scanf("%d %d", &x, &y);
        continue_game=reveal(grid,map,x,y,length_x_of_array,length_y_of_array, &revealed_squares);
        printf("\n");
        if(revealed_squares==((length_x_of_array * length_y_of_array) - number_of_bombs))
        {
            continue_game=1;
        }
    }
    if(continue_game==-1)
    {
        printf("Unfortunately, you lost.");
    }
    else if(continue_game==1)
    {
        printf("Congratulations, you win.");
    }
    free(map);
    free(grid);
}

int main()
{
    gameloop();
    return 0;
}
