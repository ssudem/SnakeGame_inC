#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#define RED     "\x1b[31m" //0
#define GREEN   "\x1b[32m" //1
#define YELLOW  "\x1b[33m" //2
#define BLUE    "\x1b[34m" //3
#define MAGENTA "\x1b[35m" //4
#define CYAN    "\x1b[36m" //5
#define RESET   "\x1b[0m"  //6
#define cls printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))
typedef struct cordi
{
    int x, y;
} cordi;
const int HEIGHT = 24, WIDTH = 52;
cordi snake[100], fruit;
int length, score;
char direction;

void setup(void)
{
    length = 0;
    score = 0;
    direction = '\0';
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    fruit.x = (rand() % (WIDTH - 4)) + 2;
    fruit.y = (rand() % (HEIGHT - 4)) + 2;
}

void PrintGame(void)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        printf(" %s|",BLUE);
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1) // boarder up and bottom .
            {
                printf("%s+",BLUE);
            }
            else if (i == fruit.y && j == fruit.x)
            {
                printf("%s$",GREEN);
            }
            else
            {
                bool flag = false;
                for (int k = 0; k <= length; k++)
                {
                    if (snake[k].x == j && snake[k].y == i)
                    {
                        flag = true;
                        if (k == 0)
                            printf("%s%c", RED,(char)(254)); 
                        else
                            printf("%so",MAGENTA);
                        break;
                    }
                }
                if (!flag)
                {
                    printf(" ");
                }
            }
        }
        printf("%s|\n",BLUE);
    }
    printf(YELLOW);
    printf("\n | -> Score = %s%3d%s | -> SnakeLength = %s%2d%s | ",RED,score,YELLOW,RED,length,YELLOW);
}

void moveHead(void)
{
    switch (direction)
    {
    case 'U':
        snake[0].y--;
        break;
    case 'L':
        snake[0].x--;
        break;
    case 'R':
        snake[0].x++;
        break;
    case 'D':
        snake[0].y++;
        break;
    default:
        snake[0].x = WIDTH / 2;
        snake[0].y = HEIGHT / 2;
    }
    // This Below conditions are for moving snake throuch walls :-
    if (snake[0].y < 1)
        snake[0].y = HEIGHT - 2;
    else if (snake[0].y > HEIGHT - 2)
        snake[0].y = 1;
    else if (snake[0].x < 0)
        snake[0].x = WIDTH - 1;
    else if (snake[0].x > WIDTH - 1)
        snake[0].x = 0;
}

void DirInput(void)
{
    if (kbhit())
    {
        switch (getch())
        {
        case 72:
            if (direction != 'D')
            {
                direction = 'U';
            }
            break;
        case 75:
            if (direction != 'R')
            {
                direction = 'L';
            }
            break;
        case 80:
            if (direction != 'U')
            {
                direction = 'D';
            }
            break;
        case 77:
            if (direction != 'L')
            {
                direction = 'R';
            }
            break;
        }
    }
}

void update(void)
{
    for (int i = length; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    if (fruit.x == snake[0].x && fruit.y == snake[0].y)
    {
        fruit.x = (rand() % (WIDTH - 4)) + 2;
        fruit.y = (rand() % (HEIGHT - 4)) + 2;
        score+=5;
        length++;
    }
}

bool gameOver(void)
{
    if (length > 98)
        return true;
    if (snake[0].x == WIDTH || snake[0].x == -1 || snake[0].y == HEIGHT - 1 || snake[0].y == 0)
        return true;
    for (int i = length; i > 0; i--)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            return true;
        }
    }
    return false;
}
int main()
{
    cls;
    srand(time(NULL));
    setup();
    while (!gameOver())
    {
        gotoxy(0, 0);
        PrintGame();
        DirInput();
        update();
        moveHead();
        sleep(0.5);
    }
    printf(RESET);
    return 0;
}