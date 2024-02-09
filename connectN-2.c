// By Paramroop Parmar, Gurjevan Bhatti
// date 2023-07-05  
// The objective of the assigment is to use array, functions, and loops. to make a game called connect the 4.
// Using array index manipulation to make the game as authentuic as the real version

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // the libaries needed
const int MAXSIZE = 25;
const int MINSIZE = 8;
const int MINCONNECTNUM = 4;  // global constants

int initializeBoard(int** connectNBoard, int numRowsinBoard);  // the prototypes 
int MakeMove(int** connectNBoard, int numRowsinBoard, int playerID, int columnChosen);
int DisplayBoard(int** connectNboard, int numRowsInBoard);
int CheckWinner (int** connectNBoard, int numRowsinBoard, int playerID, int columnChosen,int numConnect); 

int main()
{
    char c;
    int numRows; //intiliaze  varibles
    
    
    while(1)  // loop thats asks for boards size
    {
        printf("Enter the number of squares along each edge of board \n");
        if (scanf("%d",&numRows) != 1) // check if not num
        {
            printf("ERROR: The value provided was not an integer\n");
        }
        else if (numRows > MAXSIZE ) // if larger than range
        {
            printf("ERROR: Board size too large (>%d) \n",MAXSIZE);
        }
        else if (numRows < MINSIZE ) // if less than num range
        {
           printf( "ERROR: Board size too small (<%d)\n",MINSIZE);

        }
        if (numRows <= MAXSIZE && numRows >= MINSIZE)  // the range and breaks while loop
        {
            while ((c = getchar()) != '\n'){} // clear buffer
            break;
        }

        while ((c = getchar()) != '\n'){} // clear buffer
    }
   
   // prompt for numbers in a row to win
   int numToConnect;
   char cc; // intialize for num rows to win 
    
   while(2) // check if empty
   {
        printf("Enter the number of pieces that must form a line to win\n");
        if(scanf("%d",&numToConnect) != 1)
        {
            printf("ERROR: The value provided was not an integer\n");
        }
        else if (numToConnect < MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too small (<%d)\n",MINCONNECTNUM);
        }
        else if (numToConnect > numRows-1)
        {
            printf("ERROR: Number to connect is too large (>%d)\n",numRows-MINCONNECTNUM);
        }
        else if (numToConnect >= MINCONNECTNUM && numToConnect <= numRows-MINCONNECTNUM)
        {
            break;
            while ((cc = getchar()) != '\n'){}
        }
        while ((cc = getchar()) != '\n'){}
        
   }
   
    // intialize the allocate board for numrows
    int**myConnectNBoard = NULL;
        myConnectNBoard = (int**)malloc(numRows* sizeof(int*));
    for (int i = 0; i < numRows; i++)
    {
        myConnectNBoard[i] = (int*)malloc(numRows* sizeof(int));
    }
    // intialize board to zero, and check if allocated
    int checker;
    checker = initializeBoard(myConnectNBoard,numRows);
    if (checker == 0)
    {
        return -1;
    } 
    
    checker = DisplayBoard(myConnectNBoard,numRows); // print board
    if (checker == 0)
    {
        return -1;
    }
    

    int winner; // the varibles needed for the game
    int player_turns = 0; // check whos turn it is
    int playersmove; // stores the move of current player
    int key;
    int movechecker;
    char m;
    while (winner != 1) // while loop for the game.
    {
        key = 0;
        if (player_turns % 2 == 0) // uses even or odd to determine whos the winner and perint whose turn
        {
            printf("Red moves\n");
        }
        else
        {
            printf("Black moves\n");
        }
        // get players input, 3 chances

        for (int i = 0; i < 3; i++) // ask for players move // for loop for 3 tries
        {
           
            printf("Enter the column number where you want to put your piece\n");
         
            if (scanf("%d",&playersmove) != 1) // check if number
            {
                printf("ERROR: The value provided was not a number\n");
            }
            else if (playersmove < 0 || playersmove >= numRows) // check if out of range
            {
                printf("ERROR: Column %d is not on the board: try again\n",playersmove);
                printf("ERROR: Column number should be >= 0 and < %d\n",numRows);
            }
            else if (myConnectNBoard[0][playersmove] != 0) // check if column is full
            {
               printf("ERROR: Column %i is already completely full try again\n",playersmove); 
            }
            else if (playersmove >= 0 && playersmove < numRows) // num is correct and clear the buffer and give key
            {
                while ((m = getchar()) != '\n'){}
                key = 2;
                break;
            }
            if  (i == 2) // check if player forfeits turn
            {
                printf("TOO MANY ILLEGAL MOVES\n");
                if (player_turns % 2 == 0)
                {
                    printf("Red has forfeited a turn\n");
                }
                else
                {
                    printf("Black has forfeited a turn\n");
                }
            }
         while ((c = getchar()) != '\n'){} // clear buffer  
        } // end of for loop



        if (key == 2) // value has key
        {
        movechecker = MakeMove(myConnectNBoard,numRows, player_turns,playersmove); // puts move in game
        winner = CheckWinner( myConnectNBoard, numRows, player_turns, playersmove, numToConnect); // check if win
        }

         if (player_turns == numRows*numRows && winner !=1) // if draw
        {
        printf("Its a Draw\n");
        for (int i = 0; i < numRows; i++)    // clean up
            {
                free(myConnectNBoard[i]);
            }
        free(myConnectNBoard);
        return 1;
        }


        if (winner == 1) // prints winner for corresponding player
        {
            if (player_turns % 2 == 0)
            {
                printf("Red has won");
            }
            else
            {
                printf("black has won");
            }
        }
        printf("\n");
        checker = DisplayBoard(myConnectNBoard,numRows); // print board

        player_turns++;  
    } // while loop for main game end

   
    for (int i = 0; i < numRows; i++)    // clean up
    {
        free(myConnectNBoard[i]);
    }
    free(myConnectNBoard);
    return 0;
} // main function




