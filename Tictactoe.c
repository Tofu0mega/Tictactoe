#include <stdio.h>
#include <conio.h>
#include <stdlib.h>




//global Variables Used:
char mark[2];                                                        // Mark will be the symbol used by the two players
char slot[10]={'0','1','2','3','4','5','6','7','8','9'};            // Slots will be the boxes used in the game
char playername1[40];                                               // player name one
char playername2[40] = "Computer";                                   // If chosen to play against a bot the default name Computer will be assigned to player 2
int gamestatus=0;                                                       // 0 will be a winner less status 1 signifies player 1 victory 2 signifies player 2 victory
int player=0;                                                           // player will assume values 1 or 2 depending on which player is giving the command
int charchange=0;                                                       // 0 signifies characters are at default symbol 1 signifies characters have been altered
// gamestatus charchange can be reset to 0 values in program to reset to default conditions allowing values to return to default without terminating the program
//Functions used:
//Since most of the function are built to check edit or interpret the global slot[] array They are of void type and take no parameters.
void board();                   // The main module that will be displayed during the game.
void wincheck();             // Checks if the board has a winning condition present.
void winnerdisplay();       // If a winning Condition is seen displays the Winners.
void game(int gamemode);    // where the game takes place in P.V.P. or P.V.C mode according to Gamemode allocated (1 for P.V.P 2 for P.V.C)
void character();           // character select menu.
void end();                 // termination page.

int bot(int choice);        // a alogrithm checks the current conditions of the board and also the last player input to create a appropriate response in the game






/**@brief The board modulle
 *Displays the game board
 @returns nothing
 */

void board()
{
     system("CLS");
     printf("%C | %C | %C\n",slot[1],slot[2],slot[3]);
     printf("----------\n");
     printf("%C | %C | %C\n",slot[4],slot[5],slot[6]);
     printf("----------\n");
     printf("%C | %C | %C\n",slot[7],slot[8],slot[9]);
}

/* board will be shown as
1|2|3
-----
4|5|6
-----
7|8|9
*/



/**@brief The main function
 * This is the entry point of the function.It displays The startup Menu and calls the modules needed according to user input
 * The Flow always returns to this function even if the end of the program is reached until the user asks for termination of program.
 * @returns null
*/



int main()
{
    system("CLS");
    int k =1;// k set the slot index since the values are to be stored as Ascii codes from 49 to 57(1 to 9).
    for( int i = 49; i<=57;i=i+1)//
    {
        slot[k]=i;
        k=k+1;
    }

    /* gamestatus resets to no win condition every time user returns to main menu */

    gamestatus=0;
    /* checks if Characters have been changed or not
    assigns the default value if no change is detected or is in the initial run */
     if (charchange!=0)
     {
        goto menu; /* if user has chosen to change the characters for the tictactoe board and then
                    returns to main function the characterchange is changed to true and defaults are avoided*/
     }
     mark[1]='X';
     mark[2]='O';
     int choice;
     menu:


    printf("Welcome to %c%cc%c%cc%c%c%c\n\n\n\n\n",231,161,231,224,231,229,238);//Shows tictactoe as a Minimal Ascii art(τícταcτσε)
    printf("1. V/S Human \n");
    printf("2. V/S Computer\n");
    printf("3. Change Character\n");

    printf("4. Exit\n");

    printf("Enter Your Choice");

    char get=getch();// Ensures only one character is entered

    choice = get -'0';// changes the character into integer value ( char to int typecasting)


    if ( choice == 1)                   //Switchboard which directs the program flow according to User input.
    {
        game(1);
    }
    else if ( choice == 2)
    {
        game(2);
    }
    else if (choice == 3)
    {
       character();
    }
    else if ( choice ==4)
        end();
    else
    {
        system("cls");
        printf("\nInvalid Answer\n Press any key to continue\n");//error message incase a unsupported value is entered.
        getch();                    //Pauses the flow of program until any button on the keyboard is pressed.
        system("CLS");
        goto menu;
    }
    return 0;
}

