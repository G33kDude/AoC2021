#Include shared.ahk

lib := MCL.FromC(FileOpen(A_ScriptDir "\aoc11.c", "r").Read())
input := FileOpen(A_ScriptDir "\input11s.txt", "r").Read()

VarSetCapacity(levels, 100, 0)

i := 0
for k, v in StrSplit(input)
    if v is Number
        NumPut(v, &levels+(i++), "UChar")

MsgBox, % DllCall(lib.part1, "Ptr", &levels, "CDecl Int")

ShowLevels(&levels)

MsgBox, % DllCall(lib.part2, "Ptr", &levels, "CDecl Int64") + 100

ShowLevels(pLevels) {
    loop, 10
    {
        loop, 10
            out .= *(pLevels++)
        out .= "`n"
    }
    MsgBox, %out%
}
