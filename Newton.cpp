#include<iostream>		//for cin and cout
#include<cctype>		//for using toupper which turns the lowercase letters into uppercase.
using namespace std;

//---------------------------------------------------------------------------------------------------------------------
//Displays game instructions.
void displayGameInstructions()
{
	//Displaying game instructions
	cout << "Welcome to the game of Newton, where you try to be the first \n"
      	 << "to get 5 in a row either vertically, horizontally or diagonally. \n"
      	 << "Two players alternate making moves.  On each turn you may enter  \n"
         << "the column number where your piece will be placed, where that    \n"
      	 << "piece is inserted from the top and slides down as far as it can  \n"
      	 << "go in that column.  You may also enter 'r' to rotate a piece out \n"
       	 << "of the bottom of a column to be dropped back in at the top of    \n"
      	 << "that column.  Enter 'x' to exit.                               \n\n"
	 << endl;
} //end displayGameInstructions()


//-------------------------------------------------------------------------------------------------------------------------------
//Displays game board with 8 rows and 5 columns. It takes board[] and BoardValues as its parameters and does not return anything.
void displayBoard(char board[], int BoardValues)
{
	int k = 0;						//Initialize an integer loop counter.
	cout <<" 1   2   3   4   5  \n"
	   	 <<"--- --- --- --- --- \n";
	for(int i = 0; i < 8; i++) {				//For loop to iterate through 8 rows.
		for(int j = 0; j < 5; j++) {			//For loop to iterate through 5 columns.
	 		cout << " " << board[k] <<"  ";		//Displays board[0] to board[39]. Intially these values are '.'
	 		k++;					//Counter increments from 0 to 39.
		}
	 	cout << "\n";
	}
	cout <<"--- --- --- --- --- \n"
		 <<" 1   2   3   4   5"
		 << endl; 
} //end of displayBoard()


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Places game piece in the column entered by the user where that piece is inserted from the top and slides down as far as it can go in that column. 
This function takes the rowColumn[], BoardValues, columnNumber entered by user and char value which holds 'X' or 'O' as its parameters.  */
void placeGamePieceInColumn(char rowColumn[], int BoardValues, int columnNumber, char value)
{ 
	for(int i = 7; i >= 0; i--) {						//For loop iterates through all the 8 rows.
		if(rowColumn[(i*5) + (columnNumber - 1)] == '.') {		//Checks which row from the bottom is empty for the corresponding column entered by the user.	
			rowColumn[(i*5) + (columnNumber - 1)] = value;		//When an empty row is found for the column entered by the user, it is assigned with either X or O.
			break;			
		} 
	}
	displayBoard(rowColumn, BoardValues);					//Displays the game board after placing game piece.
} //end of placeGamePieceInColumn()


/*----------------------------------------------------------------------------------------------------------------
Rotates a column by taking a piece out of the bottom of a column and dropping it back in at the top of that column. 
This function takes board[], BoardElements and columnToRotate as its parameters.*/
void rotate(char board[], int BoardElements, int columnToRotate)
{	                                                                                                       
	int i;
	char temp;									
	temp = board[35 + columnToRotate - 1];				//Storing the value of last row in temp.

	for(i=7; i>0; i--) {						//For loop iterates through all the rows starting from the last row.
		if(board[((i-1)*5) + columnToRotate -1] == '.')	{	//It checks for the condition if a row corresponding to the column entered by the user is empty.	
			board[(i*5) + columnToRotate - 1] = temp;	//If an empty row is found, assign the value of temp to the row below that.
			break;
		}
		board[(i*5) + columnToRotate - 1] = board[((i-1)*5) + columnToRotate -1]; //Replace the value of every board piece with the value of board piece above it.
	}
	
	if(board[0 + columnToRotate - 1] != '.') {			//It checks for the condition if the column entered by the user to rotate is full.
		board[0 + columnToRotate - 1] = temp;			//If the column entered by the user is full then replace the top most piece in the column with the value of the last piece.
	}
	displayBoard(board, BoardElements);				//Display the rotated game board.
} //end of rotate()


