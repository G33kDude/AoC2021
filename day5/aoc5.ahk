#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc5.c", "r").Read())

input := FileOpen(A_ScriptDir "\input5.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, "`n", "`r") ; Split input on newline

; Generate a sea-floor map
ocean := []
loop, 1000
{
    y := A_Index
    loop, 1000
    {
        x := A_Index
        ocean[y, x] := 0+0
    }
}

; Pre-process vent locations
vents := []
for i, vent in input
    for j, coord in StrSplit(StrReplace(vent, " -> ", ","), ",")
        vents[i, j] := coord+0

MsgBox, % DllCall(lib.part1, "Ptr", &ocean, "Ptr", &vents, "CDecl Int")

; Debug display for sample input
out := ""
loop, 10
{
    y := A_Index
    line := ""
    loop, 10
    {
        x := A_Index
        line .= StrReplace(ocean[y, x], "0", ".")
    }
    out .= line "`n"
}
fileappend, %out%, *