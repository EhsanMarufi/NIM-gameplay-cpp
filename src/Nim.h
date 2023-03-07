// In the name of God
// Ehsan Marufi Azar, 2013

// The 'Nim' Game!

#pragma once
#ifndef NIM_H
#define NIM_H

#include<vector>

typedef unsigned int UINT;

namespace Nim
{
	typedef enum _GameMode { MISERE, NORMAL } GameMode;
	typedef enum _GameStatus { NOT_ENDED_YET = 0, WIN, LOSE } GameStatus;
	typedef enum _MoveType { BRILLIANT_MOVEMENT, UNINTELLIGENT_MOVEMENT, INCORRECT_MOVEMENT } MoveType;
	typedef std::vector<UINT> ListOfSticksCount;

	class CNim
	{
	public:
		CNim( const UINT& uiRowsCount = 4, const UINT& uiEveryRowSticks = 7, const GameMode& mode = MISERE );
		CNim( const ListOfSticksCount& lstSticksCount, const GameMode& mode = MISERE );

		MoveType play( const UINT& uiRow, const UINT& uiCount );
		MoveType calculateTheBestMove( UINT& out_uiRow, UINT& out_uiCount ) const;

		GameStatus getGameStatus() const;

		inline const ListOfSticksCount& getSticks() const { return m_lstSticksCount; }

	protected:
		ListOfSticksCount m_lstSticksCount;
		const GameMode m_GameMode;
	}; // end of class 'CNim'
} // end of namespace 'Nim'

#endif // NIM_H