/*---------------------------------------------------------------------------------------------------------------------------------------------
Checks if there are 5 consecutive X's or O's in any of the 8 rows. This function takes board[], and BoardElements as its parameters.
If 5 consecutive X's or O's are found, it returns which variable is found, else it returns '.' */
char rowCheck(char board[], int BoardElements)
{
	int i;
	char variable = '.';				
	for( i=0; i<=35; i=i+5)	{			//For loop to iterate through all 8 rows.	
		//Checks if all 5 elements in a row are equal, and also checks if all those 5 elements are not empty.	
		if( (board[i] != '.') && ((board[i] == board[i+1]) && (board[i] == board[i+2]) 
		     && (board[i] == board[i+3]) && (board[i] == board[i+4])) ) {		
			variable = board[i];		//If there are 5 consecutive X's or O's, store the X or O found in variable.
			return variable;
			break;			
		}
	}
	return '.';					//If 5 consecutive X's or O's are not found, return '.'
} //end of rowCheck()


/*----------------------------------------------------------------------------------------------------------------------------------------------------
Checks if there are 5 consecutive X's or O's in any of the 5 columns. This function takes board[], and BoardElements as its parameters.
If 5 consecutive X's or O's are found, it returns which variable is found, else it returns '.' */
char colCheck (char board[], int BoardElements)
{	
	char variable;
	for(int i=0; i<=19; i=i+1) {		//For loop which iterates through all columns.		
		//Checks if 5 elements in a column are equal, and also checks if all those 5 elements are not empty.
		if((board[i] != '.') && ((board[i] == board[i+5]) && (board[i] == board[i+10]) 
		    && (board[i] == board[i+15]) && (board[i] == board[i+20])))	{
			variable = board[i];	//If there are 5 consecutive X's or O's, store the X or O found in variable.
			return variable;	//Return the value of that variable.
			break;
		}
	}
	return '.';				//If 5 consecutive X's or O's are not found, return '.'
} //end of colCheck()


/*----------------------------------------------------------------------------------------------------------------------------------------------
Checks if there are 5 consecutive X's or O's in any diagonal from upper left to lower right. This function takes board[], and BoardElements as its parameters.
If 5 consecutive X's or O's are found in a diagonal, it returns which variable is found, else it returns '.' */
char upperLeftDiagonalCheck(char board[], int BoardElements)
{
	char variable;
	for(int i = 0; i<=15 ; i=i+5) {
		//Checks if 5 elements in a diagonal are equal, and also checks if all those 5 elements are not empty.
		if((board[i] != '.') && ((board[i] == board[i+6]) && (board[i] == board[i+12]) 
		    && (board[i] == board[i+18]) && (board[i]== board[i+24]))) {	
			variable = board[i];		//If there are 5 consecutive X's or O's in a diagonal, store the X or O found in variable.
			return variable;		//Return the value of that variable.
			break;
		}
	}
	return '.';					//If 5 consecutive X's or O's are not found in a diagonal, return '.'
} //end of upperLeftDiagonalCheck()


/*-----------------------------------------------------------------------------------------------------------------------------------------------
Checks if there are 5 consecutive X's or O's in any diagonal from lower left to upper right. This function takes board[], and BoardElements as its parameters.
If 5 consecutive X's or O's are found in a diagonal, it returns which variable is found, else it returns '.'*/
char lowerLeftDiagonalCheck(char board[], int BoardElements)
{
	char variable;
	for(int i = 4; i<20; i=i+5) {
		//Checks if 5 elements in a diagonal are equal, and also checks if all those 5 elements are not empty.
		if((board[i] != '.') && ((board[i] == board[i+4]) && (board[i] == board[i+8]) 
		    && (board[i] == board[i+12]) && (board[i]== board[i+16]))) {	
			variable = board[i];		//If there are 5 consecutive X's or O's in a diagonal, store the X or O found in variable.
			return variable;		//Return the value of that variable.
			break;
		}
	}
	return '.';					//If 5 consecutive X's or O's are not found in a diagonal, return '.'
} //end of lowerLeftDiagonalCheck()


