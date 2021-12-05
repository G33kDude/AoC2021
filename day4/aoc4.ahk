#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc4.c", "r").Read())

input := FileOpen(A_ScriptDir "\input4.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := RegExReplace(input, "`a)\R", "`n") ; Normalize newlines to single linefeed
input := StrSplit(input, "`n`n") ; Split input on double newline

numbers := []
boards := []
board_win_order := []

; Grab and numerify bingo numbers
for k, v in StrSplit(input.RemoveAt(1), ",")
	numbers[k] := v+0

; Grab and process bingo boards
for board_index, board in input
{
	; Mark board win order as -1 for all at start
	board_win_order[board_index] := -1

	; Split up each board
	for row_index, row in StrSplit(board, "`n", "`r")
	{
		row := Trim(row, " ") ; Strip leading spaces
		row := RegExReplace(row, "\s+", " ") ; Collapse multi-space to single space
		row := StrSplit(row, " ") ; Split on space

		; Numerify and set cell value
		for col_index, col in row
			boards[board_index, row_index, col_index] := col+0
	}
}

MsgBox, % DllCall(lib.part1, "Ptr", &boards, "Ptr", &numbers, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &boards, "Ptr", &numbers, "Ptr", &board_win_order, "CDecl Int")