/**@brief The game module
    Asks for the Names of the Players Involved.
    Asks for user input and modifies the game board accordingly.Also contains the UI for the data entry.
    @param gamemode ( specifies wether user wishes to play in a PVP mode or PVC mode) is either 1 or 2.
    * has no return.
*/
void game(int gamemode)
{

    // This Section is for Users to Input their Names.
    system("CLS");
    printf("Enter Your Name Player 1\n");
    scanf("%s",playername1);
    if (gamemode==1)// only asks for player 2 name if is in PVP mode
        {
            printf("Enter Your Name Player 2\n");
            scanf("%s",playername2);
        }
    int choice,run;
    system("CLS");
    int i=0;// i counts how many board pieces have been filled by user data.Also allows to determine which player should have control


    while (gamestatus ==0 )//The Main Game loops as long as gamestatus shows no player has won yet. i.e condition 0.
    {
        system("CLS");
        board();

        run= i % 2;// stores the remainder . since is modulated by 2 value is alternating between 1 and 0 in each illitration.

        if(run == 0)// if there are even player pieces control is given to player 1
        {
                player = 1;
        }
        else if ( run!= 0)// if there are odd player pieces control is given to player 2 or bot
        {

            player = 2;
        }


        choicestart:
        system("CLS");
        board();
        if (player == 1 )
        {

            printf("%s 's turn\n ",playername1);
            printf("Enter Your Slot :\n Press Esc to Return to Mainmenu\n");
            char get=getch();
            char escape= 27;
            if ( get == escape)// if the esc key is pressed calls the main module immediately
            {
                 printf("Returning to main menu\n");
                 printf("Press Any key to continue\n");
                 getch();
                 main();
            }

            choice = get -'0';
            if ((slot[choice]==mark[1]|| slot[choice]==mark[2]) || (choice > 9||choice <0))//Invalid User Criteria if number is outofbounds or is already accupied by another player mark.
             {

                 printf("Invalid Choice\n");
                 printf("\n\n Press Any Key To Continue");
                 getch();
                 goto choicestart;
             }
            else// if valid the slot is filled with player mark
            {
                slot[choice]=mark[player];
            }
            board();
        }

        else if(player == 2 )
        {

             printf("%s 's turn \n",playername2);
             if(gamemode==1)// only executes in PVP mode
                {
                     printf("Enter Your Slot :\n Press Esc to Return to Mainmenu\n");
                     char get=getch(); // pauses flow for user input
                     char escape= 27;
                    choice = get -'0';



                     if ( get == escape)
                    {
                         printf("Returning to main menu\n");
                         printf("Press Any key to continue\n");
                         getch();
                         main();
                    }
                }
                else if (gamemode==2)// only executes in PVC mode
                    {
                    choice=bot(choice);
                    }

         if ((slot[choice]==mark[1]|| slot [choice]==mark[2]) || (choice > 9 || choice <0))//criteria check for player 2 input
         {
            printf("Invalid Choice\n");
            printf("\n\n Press Any Key To Continue");
            getch(); // pauses flow for user input
            goto choicestart;
         }

        else
        {
            slot[choice]=mark[player];// assigns the mark to the slot
        }
        board();

        }
        i=i+1;
        wincheck(); winnerdisplay();
        if (i==9 && gamestatus==0)// if the board fills while gamestatus shows no winner a Game Draw Message is displayed
        {
            system("CLS");
            board();
            printf("Its a Draw\n");
            printf("press any key to return to Main Menu");
            getch();
            main();
        }

}






 }



/**@brief The wincheck module
 * Checks if the Criteria for a win has been met
 * has no return.
*/

