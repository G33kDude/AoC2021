#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc5.c", "r").Read())

input := FileOpen(A_ScriptDir "\input5.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, "`n", "`r") ; Split input on newline

; Generate blank sea-floor maps for parts 1 and 2
ocean1 := [], ocean2 := []
loop, 1000
{
    y := A_Index
    loop, 1000
        ocean2[y, A_Index] := ocean1[y, A_Index] := 0
}

; Pre-process vent locations
vents := []
for i, vent in input
    for j, coord in StrSplit(StrReplace(vent, " -> ", ","), ",")
        vents[i, j] := coord+0

MsgBox, % DllCall(lib.part1, "Ptr", &ocean1, "Ptr", &vents, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &ocean2, "Ptr", &vents, "CDecl Int")
print_ocean(ocean2, 10) ; debug sample input

print_ocean(ocean, size)
{
    loop, % size
    {
        y := A_Index
        line := ""
        loop, % size
            line .= StrReplace(ocean[y, A_Index], "0", ".")
        fileappend, %line%`n, *
    }
}