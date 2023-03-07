#include "Nim.h"
#include <stdlib.h> // for 'rand()'

using namespace Nim;

CNim::CNim( const UINT& uiRowsCount, const UINT& uiEveryRowSticks, const GameMode& mode )
	: m_GameMode( mode )
{
	for( UINT i = 0; i < uiRowsCount; i++ )
		m_lstSticksCount.push_back( uiEveryRowSticks );
}

CNim::CNim( const ListOfSticksCount& lstSticksCount, const GameMode& mode )
	: m_GameMode( mode ), m_lstSticksCount( lstSticksCount )
{}


MoveType CNim::play( const UINT& uiRow, const UINT& uiCount )
{
	UINT uiBestMove_Row = 0, uiBestMove_Count = 0;

	// firstly check for wrong movements:
	// 1. erroneously taking more than what exists in the provided row, or
	// 2. not to taking anything at all (i.e. uiCount == 0)
	UINT& requestedRowSticksCount = m_lstSticksCount[uiRow];
	if ( uiCount == 0 || requestedRowSticksCount < uiCount )
		return INCORRECT_MOVEMENT;
	

	MoveType howWell = calculateTheBestMove( uiBestMove_Row, uiBestMove_Count );

	 requestedRowSticksCount -= uiCount;
	 return howWell;
}


MoveType CNim::calculateTheBestMove( UINT& out_uiRow, UINT& out_uiCount ) const
{
	UINT uiNimSum = 0;
	const UINT& cuiRowsCount = m_lstSticksCount.size();

	for( UINT uiRow = 0; uiRow < cuiRowsCount; uiRow++ )
		uiNimSum ^= m_lstSticksCount[ uiRow ]; // The heart of the game!

	if ( uiNimSum )
	{
		for( UINT uiRow = 0; uiRow < cuiRowsCount; uiRow++ )
		{
			const UINT& cuiCurrentRowSticksCount = m_lstSticksCount[ uiRow ];
			const UINT B = uiNimSum ^ cuiCurrentRowSticksCount;

			if ( B > cuiCurrentRowSticksCount )
				continue;
			else 
			{
				out_uiRow = uiRow;
				out_uiCount = cuiCurrentRowSticksCount - B;
			}
		}

		// Nim strategy is different only when the normal play would have no heap of size two or larger
		// so, temporarilly copy the list 
		ListOfSticksCount tempLstSticksCount = m_lstSticksCount;

		// play on the temporary copy of the list!
		tempLstSticksCount[ out_uiRow ] -= out_uiCount;

		// now, first determine whether the criteria of the second strategy is satisfied
		// and meanwhile determine the number of heaps of size '1'
		bool bSecondStrategy = true;
		UINT uiNumberOfHeapsOfSizeOne = 0;

		for( UINT uiRow = 0; uiRow < cuiRowsCount; uiRow++ )
		{
			const UINT& cuiCurrentRowSticksCount = tempLstSticksCount[uiRow];
			if ( bSecondStrategy && cuiCurrentRowSticksCount > 1 )
			{
				bSecondStrategy = false;
				break;
			} else if ( cuiCurrentRowSticksCount == 1 )
				uiNumberOfHeapsOfSizeOne++;
		}

		if ( bSecondStrategy )
		{
			if ( m_GameMode == MISERE )
			{
				// for MISERE play, leave an odd number of heaps of size '1'
				if ( uiNumberOfHeapsOfSizeOne % 2 == 0 )
				{
					out_uiCount += tempLstSticksCount[ out_uiRow ] ?  1 : -1;
				}
			}
			else
			{
				// for NORMAL play, leave an even number of heaps of size '1'
				if ( uiNumberOfHeapsOfSizeOne % 2 != 0 )
				{
					out_uiCount += tempLstSticksCount[ out_uiRow ] ?  1 : -1;
				}
			}
		}
	
		return BRILLIANT_MOVEMENT;
	}
	else
	{
		// determine the heaps' indices which aren't empty
		std::vector<UINT> lstNOTEmptyHeapsIndices;
		
		for ( UINT uiRow = 0; uiRow < cuiRowsCount; uiRow++ )
			if ( m_lstSticksCount[uiRow] != 0 )
				lstNOTEmptyHeapsIndices.push_back( uiRow );

		// random( const UINT& uiMax, const UINT& uiMin = 1 )	{ return rand() % (uiMax - uiMin +1) + uiMin; }
		// choose a random non-empty row
		out_uiRow = lstNOTEmptyHeapsIndices[ rand() % ( lstNOTEmptyHeapsIndices.size() ) ];
		
		// choose a random count of sticks for the previously random selection of row!
		out_uiCount = rand() % ( m_lstSticksCount[out_uiRow] +1);
		
		return UNINTELLIGENT_MOVEMENT;
	}

}


GameStatus CNim::getGameStatus() const
{
	const UINT& cuiRowsCount = m_lstSticksCount.size();
	UINT uiSum = 0;

	for( UINT uiRow = 0; uiRow < cuiRowsCount; uiRow++ )
	{
		uiSum += m_lstSticksCount[ uiRow ];
		if ( uiSum > 1 )
			return NOT_ENDED_YET;
	}

	// just one stick remains:
	return m_GameMode == MISERE ? LOSE : WIN;
}