#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc8.c", "r").Read())

input := FileOpen(A_ScriptDir "\input8.txt", "r").Read()

; Pre-process input rows
rows := []
loop, parse, input, `n, `r
{
    tmp := StrSplit(A_LoopField, "|", " ")
    rows[A_Index] := [StrSplit(tmp[1], " "), StrSplit(tmp[2], " ")]
}

MsgBox, % DllCall(lib.part1, "Ptr", &rows, "CDecl Ptr")
; MsgBox, % DllCall(lib.part2, "Ptr", &rows, "CDecl Ptr")

