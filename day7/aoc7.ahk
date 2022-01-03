#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc7.c", "r").Read())

input := FileOpen(A_ScriptDir "\input7.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, ",") ; Split input on comma

; Pre-process crab data
for i, crab in input
    input[i] := crab+0

MsgBox, % DllCall(lib.part1, "Ptr", &input, "CDecl Ptr")
MsgBox, % DllCall(lib.part2, "Ptr", &input, "CDecl Ptr")

