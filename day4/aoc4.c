
#define UNICODE

#include <mcl.h>
#include "ahk.h"

//
// Was the number to check called at any point up to the currently called number?
//
// Parameters:
//   numbers             - Array of bingo numbers
//   called_number_index - The index of the most recently called bingo number in the numbers array
//   number_to_check     - The number to look for in the called bingo numbers
//
BOOL wasCalled(Object *numbers, int called_number_index, int number_to_check)
{
	for (int i = 0; i <= called_number_index; i++) {
		if (number_to_check == numbers->pFields[i].iValue) {
			return true;
		}
	}
	return false;
}

//
// What's the sum of all uncalled numbers on the board?
//
// Parameters:
//   board               - 2D Array of board numbers
//   numbers             - Array of bingo numbers
//   called_number_index - The index of the most recently called bingo number in the numbers array
//
int uncalledsSum(Object *board, Object *numbers, int called_number_index) {
	int sum = 0;

	// For each row
	for (int row_index = 0; row_index < board->cFields; row_index++) {
		Object* row = board->pFields[row_index].pobjValue;

		// For each column
		for (int col_index = 0; col_index < row->cFields; col_index++) {
			int val = row->pFields[col_index].iValue;

			// Add to sum if this cell was never called
			if (!wasCalled(numbers, called_number_index, val)) {
				sum += val;
			}
		}
	}

	return sum;
}

//
// Does the given board have a row or column with all numbers called?
//
// Parameters:
//   board               - 2D Array of board numbers
//   numbers             - Array of bingo numbers
//   called_number_index - The index of the most recently called bingo number in the numbers array
//
BOOL boardWins(Object *board, Object *numbers, int called_number_index) {

	// Check all rows
	for (int row_index = 0; row_index < board->cFields; row_index++) {
		Object* row = board->pFields[row_index].pobjValue;

		// Look at all columns/cells in the row
		for (int col_index = 0;; col_index++) {

			// If checking column past end of row, all numbers were called
			if (col_index >= row->cFields) {
				return true;
			}

			// Stop checking this row if this cell was not called
			if (!wasCalled(numbers, called_number_index, row->pFields[col_index].iValue)) {
				break;
			}
		}
	}

	// Check all columns
	for (int col_index = 0; col_index < board->pFields[0].pobjValue->cFields; col_index++) {

		// Look at all rows/cells in the column
		for (int row_index = 0;; row_index++) {

			// If checking row past end of column, all numbers were called
			if (row_index >= board->cFields) {
				return true;
			}

			// Stop checking this column if this cell was not called
			Object* row = board->pFields[row_index].pobjValue;
			if (!wasCalled(numbers, called_number_index, row->pFields[col_index].iValue)) {
				break;
			}
		}
	}

	// No full rows or columns detected
	return false;
}

MCL_EXPORT(part1);
TCHAR part1(Object *boards, Object *numbers) {
	// Call each number in order
	for (int called_number_index = 0; called_number_index < numbers->cFields; called_number_index++) {

		// For all boards
		for (int board_index = 0; board_index < boards->cFields; board_index++) {
			Object* board = boards->pFields[board_index].pobjValue;

			// If the board is in a win condition
			if (boardWins(board, numbers, called_number_index)) {

				// Calculate and return the puzzle solution
				int winning_number = numbers->pFields[called_number_index].iValue;
				int uncalleds_sum = uncalledsSum(board, numbers, called_number_index);
				return winning_number * uncalleds_sum;
			}
		}
	}

	return -1;
}

MCL_EXPORT(part2);
TCHAR part2(Object *boards, Object *numbers, Object *board_win_order) {
	int winning_board_count = 0; // How many boards have won?
	int winning_called_number_index = -1; // Index of the last winning called number

	// Call each number in order
	for (int called_number_index = 0; called_number_index < numbers->cFields; called_number_index++) {

		// For all boards
		for (int board_index = 0; board_index < boards->cFields; board_index++) {
			Object* board = boards->pFields[board_index].pobjValue;

			// If the board is in a win state and didn't already win
			if (boardWins(board, numbers, called_number_index)
				&& board_win_order->pFields[board_index].iValue < 0) {

				// Mark its place in the winner's order
				board_win_order->pFields[board_index].iValue = ++winning_board_count;

				// Keep track of the index of the last winning number index
				winning_called_number_index = called_number_index;
			}
		}
	}

	// Find the board that won last
	for (int board_index = 0; board_index < boards->cFields; board_index++) {
		if (board_win_order->pFields[board_index].iValue == winning_board_count) {
			Object* board = boards->pFields[board_index].pobjValue;

			// Calculate and return the puzzle solution
			int winning_number = numbers->pFields[winning_called_number_index].iValue;
			int uncalleds_sum = uncalledsSum(board, numbers, winning_called_number_index);
			return winning_number * uncalleds_sum;
		}
	}

	return -1;
}
