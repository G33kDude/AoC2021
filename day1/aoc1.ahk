#Include shared.ahk

c =
( %

#define UNICODE

#include <mcl.h>
#include "ahk.h"

MCL_EXPORT(part1);
int part1(Object *pobjIn) {

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

#define iValue(o, i) (o->pFields[i].iValue)

MCL_EXPORT(part2);
int part2(Object *pobjIn) {
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

lib := MCL.FromC(c)

input := FileOpen(A_ScriptDir "\input1.txt", "r").Read()
input := RTrim(input, "`r`n") ; Remove trailing newlines
input := StrSplit(input, "`n", "`r") ; Split input on newline

; Numerify all values
for k, v in input
	input[k] := v+0

MsgBox, % DllCall(lib.part1, "Ptr", &input, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &input, "CDecl Int")