void wincheck()
{
    //working has been explained in attatched Documentation
    if ( (slot[1]==slot[2] && slot[2]==slot[3] )&& slot[1]==mark[player])
        gamestatus=player;
    else if ( (slot[4]==slot[5] && slot[5]==slot[6] )&& slot[4]==mark[player])
        gamestatus=player;
    else if ( (slot[7]==slot[8] && slot[8]==slot[9] )&& slot[7]==mark[player])
        gamestatus=player;
    else if ( (slot[1]==slot[4] && slot[4]==slot[7] )&& slot [1]==mark[player])
        gamestatus=player;
    else if ( (slot[2]==slot[5] && slot[5]==slot[8] )&& slot [2]==mark[player])
        gamestatus=player;
    else if ( (slot[3]==slot[6] && slot[6]==slot[9] )&& slot [9]==mark[player])
        gamestatus=player;
    else if ( (slot[1]==slot[5] && slot[5]==slot[9] )&& slot [1]==mark[player])
        gamestatus=player;
     else if ( (slot[7]==slot[5] && slot[5]==slot[3] )&& slot [7]==mark[player])
        gamestatus=player;
}
/**@brief The winnerdisplay module
 * Shows who won the game according to game status
 * has no return.
*/
void winnerdisplay()
{


if (gamestatus==1){
    system("CLS");
    board();
    printf("%s has won \n",playername1);
    printf("press any key to return to Main Menu");
    getch(); // pauses flow for user input
    main();
}
else if (gamestatus==2){
system("CLS");
board();
 printf("%s has won \n",playername2);
printf("press any key to return to Main Menu");
 getch();
 main();
}


 }

/**@brief The character selection module
 *  Edits the mark of the characters to their choice from the given options. If both players Choose the same Mark the game changes it back to default.
 * has no return.
*/
void character()
{
    int choice,choice2;
    menuchar:        //Start of player selection of which modification is to be done of.Flow returns here if user inputs invalid values in choices.
    system("CLS");  // Clears the last Screen

    printf("Welcome to the Character Select Menu\n");
    printf("Selection for Player? \n");
    char get=getch(); // pauses flow for user input // Any button selected is stored into get as the character

    choice = get -'0'; // get if integer is type casted into integer if applicable
    if (choice ==1 || choice ==2)//valid responses proceeds the program flow.
        {
            system("CLS");
            menuchar2: // start of character menu. Flow returns here if user inputs invalid values in choices.
            for (int i=1 ; i<=6 ; ++i)// Displays the characters with Ascii values from 1 to 6 namely the houses of cards and smiley faces.
            {
                printf("\n%d. %c ",i,i);
            }
            printf("\n7. X");
            printf("\n8. O\n");
            printf("Enter Your Choice :");
            char get=getch();

            choice2 = get -'0';
            if (choice2 > 8 || choice2 <=0 )//Invalid Criteria Displays Error Message and returns flow to the character menu selection.
                {
                    system("CLS");
                    printf("Invalid Choice");
                    printf("\n\n Press Any Key To Continue");
                    getch();
                    system("CLS");
                    goto menuchar2;

                }
                else if (choice2 >= 1 && choice2 <=6 )// assigns the ascii value to the char data type causing the character to be stored of associated Ascii value.
                        mark[choice]=choice2;
                    else if ( choice2 ==7)
                            mark[choice]='X';
                        else if ( choice2 == 8 )
                            mark[choice]='O';
            system("CLS");
            if( mark[1]==mark[2])// If Both Players choose the same symbol/Mark Characterchange is returned as false causing values to return to default.
            {
                printf("Both Characters cant be the same \n Reset to defaults \n \n\n Press Any Key To Continue");
                charchange=0;
                getch(); // pauses flow for user input
                main();
            }
            printf("Player %d is now %c \n",choice,mark[choice]);
            charchange=1;
            printf("press any key to enter main menu\n");
            getch(); // pauses flow for user input
            main();

        }
    else
        {
            system("ClS");
            printf("\ninvalid answer\n");
            printf("\n\n Press Any Key To Continue\n");
            getch(); // pauses flow for user input
            system("CLS");
            goto menuchar;
        }
}



/**@brief The end module
 * Shows End Message along with details about the developer and Terminates the program
 * has no return.
*/

void end()
{
 system("CLS");
printf("Thankyou For Playing!!!\n");
printf("Made by Yural Pokhrel.\n");
printf("Press Any Key to Exit\n");
getch(); // pauses flow for user input
exit(0);

}

/**@brief The bot function
 * Checks the current status of the board and returns next move according to the encoded algorithm.
 * has no return.
*/
int bot(int choice)
//working has been explained in attached documents.
{
 char value[10];

 for (int i ; i <=9 ; ++i)
 {
if (slot[i]==mark[1] || slot[i]==mark[2])
value[i]='y';

 }


 int flag=0;
 for ( int i=1; i<=3;++i)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==3 && value[3]!='y')
