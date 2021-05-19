// Tic-Tac-Toe-Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ---------------------------
// Global constant values
// ---------------------------
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
// ---------------------------

// ---------------------------
// Function prototypes
// ---------------------------
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(int move, const vector<char>& board);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);
// ---------------------------

int main()
{
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);
    while (winner(board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }
    announceWinner(winner(board), computer, human);
    return 0;
}

// [FUNCTION] - Print welcome messages
void instructions()
{
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe. \n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make your move known be entering a number, 0 - 8. The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n";
    cout << " 0 | 1 | 2\n";
    cout << "----------\n";
    cout << " 3 | 4 | 5\n";
    cout << "----------\n";
    cout << " 6 | 7 | 8\n";
    cout << "----------\n\n";
    cout << "Prepare yourself, human. THe battle is about to begin.\n\n";
}

// [FUNCTION] - recieve answer from user
char askYesNo(string question)
{
    char response;
    do
    {
        cout << question << " (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

// [FUNCTION] - choose cell to place symbol
int askNumber(string question, int high, int low)
{
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    } while (number > high && number < low);
    return number;
}

// [FUNCTION] - choose side to play
// [OUTPUT] - return choosen symbol of player
char humanPiece()
{
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y')
    {
        cout << "\nThen take the first move. You will need it.\n";
        return X;
    }
    else
    {
        cout << "\nYour bravery will be your undoing...I will go first.\n";
        return O;
    }
}

// [FUNCTION] - choose computer symbol to play
// [INPUT] - symbol which was chosen by player
// [OUTPUT] - return symbol of computer
char opponent(char piece)
{
    if (piece == X)
        return O;
    else
        return X;
}

// [FUNCTION] - display players board
// [INPUT] - board vi constant reference. No changes expected
// [OUTPUT] - print board
void displayBoard(const vector<char>& board)
{
    cout << "\n----------";
    cout << "\n" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n----------";
    cout << "\n" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n----------";
    cout << "\n" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n----------\n\n";
}

// [FUNCTION] - define winner or state of game
// [INPUT] - const reference on board
// [OUTPUT] - game winner symbol or state TIE, NO_ONE, X, Y
char winner(const vector<char>& board)
{
    // possible wining combinations
    const int WINNIG_ROWS[8][3] = { {0 , 1 , 2},
                                    {3 , 4 , 5},
                                    {6 , 7 , 8},
                                    {0 , 3 , 6},
                                    {1 , 4 , 7},
                                    {2 , 5 , 8},
                                    {0 , 4 , 8},
                                    {2 , 4 , 6} };
    const int TOTAL_ROWS = 8;
    for ( int row = 0; row < TOTAL_ROWS; ++row)
    {
        // check all possible gmae cases
        if ( (board[WINNIG_ROWS[row][0]] != EMPTY) &&
             (board[WINNIG_ROWS[row][0]] == board[WINNIG_ROWS[row][1]]) &&
             (board[WINNIG_ROWS[row][1]] == board[WINNIG_ROWS[row][2]]))
        {
            return board[WINNIG_ROWS[row][0]];
        }
        // check if it is TIE
        if (count(board.begin(), board.end(), EMPTY) == 0)
            return TIE;
    }    
    // Else - continue - game not finished
    return NO_ONE;
}

// [FUNCTION] - check if made turn - valid
// [INPUT 1] - const reference on board, 
// [INPUT 2] - move position
// [OUTPUT] - true | false - valid or wrong move
inline bool isLegal(int move, const vector<char>& board)
{   
    return (board[move] == EMPTY); 
}

// [FUNCTION] - make human move
// [INPUT 1] - const reference on board
// [INPUT 2] - human symbol
// [OUTPUT] - position of made legal move
int humanMove(const vector<char>& board, char human)
{
    int move = askNumber("Where will you move?", (board.size() - 1));
    while (!isLegal(move, board))
    {
        cout << "\nThat possition is already occupied, stupid human.\n";
        move = askNumber("Where will you move now?", (board.size() - 1));
    }
    cout << "Fine...\n";
    return move;
}

// [FUNCTION] - make computer move
// [INPUT 1] - const reference on board
// [INPUT 2] - computer  symbol
// [OUTPUT] - position of made legal move by computer
int computerMove(vector<char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;
    // case 1 - if computer can win, it makes this move
    while ( !found && move < board.size())
    {
        if (isLegal(move, board))
        {
            board[move] = computer;
            found = winner(board) == computer;      // if move gians win - found will be equal 1
            board[move] = EMPTY;
        }
        if (!found)
            ++move;
    }
    // case 2 -  if user can win next - block it
     if (!found)
    {
        move = 0;                   // make brutforced previosly possible moves - equal zero
        char human = opponent(computer);
        while (!found && move < board.size())
        {
            if (isLegal(move, board))
            {
                board[move] = human;
                found = winner(board) == human;     // if move gians win - found will be equal 1
                board[move] = EMPTY;
            }
            if (!found)
            {
                ++move;
            }
        }
    }
    // case 3 - else - place an optomal possible emppty cell
    if (!found)
    {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7}; // middle cell - 4 - is the best. 
        // choose free cell
        while (!found && i < board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move, board))
            {
                found = true;
            }
            ++i;
        }
    }
    cout << "I shall take square number " << move << endl;
    return move;
}

// [FUNCTION] - anounce winner 
// [INPUT 1] - figure winner
// [INPUT 2] - computer  symbol
// [INPUT 3] - human  symbol
void announceWinner(char winner, char computer, char human)
{
    if (winner == computer) 
    {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am truimphant once more -- prof \n";
        cout << "that computers are superior to humans in all regard.\n";
    }
    else if (winner == human)
    {
        cout << winner << "'s won!\n";
        cout << "No, no! It cannot be! Somehow you tricked me, human. \n";
        cout << "But never again! I, the computer, so swear it! \n";
    }
    else
    {
        cout << "It is a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}