int initializeBoard(int** connectNBoard, int numRowsinBoard) // makes board to 0
{


    if ((numRowsinBoard < MINSIZE || numRowsinBoard > MAXSIZE)) // check if out of range
    {
        printf("ERROR: illegal number of rows in board");
        return false;
    }
    for (int i = 0; i < numRowsinBoard; i++) // makes board to 0
    {
        for (int m = 0; m < numRowsinBoard; m++)
        {
           connectNBoard[i][m] = 0;
        }
        
    }
    if (connectNBoard == NULL) // ckeck if board is null
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL \n");
        return false;
    }
    else
    {
        return true;
    }
}

int DisplayBoard(int** connectNBoard, int numRowsInBoard ) // check if values in range and allocated first, then print board
{
        if ((numRowsInBoard < MINSIZE || numRowsInBoard > MAXSIZE))
    {
        printf("ERROR: illegal number of rows in board");
        return false;
    }
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL \n");
        return false;
    }
    printf("   "); // for first row spacing
    for (int i = 0; i < numRowsInBoard; i++)
    {
        printf("%3d",i); // to add the numbers
    }
    printf("\n");

    for (int i = 0; i < numRowsInBoard; i++) // printd board
    { 
        printf("%3d",i);
        for (int j = 0; j < numRowsInBoard; j++)
        {
            if (connectNBoard[i][j] == 0)
            {
                printf("%3c",'o'); // if entry 0

            }
            else if (connectNBoard[i][j] == 1) // if entry 1
            {
                printf("%3c",'R');
            }
            else if (connectNBoard[i][j] == 2) // if entry 2
            {
                printf("%3c",'B');
            }
            
        }
        printf("\n");
        
    }
    return true;
}


