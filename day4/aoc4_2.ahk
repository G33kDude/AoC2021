#NoEnv
SetBatchLines, -1

#Include MCL.ahk\MCL.ahk

MCL.CompilerPrefix := "/usr/bin/x86_64-w64-mingw32-"
MCL.CompilerSuffix := ""

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc4.c", "r").Read())

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

