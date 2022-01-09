#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc10.c", "r").Read())

input := FileOpen(A_ScriptDir "\input10.txt", "r").Read()
input := RTrim(input, "`r`n")
input := StrSplit(input, "`n", "`r")

MsgBox, % DllCall(lib.part1, "Ptr", &input, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &input, "CDecl Int64")

