#include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc3.c", "r").Read())

input := FileOpen(A_ScriptDir "\input3.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, "`n", "`r") ; Split input on newline

; Part 2 modifies the object. Clone for use in second pass.
input2 := input.Clone()

MsgBox, % "Part 1: " DllCall(lib.part1, "Ptr", &input, "CDecl Int")
MsgBox, % "Part 2: " DllCall(lib.part2, "Ptr", &input, "Int", 1, "CDecl Int") * DllCall(lib.part2, "Ptr", &input2, "Int", 2, "CDecl Int")
