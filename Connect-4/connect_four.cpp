#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <windows.h>

const int rows = 6;
const int columns = 7;
int turn = 1; // By default, it is of player 1
bool isWon = false; // whether a certain player has won or not

struct information
{
    int x; // x-coordinate of the rectangular block
    int y; // y-coordinate of the rectangular block
    bool filled; // rectangular block is colored or not
    int who_filled; // who filled this block. 1 for player one, 2 for player two, and 0 for empty
};
information board[rows][columns];

void drawBoard()
{
    int x = 40, y = 40; // initial x and y coordinates
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            setcolor(BLUE);
            rectangle(x, y, x + 40, y + 40);
            board[i][j].x = x + 1;
            board[i][j].y = y + 1;
            board[i][j].filled = false;
            board[i][j].who_filled = 0;
            x = x + 40;
        }
        x = 40;
        y = 40 + y;
    }
    // writing column names under the board
    settextstyle(8, 0, 1); // font type, font direction, font size
    setcolor(BLACK);
    outtextxy(55, 285, "a");
    outtextxy(95, 285, "b");
    outtextxy(135, 285, "c");
    outtextxy(175, 285, "d");
    outtextxy(215, 285, "e");
    outtextxy(255, 285, "f");
    outtextxy(295, 285, "g");
    line(40, 310, 321, 310); // drawing a black line under the column names
}

bool checkWin()
{
    // checking for horizontal
    for (int j = 0; j < 6; j++)
    {
        for (int i = 3; i < 7; i++)
        {
            // 4 blocks in a row and they all should match
            int first = board[j][i].who_filled;
            int second = board[j][i-1].who_filled;
            int third = board[j][i-2].who_filled;
            int fourth = board[j][i-3].who_filled;
            if (first == turn && second == turn && third == turn && fourth == turn)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }

    // checking for vertical
    for (int i = 0; i < 7; i++)
    {
        for (int j = 3; j < 6; j++)
        {
            // 4 blocks in a row and they all should match
            int first = board[j][i].who_filled;
            int second = board[j-1][i].who_filled;
            int third = board[j-2][i].who_filled;
            int fourth = board[j-3][i].who_filled;
            if (first == turn && second == turn && third == turn && fourth == turn)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }

    // checking for diagonal
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // checking left and right both diagonals
            // if either matches, then it is a win
            int first = board[j][i].who_filled;
            int second = board[j+1][i+1].who_filled;
            int third = board[j+2][i+2].who_filled;
            int fourth = board[j+3][i+3].who_filled;

            int five = board[j+3][i].who_filled;
            int six = board[j+2][i+1].who_filled;
            int seven = board[j+1][i+2].who_filled;
            int eight = board[j][i+3].who_filled;

            if ((first == turn && second == turn && third == turn && fourth == turn) || (five == turn && six == turn && seven == turn && eight == turn))
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

// function to fill rectangular block with green or red color depending on whose turn it is
// i and j are the row and column index of game board
void fillRectangle(int i, int j)
{
    bool flag = false; // whether a particular column was completely filled or not
    while (i >= 0) // keep running until we run out of rows to fill
    {
        if (board[i][j].filled == false) // if current block not filled, we will then color it
        {
            if (turn == 1)
            {
                setfillstyle(SOLID_FILL, GREEN);
                floodfill(board[i][j].x, board[i][j].y, BLUE);
                board[i][j].filled = true;
                board[i][j].who_filled = 1;
                bool won = checkWin();
                if (won == true)
                {
                    isWon = true;
                    return;
                }
                turn = 2;
            }
            else
            {
                setfillstyle(SOLID_FILL, RED);
                floodfill(board[i][j].x, board[i][j].y, BLUE);
                board[i][j].filled = true;
                board[i][j].who_filled = 2;
                bool won = checkWin();
                if (won == true)
                {
                    isWon = true;
                    return;
                }
                turn = 1;
            }
            flag = true;
            break;
        }
        else
        {
            i--; // move to the upper row if current block is filled already
        }
    }
    if (flag == false) // meaning that particular column was completely filled
    {
        settextstyle(8, 0, 1); // font type, font direction, font size
        setcolor(BLACK);
        outtextxy(340, 140, "This column is filled");
        outtextxy(340, 170, "Choose another one please!");
    }
}

bool checkAllFilled()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j].filled == false)
            {
                return false;
            }
        }
    }
    return true;
}

void clear_board()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            board[i][j].filled = false;
            board[i][j].who_filled = 0;
        }
    }
}

