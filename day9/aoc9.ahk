#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc9.c", "r").Read())

input := FileOpen(A_ScriptDir "\input9.txt", "r").Read()
input := RTrim(input, "`r`n")
input := StrSplit(input, "`n", "`r")

; Pre-process input rows into byte/uchar buffer
iHMapHeight := input.Count()
iHMapWidth := StrLen(input[1])
VarSetCapacity(bufHMap, iHMapWidth * iHMapHeight, 0)
for y, row in input
    for x, height in StrSplit(row)
        NumPut(height, &bufHMap + (y-1) * iHMapWidth + (x-1), "UChar")

MsgBox, % DllCall(lib.part1, "Ptr", &bufHMap, "Int", iHMapWidth, "Int", iHMapHeight, "CDecl Ptr")
MsgBox, % DllCall(lib.part2, "Ptr", &bufHMap, "Int", iHMapWidth, "Int", iHMapHeight, "CDecl Ptr")

