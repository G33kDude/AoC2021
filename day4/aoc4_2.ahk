#NoEnv
SetBatchLines, -1

#Include MCL.ahk\MCL.ahk

MCL.CompilerPrefix := "/usr/bin/x86_64-w64-mingw32-"
MCL.CompilerSuffix := ""

c =
( %

#define UNICODE

#include <mcl.h>
#include "ahk.h"

BOOL inNums(Object *numbers, int cutoff, int number)
{
	for (int i = 0; i <= cutoff; i++) {
		if (number == numbers->pFields[i].iValue) {
			return 1;
		}
	}
	return 0;
}

int invalidSum(Object *board, Object *numbers, int cutoff) {
	int sum = 0;
	for (int irow = 0; irow < board->cFields; irow++) {
		Object* row = board->pFields[irow].pobjValue;
		for (int icol = 0; icol < row->cFields; icol++) {
			int val = row->pFields[icol].iValue;
			if (!inNums(numbers, cutoff, val)) {
				sum += val;
			}
		}
	}
	return sum;
}

BOOL validBoard(Object *board, Object *numbers, int cutoff) {
	// Rows
	for (int irow = 0; irow < board->cFields; irow++) {
		for (int icol = 0;; icol++) {
			// Completed row means the board is vaild
			if (icol >= board->pFields[irow].pobjValue->cFields) {
				return 1;
			}

			// Bail on bad rows
			if (!inNums(numbers, cutoff, board->pFields[irow].pobjValue->pFields[icol].iValue)) {
				break;
			}
		}
	}


	// Columns
	for (int icol = 0; icol < board->pFields[0].pobjValue->cFields; icol++) {
		for (int irow = 0;; irow++) {
			// Completed column means the board is vaild
			if (irow >= board->cFields) {
				return 1;
			}

			// Bail on bad columns
			if (!inNums(numbers, cutoff, board->pFields[irow].pobjValue->pFields[icol].iValue)) {
				break;
			}
		}
	}

	return 0;
}


MCL_EXPORT(part1);
TCHAR part1(Object *boards, Object *numbers, Object *windex) {
	int winnercount = 0;
	int winning_inum = -1;

	int last_winner = -1;
	for (int inum = 0; inum < numbers->cFields; inum++) {
		for (int iboard = 0; iboard < boards->cFields; iboard++) {
			Object* board = boards->pFields[iboard].pobjValue;
			if (validBoard(board, numbers, inum)) {
				if (windex->pFields[iboard].iValue < 0) {
					windex->pFields[iboard].iValue = ++winnercount;
					winning_inum = inum;
				}
			}
		}
	}
	
	for (int iboard = 0; iboard < boards->cFields; iboard++) {
		if (windex->pFields[iboard].iValue == winnercount) {
			return numbers->pFields[winning_inum].iValue * invalidSum(boards->pFields[iboard].pobjValue, numbers, winning_inum);
		}
	}

	return -1;
}

)

lib := MCL.FromC(c)

obj := StrSplit(RegExReplace(RTrim(FileOpen(A_ScriptDir "\input4.txt", "r").Read(), "`r`n"), "`a)\R", "`n"), "`n`n")

numbers := StrSplit(obj.RemoveAt(1), ",")
for k, v in numbers
	numbers[k] := v+0
boards := []

windex := []
for iboard, board in obj {
	windex[iboard] := -1
	for irow, row in StrSplit(board, "`n", "`r") {
		for icol, col in StrSplit(RegExReplace(Trim(row, " "), "\s+", " "), " ")
			boards[iboard, irow, icol] := col+0
	}
}

MsgBox, % DllCall(lib.part1, "Ptr", &boards, "Ptr", &numbers, "Ptr", &windex, "CDecl Int")

