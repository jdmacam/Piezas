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

TEST(PiezasTest, constructor_first_turn)
{
	Piezas obj;
	ASSER_TRUE(turn == X);
}
