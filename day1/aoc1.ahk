#NoEnv
SetBatchLines, -1

#Include MCL.ahk\MCL.ahk

MCL.CompilerPrefix := "/usr/bin/x86_64-w64-mingw32-"
MCL.CompilerSuffix := ""

part1 =
( %

#include "ahk.h"

int SavedValue = 10;

int __main(Object *pobjIn) {

	Field *pField = pobjIn->pFields;
	int last = pField->iValue;

	int count = 0;
	for (int i = 0; i < pobjIn->cFields; i++) {
		pField = pobjIn->pFields + i;
		if (pField->iValue > last) {
			count++;
		}
		last = pField->iValue;
	}

	return count;
}

)

part2 =
( %

#include "ahk.h"

#define iValue(o, i) (((Field*)(o->pFields + i))->iValue)

int SavedValue = 10;

int __main(Object *pobjIn) {
	int last = iValue(pobjIn, 0) + iValue(pobjIn, 1) + iValue(pobjIn, 2);

	int count = 0;
	for (int i = 3; i < pobjIn->cFields; i++) {
		int next = iValue(pobjIn, i) + iValue(pobjIn, i - 1) + iValue(pobjIn, i - 2);
		if (next > last) {
			count++;
		}
		last = next;
	}

	return count;
}

)

obj := StrSplit(RTrim(FileOpen("input1.txt", "r").Read(), "`r`n"), "`n", "`r")
for k, v in obj
	obj[k] := v+0

MsgBox, % DllCall(MCL.FromC(part1), "Ptr", &obj, "CDecl Int")
MsgBox, % DllCall(MCL.FromC(part2), "Ptr", &obj, "CDecl Int")