int MakeMove(int** connectNBoard, int numRowsInBoard, int playeID,int columnChosen) // adds move to array
{
    if (connectNBoard == NULL) // check if array is null
    {
        printf("ERROR: cannot print the board because the pointer to the board is NULL\n");
        return false;
    }
    if (columnChosen >= numRowsInBoard || columnChosen < 0) // check if out of range
    {
        printf("illegal Move\n");
        return false;
    }
    int count = 1;
    while(true) // adds the chosen coloumn value to bottom of array
    {
        if (connectNBoard[numRowsInBoard-count][columnChosen] == 0)
        {
            if (playeID % 2 == 0)
            {
                connectNBoard[numRowsInBoard-count][columnChosen] = 1;
                printf("Red has moved\n");
            }
            else
            {
                connectNBoard[numRowsInBoard-count][columnChosen] = 2;
                printf("Black has moved\n");
            }
            return true;

        }
        count++;
    }

}

int CheckWinner(int** connectNBoard, int numRowsinBoard, int playerID, int columnChosen,int numConnect) // 1.even -> red, 2.odd -> black
{
    if (connectNBoard == NULL) // check if to NULL
    {
        printf("ERROR: cannot print the board because the pointer to the board is NULL\n");
        return false;
    }
    if (columnChosen >= numRowsinBoard || columnChosen < 0) // invaild option
    {
        printf("ERROR: invalid column chosen, cannot check for winner \n");
        return false;
    }
    int player = playerID % 2; // caculate player id, values
    int count = 0; 
    int newrow;
    
    while(1) // determine row new game piece 
    {
        if (connectNBoard[count][columnChosen] != 0)
        {
            newrow = count;
           break;
        }
        count++;
    } 
    
    
    int beforeCount = 0, afterCount = 0;  // check if row win
    if (player == 0) // red
    { 
        
        for (int i = columnChosen; i >= 0; i--) // row left 
        {
            if (connectNBoard[newrow][i] != 1)
            {
                break;
            }
            else if (connectNBoard[newrow][i] == 1)
            {
                beforeCount++;

            }
            
        }
        for (int i = columnChosen; i <= numRowsinBoard; i++) // row right
        {
            if (connectNBoard[newrow][i] != 1)
            {
                break;
            }
            else if (connectNBoard[newrow][i] == 1)
            {
                afterCount++;
            }
            
        }
        if (afterCount + beforeCount -1 >= numConnect) // check if win
        {
            return true;
        }


        
        
        beforeCount = 0, afterCount = 0;  // column win
        for (int i = 0; i < numRowsinBoard; i++) // column down
        {
           
            if (newrow + i == numRowsinBoard||connectNBoard[newrow+i][columnChosen] != 1)
            {
                break;
            }
            else if (connectNBoard[newrow+i][columnChosen] == 1)
            {
                beforeCount++;
               
            }
            
        }
            
        
        if (afterCount + beforeCount  >= numConnect) // check win
            {
                
                return true;
            }
        
        
        /* diagonal this way -> /                               */
        afterCount = 0, beforeCount = 0;
        for (int i = 0; i<numRowsinBoard; i++ ) // right & up right  & up right & up
        {
            
            if ( newrow +i == numRowsinBoard || i + columnChosen == numRowsinBoard || connectNBoard[newrow + i][columnChosen + i] != 1 )
            {
                break;
            }
            else if (connectNBoard[newrow + i][columnChosen + i] == 1)
            {
                beforeCount++;
            }
        }
       
        for (int i = 0; i < numRowsinBoard; i++) // left & down  left & down left & down
        {
            if (connectNBoard[newrow - i][columnChosen - i] != 1 || newrow - i == -1 ||   columnChosen - i == -1)
            {
                break;
            }
            else if (connectNBoard[newrow - i][columnChosen - i] == 1)
            {
                afterCount++;
            }
        }
        if (afterCount + beforeCount -1 >= numConnect) // check if win
            {
                return true;
            } 

       
        afterCount = 0, beforeCount = 0; // now its diagonal left up -> right down
        for (int i = 0; i < numRowsinBoard; i++)
        {
            if ( newrow + i == numRowsinBoard ||   columnChosen - i == -1 || connectNBoard[newrow + i][columnChosen - i] != 1 ) // left & up, left & up
            {
                break;
            } 
            else if (connectNBoard[newrow + i][columnChosen - i] == 1)      
            {
                beforeCount++;
            }    
        }
     
        for (int i = 0; i < numRowsinBoard; i++)
        {
            if ( newrow - i == -1 ||   columnChosen + i == numRowsinBoard || connectNBoard[newrow - i][columnChosen + i] != 1 )
            {
                break;
            } 
            else if (connectNBoard[newrow - i][columnChosen + i] == 1)      
            {
                beforeCount++;
            }    
        } 
        if (afterCount + beforeCount -1 >= numConnect) // check if win
            {
                return true;

            }   
                 
    } //-- end of red
    


      else // BLACK
    { 
         
        for (int i = columnChosen; i >= 0; i--) // row left 
        {
            if (connectNBoard[newrow][i] != 2)
            {
                break;
            }
            else if (connectNBoard[newrow][i] == 2)
            {
                beforeCount++;
            }
            
        }
        for (int i = columnChosen; i <= numRowsinBoard; i++) // row right
        {
            if (connectNBoard[newrow][i] != 2)
            {
                break;
            }
            else if (connectNBoard[newrow][i] == 2)
            {
                afterCount++;
            }
            
        }
        if (afterCount + beforeCount -1 >= numConnect) // check if win
        {
            return true;
        }


        
        
        beforeCount = 0, afterCount = 0;  // column win
        for (int i = 0; i < numRowsinBoard; i++) // column down
        {
           
            if (newrow + i == numRowsinBoard||connectNBoard[newrow+i][columnChosen] != 2)
            {
                break;
            }
            else if (connectNBoard[newrow+i][columnChosen] == 2)
            {
                beforeCount++;
               
            }
            
        }
                   
        if (afterCount + beforeCount  >= numConnect) // check win
            {
                
                return true;
            }
        
        
       
        /* diagonal this way -> /                               */
        afterCount = 0, beforeCount = 0;
        for (int i = 0; i<numRowsinBoard; i++ ) // right & up right  & up right & up
        {
            
            if ( newrow +i == numRowsinBoard || i + columnChosen == numRowsinBoard || connectNBoard[newrow + i][columnChosen + i] != 2 )
            {
                break;
            }
            else if (connectNBoard[newrow + i][columnChosen + i] == 2)
            {
                beforeCount++;
            }
        }
     
        for (int i = 0; i < numRowsinBoard; i++) // left & down  left & down left & down
        {
            if ( newrow - i == -1 ||   columnChosen - i == -1 || connectNBoard[newrow - i][columnChosen - i] != 2 )
            {
                break;
            }
            else if (connectNBoard[newrow - i][columnChosen - i] == 2)
            {
                afterCount++;
            }
        }
        if (afterCount + beforeCount -1 >= numConnect) // check if win
            {
                return true;
            } 

        
        afterCount = 0, beforeCount = 0; // now its diagonal left up -> right down
        for (int i = 0; i < numRowsinBoard; i++)
        {
            if ( newrow + i == numRowsinBoard ||   columnChosen - i == -1 || connectNBoard[newrow + i][columnChosen - i] != 2 ) // left & up, left & up
            {
                break;
            } 
            else if (connectNBoard[newrow + i][columnChosen - i] == 2)      
            {
                beforeCount++;
            }    
        }
         
        for (int i = 0; i < numRowsinBoard; i++)
        {
            if ( newrow - i == -1 ||   columnChosen + i == numRowsinBoard || connectNBoard[newrow - i][columnChosen + i] != 2 )
            {
                break;
            } 
            else if (connectNBoard[newrow - i][columnChosen + i] == 2)      
            {
                beforeCount++;
            }    
        } 
        if (afterCount + beforeCount -1 >= numConnect) // check if win
            {
                return true;

            }   
    }

    return false; // if no win return false
}
