/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, constructor_first_space)
{
  Piezas obj;
  ASSERT_TRUE(obj.pieceAt(0,0) == Blank);
}

TEST(PiezasTest, constructor_all_spaces)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      ASSERT_TRUE(obj.pieceAt(i,j) == Blank);
    }
  }
}

TEST(PiezasTest, drop_1_in_column)
{
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_TRUE(obj.pieceAt(0,0) == X);
}

TEST(PiezasTest, drop_2_in_column)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	ASSERT_TRUE(obj.pieceAt(0,0) == X);
	ASSERT_TRUE(obj.pieceAt(1,0) == X);
}

TEST(PiezasTest, drop_3_in_column)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	ASSERT_TRUE(obj.pieceAt(0,0) == X);
	ASSERT_TRUE(obj.pieceAt(1,0) == X);
	ASSERT_TRUE(obj.pieceAt(2,0) == X);
}

TEST(PiezasTest, drop_alternating_to_full)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	ASSERT_TRUE(obj.pieceAt(0,0) == X);
	ASSERT_TRUE(obj.pieceAt(1,0) == X);
	ASSERT_TRUE(obj.pieceAt(2,0) == X);
	ASSERT_TRUE(obj.pieceAt(0,1) == O);
	ASSERT_TRUE(obj.pieceAt(1,1) == O);
	ASSERT_TRUE(obj.pieceAt(2,1) == O);
}

TEST(PiezasTest, reset_test)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.reset();
	ASSERT_TRUE(obj.pieceAt(0,0) == Blank);
	ASSERT_TRUE(obj.pieceAt(1,0) == Blank);
	ASSERT_TRUE(obj.pieceAt(2,0) == Blank);
	ASSERT_TRUE(obj.pieceAt(0,1) == Blank);
	ASSERT_TRUE(obj.pieceAt(1,1) == Blank);
	ASSERT_TRUE(obj.pieceAt(2,1) == Blank);
}

TEST(PiezasTest, full_column)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	ASSERT_TRUE(obj.dropPiece(0) == Blank);
}

TEST(PiezasTest, out_of_upper_bounds)
{
	Piezas obj;
	ASSERT_TRUE(obj.dropPiece(BOARD_COLS) == Invalid);
}

TEST(PiezasTest, out_of_lower_bounds)
{
	Piezas obj;
	ASSERT_TRUE(obj.dropPiece(-1) == Invalid);
}

TEST(PiezasTest, game_not_over_empty)
{
	Piezas obj;
	ASSERT_TRUE(obj.gameState() == Invalid);
}

TEST(PiezasTest, game_not_over_1_column_full)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	ASSERT_TRUE(obj.gameState() == Invalid);
}

TEST(PiezasTest, gamestate_tie)
{
	Piezas obj;
	for(int i = 0; i < BOARD_COLS; i++){
		obj.dropPiece(i);
		obj.dropPiece(i);
		obj.dropPiece(i);
	}
	ASSERT_TRUE(obj.gameState() == Blank);
}

TEST(PiezasTest, x_winner)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(3);
	ASSERT_TRUE(obj.gameState() == X);
}

TEST(PiezasTest, o_winner)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(2);
	obj.dropPiece(0);
	obj.dropPiece(3);
	obj.dropPiece(1);
	obj.dropPiece(3);
	obj.dropPiece(2);
	obj.dropPiece(3);
	ASSERT_TRUE(obj.gameState() == O);
}
