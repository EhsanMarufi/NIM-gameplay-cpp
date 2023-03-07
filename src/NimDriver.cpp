// Nim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Nim.h"
#include <iostream>
#include <conio.h> // for '_getche()'

using namespace Nim;
using namespace std;
//using std::cout;
//using std::endl;
//using std::cin;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "In the name of God" << endl;
	cout << "Nim game, by Ehsan Marufi Azar, Apr 2013 (c)" << endl;
	
	int iPlayAgain = 0;


	do {
		// a new game has been just started!
		cout << endl << endl;
		cout << "row  0,  1,  2,  3" << endl;
		cout << "------------------" << endl;

		
		UINT arrSticksCount[] = { 1, 3, 5, 7 }; //{ 3, 4, 5, 0 };
		ListOfSticksCount lstSticksCount( arrSticksCount, arrSticksCount + 4 );
		CNim nim( lstSticksCount );

		do {
			// play the current game, until someone wins!
			// player's turn:
			UINT uiPlayedRow = 0, uiPlayedCount = 0;

			const ListOfSticksCount& gameSticksCount = nim.getSticks();
			cout << "You  ";
			for ( UINT i = 0; i < 4; i++ )
				cout << gameSticksCount[i] << ",  ";

			cout << "> ";
			cin >> uiPlayedRow >> uiPlayedCount;
			while ( nim.play( uiPlayedRow, uiPlayedCount ) == INCORRECT_MOVEMENT )
			{
				cout << " INCORRECT MOVEMENT! > ";
				cin >> uiPlayedRow >> uiPlayedCount;
			}
			// player-one may win!!
			if ( nim.getGameStatus() != NOT_ENDED_YET )
				break;

			// computer's turn
			cout <<"Com  ";
			for ( UINT i = 0; i < 4; i++ )
				cout << gameSticksCount[i] << ",  ";

			nim.calculateTheBestMove( uiPlayedRow, uiPlayedCount );
			cout << "> " << uiPlayedRow << "\t" << uiPlayedCount << endl;
			nim.play( uiPlayedRow, uiPlayedCount );

		} while ( nim.getGameStatus() == NOT_ENDED_YET );
		cout << "  !! Winner !!";

	cout << "\n\nDo you want to play again(y/n)? ";
	} while ( ( iPlayAgain = _getche() ) == 'y' || iPlayAgain == 'Y' );
	return 0;
}