//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	//Global constant
	const int BoardElements = 40;  			//Number of pieces on game board.
	
	//Declare and initialize gameBoard[] 
	char gameBoard[BoardElements] = {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',
									 '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
	char userInput;
	char value;
	char winner = '.';
	int x = 1;
	int columnNumber;
	int columnToRotate;
	
	displayGameInstructions();						//Display header info and instructions.
	displayBoard(gameBoard, BoardElements);					//Display Game Board.
	
	cout<< x <<". Enter column number to place X or 'r' to rotate:";	//Get user input

	//Main loop to play game.
	while(cin >> userInput) {
		userInput = toupper(userInput);					//Convert userInput to upper case
		cout << endl;
		(x % 2 == 1) ? value = 'X' : value = 'O';			//Assign variable X or O to value alternatively.
		
		//Checks if the column entered by the user is full
		if(((gameBoard[0] !='.') && (userInput == '1'))|| ((gameBoard[1] != '.') && (userInput == '2')) || ((gameBoard[2] != '.') && (userInput == '3')) ||
                   ((gameBoard[3] != '.') && (userInput == '4')) || ((gameBoard[4] != '.') && (userInput == '5') )) {
			cout << "*** Sorry, that column is already full.  Please choose another." << endl << endl; 		
			cout << x << ". Enter column number to place X or 'r' to rotate:" ;
			continue;						//Goes back to the start of while loop
		}
		
		//Checks if user enters a number between 1 and 5 inclusive. 
		else if((userInput > '0') && (userInput < '6'))	{
			columnNumber = int(userInput - 48);					//Convert userInput to integer and assign the integer to columnNumber.
			placeGamePieceInColumn(gameBoard, BoardElements, columnNumber, value);	//Call the placeGamePieceInColumn()	
		}
		
		//Check if userInput is R
		else if(userInput == 'R') {
			cin >> userInput; 
			if((userInput > '0') && (userInput < '6')) {		  //Checks if user enters a number between 1 and 5 inclusive.
				columnToRotate = int(userInput - 48);		  //Convert userInput to integer and assign the integer to columnToRotate
				rotate(gameBoard, BoardElements, columnToRotate); //Call the rotate()
			}
		}
		
		//Check if userInput is X
		else if(userInput == 'X') {
			exit;
		}
		
		//If userInput is not a number between 1 and 5 inclusive, and is not X or R then execute the else part.
		else {
			cout<< "*** Invalid input.  Please retry..." << endl << endl;
			cout<< x << ". Enter column number to place X or 'r' to rotate:";
			continue;												//Goes back to the start of while loop
		}
		
		if(winner == '.') {
			winner = rowCheck(gameBoard, BoardElements);		   //Call rowCheck() and if someone wins, assign the variable to winner.	
		}
	 	if(winner == '.') {
			winner = colCheck(gameBoard, BoardElements); 	       	   //Call colCheck() and if someone wins, assign the variable to winner.
		}
	    	if(winner == '.') {
			winner = upperLeftDiagonalCheck(gameBoard, BoardElements); //Call upperLeftDiagonalCheck() and if someone wins, assign the variable to winner.
		}
		if(winner == '.') {
			winner = lowerLeftDiagonalCheck(gameBoard, BoardElements); //Call lowerLeftDiagnalCheck() and if someone wins, assign the variable to winner.
		}
		
		//Executes this if winner is either X or O.
		if(winner != '.') {											
			cout << endl << "***Congratulations " << winner << ", you just won!***" << endl << endl; 	
			displayBoard(gameBoard, BoardElements);
			break;													//Exits the game
		}	
		
		cout<< x+1 << ". Enter column number to place X or 'r' to rotate:";
		userInput = toupper(userInput);
		x++;														//Increment x to alternate values between X and O
	}
	return 0;
} //end of main()

