#NoEnv
SetBatchLines, -1

#Include MCL.ahk\MCL.ahk

MCL.CompilerPrefix := "/usr/bin/x86_64-w64-mingw32-"
MCL.CompilerSuffix := ""

c =
( %

#define UNICODE

#include <mcl.h>
#include "ahk.h"

MCL_EXPORT(part1);
TCHAR part1(Object *pobjIn) {
	int g = 0;
	int e = 0;

	for (int j = 0; pobjIn->pFields[0].pstrValue[j] != 0; j++) {
		int ones = 0;
		int zeds = 0;
		for (int i = 0; i < pobjIn->cFields; i++) {
			switch((pobjIn->pFields[i]).pstrValue[j]) {
				case '0': zeds++; break;
				case '1': ones++; break;
				default: return -1;
			}
		}
		g <<= 1; e <<= 1;
		if (ones > zeds) { g |= 1; e |= 0; }
		else { g |= 0; e |= 1; }
	}

	return g*e;
}

MCL_EXPORT(part2);
TCHAR part2(Object *pobjIn, int part) {
	// Increase column index j until reach first array item's null
	for (int j = 0; pobjIn->pFields[0].pstrValue[j] != 0; j++) {
		int ones = 0;
		int zeds = 0;
		TCHAR consider;

		// For all values in the input object
		for (int i = 0; i < pobjIn->cFields; i++) {
			// If the string has been truncated, skip it
			if (pobjIn->pFields[i].pstrValue[0] == 0) { continue; }

			// Count the bit in column j toward its total
			switch((pobjIn->pFields[i]).pstrValue[j]) {
				case '0': zeds++; break;
				case '1': ones++; break;
				default: return -1;
			}
		}

		// Check which bit counted higher
		if (part == 1) {
			consider = ones >= zeds ? '1' : '0';
		} else if (part == 2) {
			consider = ones >= zeds ? '0' : '1';
		} else {
			return -2;
		}

		// Truncate strings with the uncommon bit in column j
		int remaining = pobjIn->cFields;
		for (int i = 0; i < pobjIn->cFields; i++) {
			if (pobjIn->pFields[i].pstrValue[0] == 0) {
				remaining--;
			} else if (pobjIn->pFields[i].pstrValue[j] != consider) {
				pobjIn->pFields[i].pstrValue[0] = 0;
				remaining--;
			}
		}
		if (remaining == 1) { break; }
	}

	for (int i = 0; i < pobjIn->cFields; i++) {
		if (pobjIn->pFields[i].pstrValue[0] == 0) { continue; }
		
		int val = 0;
		for (int j = 0; pobjIn->pFields[i].pstrValue[j] > 0; j++) {
			val <<= 1;
			val |= (pobjIn->pFields[i].pstrValue[j] == '1') ? 1 : 0;
		}
		return val;
	}

	return -3;
}


)

lib := MCL.FromC(c)

obj := StrSplit(RTrim(FileOpen("input3.txt", "r").Read(), "`r`n"), "`n", "`r")
objb := obj.Clone()

MsgBox, % DllCall(lib.part1, "Ptr", &obj, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &obj, "Int", 1, "CDecl Int") * DllCall(lib.part2, "Ptr", &objb, "Int", 2, "CDecl Int")

