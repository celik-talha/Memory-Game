#ifdef _WIN32
#include <Windows.h>
const int os = 0;
#else
#include <unistd.h>
const int os = 1;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j,k,t,u,n,m,l,w,b,c,y,v;
int blank = 1;

int mode;
int deck[8][8];
int hidedDeck[8][8];

int memory[16][3];
int memoryIndex=0;

int roundCount = 1;
int playerScore = 0;
int pcScore = 0;

int row,column;
int guess,prevGuess;
int prevRaw,prevColumn;
int nextMove1X,nextMove1Y,nextMove2X,nextMove2Y;
int hidedGuess;
int roundForWin;
int flag = 0;
int limit;
int tempIndex;
int endGame = 0;
int restartKey;
void game();


void createDeck(){
    if (mode == 1)
    {
        for (i = 1; i <= 8; i++)
        {
            for (j = 1; j <=2; j++)
            {
                while (blank == 1)
                {
                    t = rand() % 4;
                    u = rand() % 4;
                
                    if (deck[t][u] == 0)
                    {
                        deck[t][u] = i;
                        blank=0;
                    }
                    else
                    {
                        blank=1;
                    }
                
                }
                blank=1;
            }
        }
        
    }

    else if (mode == 2)
    {
        for (i = 1; i <= 18; i++)
        {
            for (j = 1; j <=2; j++)
            {
                while (blank == 1)
                {
                    t = rand() % 6;
                    u = rand() % 6;
                
                    if (deck[t][u] == 0)
                    {
                        deck[t][u] = i;
                        blank=0;
                    }
                    else
                    {
                        blank=1;
                    }
                
                }
                blank=1;
            }
        }
    }
    else if (mode == 3)
    {
        for (i = 1; i <= 32; i++)
        {
            for (j = 1; j <=2; j++)
            {
                while (blank == 1)
                {
                    t = rand() % 8;
                    u = rand() % 8;
                
                    if (deck[t][u] == 0)
                    {
                        deck[t][u] = i;
                        blank=0;
                    }
                    else
                    {
                        blank=1;
                    }
                
                }
                blank=1;
            }
        }

    }
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            hidedDeck[i][j]=0;
        }
        
    }
    
    
}
void showDeck(){

    if (mode == 1)
    {
        printf("\n");
        for (n = 0; n <4; n++)
        {
           for (m = 0; m < 4; m++)
            {
                printf(" %d",deck[n][m]);
            }
        printf("\n");
        }
    }

    else if (mode == 2)
    {
        printf("\n");
        for (n = 0; n <6; n++)
        {
           for (m = 0; m < 6; m++)
            {
                if (deck[n][m] >= 10)
                {
                    printf("%d  ",deck[n][m]);
                }
                else{
                    printf("%d   ",deck[n][m]);
                }
                
            }
        printf("\n");
        }
    }

    else if (mode == 3)
    {
        printf("\n");
        for (n = 0; n <8; n++)
        {
           for (m = 0; m < 8; m++)
            {
                if (deck[n][m] >= 10)
                {
                    printf("%d  ",deck[n][m]);
                }
                else{
                    printf("%d   ",deck[n][m]);
                }
                
            }
        printf("\n");
        }
    }
    printf("\nMemory: ");
    for (v = 0; v < limit; v++)
    {
        printf("%d  ",memory[v][0]);
    }
    printf("\n");
    
}
void showHidedDeck(){

    if (mode == 1)
    {
        printf("\n");
        for (n = 0; n <4; n++)
        {
           for (m = 0; m < 4; m++)
            {
                if (hidedDeck[n][m] == 0)
                {
                    printf(" *");
                }
                else if (hidedDeck[n][m] == -1)
                {
                    printf(" -");
                }
                else
                {
                    printf(" %d",hidedDeck[n][m]);
                }
            }
        printf("\n");
        }
    }

    else if (mode == 2)
    {
        printf("\n");
        for (n = 0; n <6; n++)
        {
           for (m = 0; m < 6; m++)
            {
                if (hidedDeck[n][m] == 0)
                {
                    printf("  *");
                }
                else if (hidedDeck[n][m] == -1)
                {
                    printf("  -");
                }
                else
                {
                    if (hidedDeck[n][m] >= 10)
                    {
                    printf(" %d",hidedDeck[n][m]);
                    }
                    else{
                    printf("  %d",hidedDeck[n][m]);
                    }
                }
                
            }
        printf("\n");
        }
    }

    else if (mode == 3)
    {
        printf("\n");
        for (n = 0; n <8; n++)
        {
           for (m = 0; m < 8; m++)
            {
                if (hidedDeck[n][m] == 0)
                {
                    printf("  *");
                }
                else if (hidedDeck[n][m] == -1)
                {
                    printf("  -");
                }
                else
                {
                    if (hidedDeck[n][m] >= 10)
                    {
                    printf(" %d",hidedDeck[n][m]);
                    }
                    else{
                    printf("  %d",hidedDeck[n][m]);
                    }
                }
                
            }
        printf("\n");
        }
    }
    
    
}
void clearScreen(){
    printf("\n");
    if (os == 0)
    {
        system("cls");
    }
    else if (os == 1)
    {
        system("clear");
    }
    showDeck();
    
}
void hide(int a, int b){
    hidedDeck[a][b]=0;
}
void foundDeck(int r, int f)
{
    hidedDeck[r][f]=-1;
}
void unHide(int c,int d){
    hidedDeck[c][d]=deck[c][d];
}
void addToMemory(int x,int y){

    if (mode == 1)
    {
        if (memoryIndex == 1)
        {
            memory[0][0] = deck[x][y];
            memory[0][1] = x;
            memory[0][2] = y;
            memoryIndex = 0;
        }
        else{
            memory[1][0] = deck[x][y];
            memory[1][1] = x;
            memory[1][2] = y;
            memoryIndex = 1;
        }
    }
    else if (mode == 2)
    {
        if (memoryIndex == 5)
        {
            memory[0][0] = deck[x][y];
            memory[0][1] = x;
            memory[0][2] = y;
            memoryIndex=0;
        }
        else{
            memory[memoryIndex + 1][0]= deck[x][y];
            memory[memoryIndex + 1][1] = x;
            memory[memoryIndex + 1][2] = y;
            memoryIndex = memoryIndex + 1;
        }
    }
    else if (mode == 3)
    {
        if (memoryIndex == 15)
        {
            memory[0][0] = deck[x][y];
            memory[0][1] = x;
            memory[0][2] = y;
            memoryIndex=0;
        }
        else{
            memory[memoryIndex + 1][0]= deck[x][y];
            memory[memoryIndex + 1][1] = x;
            memory[memoryIndex + 1][2] = y;
            memoryIndex = memoryIndex + 1;
        }
    }
    
}
int checkMemory(int turn){
    if (turn == 0)
    {
        if (mode == 2 || mode == 3)
        { 
            for (b = 0; b <= limit-2; b++)
            {
                for (c = b+1; c <= limit-1; c++)
                {
                    if (memory[c][0] == memory[b][0] && memory[c][0] != 0)
                    {
                        if (memory[c][1] != memory[b][1] || memory[c][2] != memory[b][2])
                        {
                            nextMove1X=memory[c][1];
                            nextMove1Y=memory[c][2];
                            nextMove2X=memory[b][1];
                            nextMove2Y=memory[b][2];
                            memory[c][0]=0;
                            memory[b][0]=0;
                            return 1;
                        }
                    
                    }
                }
            
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (mode == 1)
        {
            if (memoryIndex == 0)
            {
                tempIndex = 1;
            }
            else if(memoryIndex == 1)
            {
                tempIndex = 0;
            }
            
            if (memory[tempIndex][0] == prevGuess)
            {
                nextMove1X=memory[tempIndex][1];
                nextMove1Y=memory[tempIndex][2];
                return 1;
            }
            else
            {
                return 0;
            }

        }

        if (mode == 2 || mode == 3)
        {
            for (i = 0; i <limit; i++)
            {
                if (guess == memory[i][0])
                {
                    if (row != memory[i][1] && column != memory[i][2])
                    {
                        nextMove1X=memory[i][1];
                        nextMove1Y=memory[i][2];
                        return 1;
                    }
                    
                }
                
            }
            return 0;
        }
        else
        {
            printf("Invalid mode");
            return 3;
        }
        
    }
    
    
}
void clearFromMemory(int number,int xRow,int xColumn)
{
    for (y = 0; y < limit; y++)
    {
        if (memory[y][0] == number)
        {
            if (memory[y][1] == xRow && memory[y][2] == xColumn)
            {
                memory[y][0] = 0;
                memory[y][1] = 0;
                memory[y][2] = 0;
            }
            
        }
        
    }
} 
void playerTurn(){
    clearScreen();
    printf("\n\n%d. Round",roundCount);
    printf("\nYour Turn");
    for (l = 1; l<= 2; l++)
    {
        printf("\nPlease enter row number for your %d.guess :",l);
        scanf("%d",&row);

        printf("\nPlease enter column number for your %d.guess :",l);
        scanf("%d",&column);
        row--;
        column--;
        guess = deck[row][column];
        unHide(row,column);
        showHidedDeck();
        addToMemory(row,column);
        if (l == 1)
        {
            prevRaw = row;
            prevColumn = column;
            prevGuess = guess;
            sleep(2);
        }
        if (l == 2)
        {
            if (guess == prevGuess)
            {

                playerScore++;
                printf("\nYou found right! You have %d points.",playerScore);
                foundDeck(prevRaw,prevColumn);
                foundDeck(row,column);
                sleep(2);
                clearFromMemory(guess,row,column);
                clearFromMemory(prevGuess,prevRaw,prevColumn);
            }
            else
            {
                hide(row,column);
                hide(prevRaw,prevColumn);
            }
            sleep(2);
        }
        
    }
}
void pcTurn(){
    clearScreen();
    printf("\nComputer's Turn");
    if (checkMemory(0) == 1)
    {
        printf("\nFirst guess of AI:");
        unHide(nextMove1X,nextMove1Y);
        showHidedDeck();
        sleep(3);
        printf("\nSecond guess of AI:");
        unHide(nextMove2X,nextMove2Y);
        showHidedDeck();
        sleep(1);
        foundDeck(nextMove1X,nextMove1Y);
        foundDeck(nextMove2X,nextMove2Y);
        pcScore++;
        printf("\nPc found right! Now it has %d points",pcScore);
        clearFromMemory(deck[nextMove1X][nextMove1Y],nextMove1X,nextMove1Y);
        clearFromMemory(deck[nextMove2X][nextMove2Y],nextMove2X,nextMove2Y);
    }
    else
    {
        for (w = 1; w <=2; w++)
        {
            while (flag == 0)
            {
                
                if (mode == 1)
                {
                    row = rand() % 4;
                    column = rand() % 4;
                }
                else if (mode == 2)
                {
                    row = rand() % 6;
                    column = rand() % 6;
                }
                else
                {
                    row = rand() % 8;
                    column = rand() % 8;
                }
    
                hidedGuess=hidedDeck[row][column];
                if (hidedGuess == 0)
                {   
                    guess=deck[row][column];
                    flag = 1;
                    if (w == 1)
                    {
                        printf("\nFirst guess of AI:");
                        unHide(row,column);
                        showHidedDeck();
                        addToMemory(row,column);
                        prevRaw=row;
                        prevColumn=column;
                        prevGuess=guess;
                        sleep(3);

                        if (checkMemory(1) == 1)
                        {
                            printf("\nSecond guess of AI:");
                            unHide(nextMove1X,nextMove1Y);
                            pcScore++;
                            printf("\nPc found right! Now it has %d points",pcScore);
                            foundDeck(row,column);
                            foundDeck(nextMove1X,nextMove1Y);
                            clearFromMemory(guess,row,column);
                            clearFromMemory(deck[nextMove1X][nextMove1Y],nextMove1X,nextMove1Y);
                            flag = 1;
                            sleep(3);
                            
                        }
                    }
                    else if (w == 2)
                    {    
                        printf("\nSecond guess of AI:");
                        unHide(row,column);
                        showHidedDeck();
                        addToMemory(row,column);                    
                        if (prevGuess == guess)
                        {
                            pcScore++;
                            printf("\nPc found right! Now it has %d points",pcScore);
                            clearFromMemory(guess,row,column);
                            clearFromMemory(prevGuess,prevRaw,prevColumn);
                            foundDeck(prevRaw,prevColumn);
                            foundDeck(row,column);
                        }
                        else
                        {
                            hide(prevRaw,prevColumn);
                            hide(row,column);
                        }
                        sleep(2);
                    }
                }
            }
            flag = 0;
        
        }
    }
    sleep(5);
}
void restartGame(){
    printf("\nType 1 to play again. ");
    scanf("%d",&restartKey);
    if (restartKey == 1)
    {
        blank = 1;
        memoryIndex=0;
        roundCount = 1;
        playerScore = 0;
        pcScore = 0;
        flag = 0;
        endGame = 0;
        game();
    }
}
void game(){
    printf("\nWelcome to the game, Please type 1 for easy, 2 for normal, 3 for hard mode :");
    scanf("%d",&mode);
    if (mode == 2)
    {
        limit = 6;
    }
    else if (mode == 3)
    {
        limit = 8;
    }
    
    createDeck();
    showDeck();
    if (mode == 1)
    {
        roundForWin = 5;
    }
    else if(mode == 2)
    {
        roundForWin = 10;
    }
    else
    {
        roundForWin = 17;
    }
    
    while (endGame == 0)
    {
        if ( playerScore == roundForWin-1 && pcScore == roundForWin-1 )
        {
            printf("\nTie!");
            restartGame();
            
        }
        else if (playerScore >= roundForWin)
        {
            printf("\nYou won after %d rounds!",roundCount);
            restartGame();
        }
        else if (pcScore >= roundForWin)
        {
            printf("\nPc won after %d rounds!",roundCount);
            restartGame();
        }
        else
        {
            playerTurn();
            pcTurn();
            roundCount++;
        }
        
    }
    
}
int main(){
    clearScreen();
    srand(time(NULL));
    game();
    return 0;
}
