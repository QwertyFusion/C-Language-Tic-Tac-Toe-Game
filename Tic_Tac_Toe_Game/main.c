// TIC TAC TOE GAME CODE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define CYAN_FORMAT "\033[36;1m"
#define LIGHT_YELLOW_FORMAT "\033[33;1m"
#define RED_FORMAT "\033[31m"
#define GREEN_FORMAT "\033[32m"
#define WHITE_FORMAT "\033[0;1m"

char board[3][3], player = ' ', computer = ' ', winner = ' ', response = ' ', response2 = ' ';
int round = 1, wins = 0, loses = 0, draws = 0, gameNumber = 0, totalGames = 0, temp = 0;

void ResetBoard();
void PrintBoard();
int CheckFreeSpaces();
void PlayerMove();
void ComputerMove();
char CheckWinner();
void PrintWinner(char);

void main()
{
   int l; // l = Loop Variable

   printf("%s", WHITE_FORMAT);
   DisplayFormatting();
   printf("\n\t\n");
   printf("\t\t      %sWELCOME TO %sTIC TAC TOE GAME%s IN %sC%s\n\n", LIGHT_YELLOW_FORMAT, CYAN_FORMAT, LIGHT_YELLOW_FORMAT, CYAN_FORMAT, WHITE_FORMAT);
   DisplayFormatting();
   printf("\n\n\t\t\t%sDEVELOPED BY %sRISHI BANERJEE%s\n\n", LIGHT_YELLOW_FORMAT, CYAN_FORMAT, WHITE_FORMAT);
   DisplayFormatting();
   printf("\n\n%sPLEASE ENTER %sANY KEY %sTO CONTINUE", LIGHT_YELLOW_FORMAT, RED_FORMAT, LIGHT_YELLOW_FORMAT);

   Sleep(500);
   for (l = 0; l < 5; l++)
   {
      printf(".");
      Sleep(500); // after printing one . another comes after 0.5 seconds
   }

   getch();

   PlayerSelection();

   printf("\n\n%sPLEASE ENTER %sANY KEY %sTO START", LIGHT_YELLOW_FORMAT, RED_FORMAT, LIGHT_YELLOW_FORMAT);

   for (l = 0; l < 5; l++)
   {
      printf(".");
      Sleep(500);
   }

   fflush(stdin);
   getch();
   system("cls");
   if (player == 'X')
   {
      StartWithPlayer();
   }
   else
   {
      StartWithComputer();
   }

   EndScreen();
}

void StartWithPlayer()
{
   system("color 0b"); // 1st is for back ground color and second is for text color
   winner = ' ';
   response = ' ';
   ResetBoard();

   while (winner == ' ' && CheckFreeSpaces() != 0)
   {
      // PLAYER TURN
      system("cls");
      system("color 0b");
      printf("Round %d\t\t\t\t\t\t\t\t       Your Turn\n", round);
      PrintBoard();
      PlayerMove();

      // PLAYER TURN RESULT
      system("cls");
      system("color 0b");
      printf("Round %d Result\t\t\t\t\t\t\tYour Turn Result\n", round++);
      PrintBoard();
      system("pause");
      fflush(stdin);

      winner = CheckWinner();
      if (winner != ' ' || CheckFreeSpaces() == 0)
      {
         break;
      }

      // COMPUTER TURN
      system("cls");
      system("color 0c");
      printf("Round %d\t\t\t\t\t\t\t\t    Enemy's Turn\n", round++);
      ComputerMove();
      PrintBoard();
      system("pause");
      fflush(stdin);
      winner = CheckWinner();
      if (winner != ' ' || CheckFreeSpaces() == 0)
      {
         break;
      }
   }

   ResultScreen();
}

void StartWithComputer()
{
   system("color 0c"); // 1st is for back ground color and second is for text color
   winner = ' ';
   response = ' ';
   ResetBoard();

   while (winner == ' ' && CheckFreeSpaces() != 0)
   {
      // COMPUTER TURN
      system("cls");
      system("color 0c");
      printf("Round %d\t\t\t\t\t\t\t\t    Enemy's Turn\n", round++);
      ComputerMove();
      PrintBoard();
      system("pause");
      fflush(stdin);
      winner = CheckWinner();
      if (winner != ' ' || CheckFreeSpaces() == 0)
      {
         break;
      }

      // PLAYER TURN
      system("cls");
      system("color 0b");
      printf("Round %d\t\t\t\t\t\t\t\t       Your Turn\n", round);
      PrintBoard();
      PlayerMove();

      // PLAYER TURN RESULT
      system("cls");
      system("color 0b");
      printf("Round %d Result\t\t\t\t\t\t\tYour Turn Result\n", round++);
      PrintBoard();
      system("pause");
      fflush(stdin);

      winner = CheckWinner();
      if (winner != ' ' || CheckFreeSpaces() == 0)
      {
         break;
      }
   }

   ResultScreen();
}