void main_menu()
{
    // Connect 4 text
    setcolor(BLUE);
    settextstyle(8, 0, 8); // font type, font direction, font size
    outtextxy(70, 170, "Connect 4");
    // Red circle inside first C
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(97, 207, 10);
    floodfill(97, 207, RED);
    // Green circle inside O
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    circle(145, 212, 10);
    floodfill(145, 212, GREEN);
    // Red circle inside second c
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(348, 212, 8);
    floodfill(348, 212, RED);
    // Press any key to start game... text
    setcolor(BLACK);
    settextstyle(8, 0, 2); // font type, font direction, font size
    outtextxy(100, 260, "Press any key to start game...");
    // Playing main menu sound effect
    PlaySound("main_menu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void player_drawing()
{
    settextstyle(8, 0, 3); // font type, font direction, font size
    setcolor(GREEN);
    outtextxy(110, 370, "Player 1: ");
    setcolor(RED);
    outtextxy(310, 370, "Player 2: ");
}

void display_wins(int p1, int p2, int d)
{
    settextstyle(8, 0, 3); // font type, font direction, font size

    // By player 1
    setcolor(GREEN);
    outtextxy(110, 410, "Wins: ");
    char p1_to_string[10]; // to convert from int to string
    sprintf(p1_to_string, "%d", p1);
    outtextxy(190, 410, p1_to_string);

    // By player 2
    setcolor(RED);
    outtextxy(310, 410, "Wins: ");
    char p2_to_string[10];
    sprintf(p2_to_string, "%d", p2);
    outtextxy(390, 410, p2_to_string);

    // Number of draws
    setcolor(BLACK);
    outtextxy(210, 440, "Draw: ");
    char d_to_string[10];
    sprintf(d_to_string, "%d", d);
    outtextxy(290, 440, d_to_string);
}

int main()
{
    int gd=DETECT;
    int gm;

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE); // setting background color to white
    cleardevice(); // if we not do this, then screen will appear black
    main_menu();

    getch();

    PlaySound(NULL, 0, 0); // Stop the current playing sound

    int p1_wins = 0;
    int p2_wins = 0;
    int draws = 0;
    bool isDraw = false;

    char c;
    while (1)
    {
        setbkcolor(WHITE);
        cleardevice();
        PlaySound(NULL, 0, 0);
        PlaySound("soundtrack.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // Playing sound effect
        clear_board();
        drawBoard();
        player_drawing();
        turn = 1;
        isDraw = false;
        isWon = false;
        display_wins(p1_wins, p2_wins, draws);

        while (1)
        {
            if (turn == 1)
            {
                // If it is player 1's turn, fill player 1 circle with green color
                setcolor(GREEN);
                setfillstyle(SOLID_FILL, GREEN);
                circle(270, 380, 20);
                floodfill(270, 380, GREEN);
                // If it is player 1's turn, fill player 2 circle with white color
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, WHITE);
                circle(470, 380, 20);
                floodfill(470, 380, BLACK);
            }
            else if (turn == 2)
            {
                // If it is player 2's turn, fill player 1 circle with white color
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, WHITE);
                circle(270, 380, 20);
                floodfill(270, 380, BLACK);
                // If it is player 2's turn, fill player 2 circle with red color
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                circle(470, 380, 20);
                floodfill(470, 380, RED);
            }
            c = getch(); // get column name e.g a, b, c, d, e, f, or g from current player

            // this portion is to over write the column filled message with white to make it disappear
            settextstyle(8, 0, 1); // font type, font direction, font size
            setcolor(WHITE);
            outtextxy(340, 140, "This column is filled");
            outtextxy(340, 170, "Choose another one please!");

            if (c == 'a' || c == 'A')
            {
                fillRectangle(5, 0);
            }
            else if (c == 'b' || c == 'B')
            {
                fillRectangle(5, 1);
            }
            else if (c == 'c' || c == 'C')
            {
                fillRectangle(5, 2);
            }
            else if (c == 'd' || c == 'D')
            {
                fillRectangle(5, 3);
            }
            else if (c == 'e' || c == 'E')
            {
                fillRectangle(5, 4);
            }
            else if (c == 'f' || c == 'F')
            {
                fillRectangle(5, 5);
            }
            else if (c == 'g' || c == 'G')
            {
                fillRectangle(5, 6);
            }
            if (isWon == true) // check if current player who took turn won or not
            {
                if (turn == 1)
                {
                    p1_wins++;
                }
                else
                {
                    p2_wins++;
                }
                display_wins(p1_wins, p2_wins, draws);
                break;
            }
            if (checkAllFilled() == true)
            {
                isDraw = true;
                draws++;
                display_wins(p1_wins, p2_wins, draws);
                break;
            }
        }

        if (isDraw == true)
        {
            PlaySound(NULL, 0, 0);
            PlaySound("ending.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            settextstyle(8, 0, 1); // font type, font direction, font size
            setcolor(BLACK);
            outtextxy(380, 100, "It is a draw!");
            outtextxy(380, 130, "Press 'q' to exit");
            outtextxy(380, 160, "or 'n' to start new");
            outtextxy(380, 190, "game");
            char d;
            label: d = getch();
            if (d == 'q' || d == 'Q')
            {
                break;
            }
            else if (d == 'n' || d == 'N')
            {
                continue;
            }
            else
            {
                settextstyle(8, 0, 1); // font type, font direction, font size
                setcolor(RED);
                outtextxy(350, 235, "Please choose 'q' or 'n'!");
                goto label;
            }
        }

        else
        {
            PlaySound(NULL, 0, 0);
            PlaySound("ending.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            settextstyle(8, 0, 1); // font type, font direction, font size
            setcolor(BLACK);

            if (turn == 1)
            {
                outtextxy(380, 100, "Player 1 won!");
            }
            else
            {
                outtextxy(380, 100, "Player 2 won!");
            }
            outtextxy(380, 130, "Press 'q' to exit");
            outtextxy(380, 160, "or 'n' to start new");
            outtextxy(380, 190, "game");
            char d;
            label2: d = getch();
            if (d == 'q' || d == 'Q')
            {
                break;
            }
            else if (d == 'n' || d == 'N')
            {
                continue;
            }
            else
            {
                settextstyle(8, 0, 1); // font type, font direction, font size
                setcolor(RED);
                outtextxy(350, 235, "Please choose 'q' or 'n'!");
                goto label2;
            }
        }
    }

    closegraph();

    return 0;
}