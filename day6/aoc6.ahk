#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc6.c", "r").Read())

input := FileOpen(A_ScriptDir "\input6.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, ",") ; Split input on comma

; Pre-process lanternfish data
for i, fish in input
    input[i] := fish+0
input2 := input.Clone()

MsgBox, % DllCall(lib.part1, "Ptr", &input, "CDecl Int")

;           0  1  2  3  4  5  6  7  8
schools := [0, 0, 0, 0, 0, 0, 0, 0, 0] ; 9 schools of fish, one per breeding cycle

MsgBox, % DllCall(lib.part2, "Ptr", &input2, "Ptr", &schools, "CDecl Ptr")