void ResetBoard()
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         board[i][j] = ' ';
      }
   }
}
void PrintBoard()
{
   time_t t;   //importing time
   time(&t);
   printf("Your sign: %c\t\t\t\t\t\t\tComputer Sign: %c\n", player, computer);
   printf("Total Games: %d\n", totalGames);
   printf("%s\n", ctime(&t));
   DisplayFormatting();
   printf("\n\n\t\t\t\t  %c \xdb\xdb %c \xdb\xdb %c \n", board[0][0], board[0][1], board[0][2]);
   printf("\t\t\t\t ");
   for (int l = 0; l < 13; l++)
   {
      printf("\xdb");
   }
   printf("\n\t\t\t\t  %c \xdb\xdb %c \xdb\xdb %c \n", board[1][0], board[1][1], board[1][2]);
   printf("\t\t\t\t ");
   for (int l = 0; l < 13; l++)
   {
      printf("\xdb");
   }
   printf("\n\t\t\t\t  %c \xdb\xdb %c \xdb\xdb %c \n", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}
int CheckFreeSpaces()
{
   int freeSpaces = 9;

   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (board[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}
void PlayerMove()
{
   int x;
   int y;

   do
   {
      printf("Enter row Number (1-3): ");
      scanf("%d", &x);
      x--;
      printf("Enter column Number (1-3): ");
      scanf("%d", &y);
      y--;

      if (board[x][y] != ' ')
      {
         printf("Invalid move!\n");
      }
      else
      {
         board[x][y] = player;
         break;
      }
   } while (board[x][y] != ' ');
}
void ComputerMove()
{
   // creates a seed based on current time
   srand(time(0));
   int x;
   int y;

   if (CheckFreeSpaces() > 0)
   {
      do
      {
         x = rand() % 3;
         y = rand() % 3;
      } while (board[x][y] != ' ');

      board[x][y] = computer;
   }
   else
   {
      PrintWinner(' ');
   }
}
char CheckWinner()
{
   // check rows
   for (int i = 0; i < 3; i++)
   {
      if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
      {
         return board[i][0];
      }
   }
   // check columns
   for (int i = 0; i < 3; i++)
   {
      if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
      {
         return board[0][i];
      }
   }
   // check diagonals
   if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
   {
      return board[0][0];
   }
   if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
   {
      return board[0][2];
   }

   return ' ';
}
void PrintWinner(char winner)
{
   if (winner == player)
   {
      printf("YOU WIN!");
   }
   else if (winner == computer)
   {
      printf("YOU LOSE!");
   }
   else
   {
      printf("IT'S A TIE!");
   }
}

void DisplayFormatting()
{
   for (int l = 0; l < 80; l++)
   {
      printf("\xdb");
   }
}

void PlayerSelection()
{
   char ch;
   system("cls"); // clears the screen
   printf("\n%s", WHITE_FORMAT);
   DisplayFormatting();
   printf("\n\n\t\t\t\t%sTIC TAC TOE GAME%s\n\n", CYAN_FORMAT, WHITE_FORMAT);
   DisplayFormatting();
   printf("\n\n%s[NOTE: X goes first]%s", RED_FORMAT, LIGHT_YELLOW_FORMAT);
   printf("\nWho you want to play as? %s(X or O):%s ", CYAN_FORMAT, LIGHT_YELLOW_FORMAT);
   scanf("%c", &player);
   player = toupper(player);
   if (player == 'X')
   {
      computer = 'O';
   }
   else if (player == 'O')
   {
      computer = 'X';
   }
   else
   {
      MessageBox(0, "Invalid Selection!\nPlease choose between X or O.\nEnter Again...", "Error!", 0);
      fflush(stdin);
      PlayerSelection();
   }

   fflush(stdin);
   printf("Are you sure you want to play as %s%c%s? %s(Y/N)%s: ", CYAN_FORMAT, player, LIGHT_YELLOW_FORMAT, CYAN_FORMAT, LIGHT_YELLOW_FORMAT);
   scanf("%c", &ch);
   fflush(stdin);
   if (ch == 'N' || ch == 'n')
   {
      PlayerSelection();
   }
}

void ResultScreen()
{
   system("cls");

   if (winner == player)
   {
      ++wins;
   }
   else if (winner == computer)
   {
      ++loses;
   }
   else
   {
      ++draws;
   }
   totalGames = draws + wins + loses;

   printf("%s", WHITE_FORMAT);
   printf("Total Rounds: %d\n", --round);
   PrintBoard();
   printf("\n");
   if (winner == player)
   {
      printf("%s", GREEN_FORMAT);
   }
   else if (winner == computer)
   {
      printf("%s", RED_FORMAT);
   }
   else
   {
      printf("%s", LIGHT_YELLOW_FORMAT);
   }
   DisplayFormatting();
   printf("\nGame #%d Results:\n", ++gameNumber);
   PrintWinner(winner);
   printf("\n\n%s", WHITE_FORMAT);
   DisplayFormatting();
   printf("\nOverall Stats:");

   printf("\nTotal Games: %d", totalGames);
   printf("\n%sWins: %d/%d\t", GREEN_FORMAT, wins, totalGames);

   temp = wins * 64 / totalGames;
   for (int l = 0; l < temp; l++)
   {
      printf("\xdb");
   }
   temp = (totalGames - wins) * 64 / totalGames;
   printf("%s", WHITE_FORMAT);
   for (int l = 0; l < temp; l++)
   {
      printf("-");
   }

   printf("\n%sLoses: %d/%d\t", RED_FORMAT, loses, totalGames);
   temp = loses * 64 / totalGames;
   for (int l = 0; l < temp; l++)
   {
      printf("\xdb");
   }
   temp = (totalGames - loses) * 64 / totalGames;
   printf("%s", WHITE_FORMAT);
   for (int l = 0; l < temp; l++)
   {
      printf("-");
   }

   printf("\n%sDraws: %d/%d\t", LIGHT_YELLOW_FORMAT, draws, totalGames);
   temp = draws * 64 / totalGames;
   for (int l = 0; l < temp; l++)
   {
      printf("\xdb");
   }
   temp = (totalGames - draws) * 64 / totalGames;
   printf("%s", WHITE_FORMAT);
   for (int l = 0; l < temp; l++)
   {
      printf("-");
   }

   printf("\n\n%s", WHITE_FORMAT);
   DisplayFormatting();
   printf("\nWould you like to play again? %s(Y/N)%s: ", CYAN_FORMAT, WHITE_FORMAT);
   scanf("%c", &response);
   response = toupper(response);
   if (response == 'Y')
   {
      round = 0;
      fflush(stdin);
      printf("\nWould you like to swap sign to %s%c%s [Current: %s%c%s]? (%sY/N%s): ",
             CYAN_FORMAT, computer, WHITE_FORMAT, CYAN_FORMAT, player, WHITE_FORMAT, CYAN_FORMAT, WHITE_FORMAT);
      scanf("%c", &response2);
      response2 = toupper(response2);
      if (response2 == 'Y')
      {
         char t = player;
         player = computer;
         computer = t;
      }
      if (player == 'X')
      {
         StartWithPlayer();
      }
      else
      {
         StartWithComputer();
      }
   }
}

void EndScreen()
{
   system("cls");
   time_t t;   //importing time
   time(&t);
   printf("%s\n", ctime(&t));
   DisplayFormatting();
   printf("%s\n\n\t\t\tThank you for playing %sTic Tac Toe\n\n", LIGHT_YELLOW_FORMAT, CYAN_FORMAT);
   printf("%s\t\tBy %sRishi Banerjee%s\t||\t Project in %sC Language%s\n\n",
          LIGHT_YELLOW_FORMAT, CYAN_FORMAT, LIGHT_YELLOW_FORMAT, CYAN_FORMAT, WHITE_FORMAT);
   system("pause");
   system("cls");
   printf("\n\n\t\t\t\tExiting\033[31;5m\n\n");
   for (int l = 1; l <= 70; l++)
   {
      Sleep(50);
      printf("-");
   }
   exit(0);
}