return 3;
 else if (flag==5&& value[1]!='y')
return 1;
 else if ( flag == 4 && value[2]!='y')
return 2;

flag=0;
 for ( int i=4; i<=6;++i)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==9 && value[6]!='y')
return 6;
 else if (flag==11 && value[4]!='y')
return 4;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=7; i<=9;++i)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==15 && value[9]!='y')
return 9;
 else if (flag==17 && value[7]!='y')
return 7;
 else if ( flag == 16 && value[8]!='y')
return 8;




flag=0;
 for ( int i=1; i<=7;i=i+3)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==5 && value[7]!='y')
return 7;
 else if (flag==11 && value[1]!='y')
return 1;
 else if ( flag == 8 && value[4]!='y')
return 4;



flag=0;
 for ( int i=2; i<=8;i=i+3)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==7 && value[8]!='y')
return 8;
 else if (flag==13 && value[2]!='y')
return 2;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=3; i<=9;i=i+3)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==9 && value[9]!='y')
return 9;
 else if (flag==15 && value[3]!='y')
return 3;
 else if ( flag == 12 && value[6]!='y')
return 6;

flag=0;
 for ( int i=1; i<=9;i=i+4)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==6 && value[9]!='y')
return 9;
 else if (flag==14 && value[1]!='y')
return 1;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=3; i<=7;i=i+2)
 {
if (slot[i]==mark[2])
flag=flag+i;

 }
 if (flag==8 && value[7]!='y')
return 7;
 else if (flag==12 && value[3]!='y')
return 3;
 else if ( flag == 10 && value[5]!='y')
return 5;




flag=0;
 for ( int i=1; i<=3;++i)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==3 && value[3]!='y')
return 3;
 else if (flag==5&& value[1]!='y')
return 1;
 else if ( flag == 4 && value[2]!='y')
return 2;

flag=0;
 for ( int i=4; i<=6;++i)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==9 && value[6]!='y')
return 6;
 else if (flag==11 && value[4]!='y')
return 4;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=7; i<=9;++i)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==15 && value[9]!='y')
return 9;
 else if (flag==17 && value[7]!='y')
return 7;
 else if ( flag == 16 && value[8]!='y')
return 8;




flag=0;
 for ( int i=1; i<=7;i=i+3)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==5 && value[7]!='y')
return 7;
 else if (flag==11 && value[1]!='y')
return 1;
 else if ( flag == 8 && value[4]!='y')
return 4;



flag=0;
 for ( int i=2; i<=8;i=i+3)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==7 && value[8]!='y')
return 8;
 else if (flag==13 && value[2]!='y')
return 2;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=3; i<=9;i=i+3)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==9 && value[9]!='y')
return 9;
 else if (flag==15 && value[3]!='y')
return 3;
 else if ( flag == 12 && value[6]!='y')
return 6;

flag=0;
 for ( int i=1; i<=9;i=i+4)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==6 && value[9]!='y')
return 9;
 else if (flag==14 && value[1]!='y')
return 1;
 else if ( flag == 10 && value[5]!='y')
return 5;


flag=0;
 for ( int i=3; i<=7;i=i+2)
 {
if (slot[i]==mark[1])
flag=flag+i;

 }
 if (flag==8 && value[7]!='y')
return 7;
 else if (flag==12 && value[3]!='y')
return 3;
 else if ( flag == 10 && value[5]!='y')
return 5;






int k=0;
 if (value[5] != 'y')
return 5;


int j=0;
 for ( int i =1; i<=9;++i)

 {
        j=j+1;
        if( j>9)
            j=j-9;
        if (slot[i]== mark[2] && value[j]!='y')
        {
                k=i+1;
                if (k >9)
                 k=k-9;


                return k;
        }
 }
 k=0;
for (int i=2;i<=6;i=i+2)
 {
        k=choice+i;
        if (k >9)
        k=k-9;
        if (value[k]!='y')
            return k;
 }
 k=0;
for (int i=1;i<=9;++i)
 {
    k=choice+i;
    if (k >9)
    k=k-9;
    if (value[k]!='y')
    return k;
 }
 return 0;
}







