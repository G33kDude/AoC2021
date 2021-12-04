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
	int x = 0;
	int d = 0;
	for (int i = 0; i < pobjIn->cFields; i++) {
		LPTSTR command = (pobjIn->pFields[i]).pstrValue;
		int i = 0;

		while (command[i] < '0' || command[i] > '9') {
			if (command[++i] == 0) { return -2; }
		}
		
		int n = 0;
		while (command[i] >= '0' && command[i] <= '9') {
			n = n * 10 + command[i++] - '0';
		}
		
		if (command[0] == 'f') { // Forward
			x += n;
		} else if (command[0] == 'd') { // Down
			d += n;
		} else if (command[0] == 'u') { // Up
			d -= n;
		} else {
			return -1;
		}
	}

	return x*d;
}

MCL_EXPORT(part2);
TCHAR part2(Object *pobjIn) {
	int x = 0;
	int d = 0;
	int aim = 0;
	for (int i = 0; i < pobjIn->cFields; i++) {
		LPTSTR command = (pobjIn->pFields[i]).pstrValue;
		int i = 0;

		while (command[i] < '0' || command[i] > '9') {
			if (command[++i] == 0) { return -2; }
		}
		
		int n = 0;
		while (command[i] >= '0' && command[i] <= '9') {
			n = n * 10 + command[i++] - '0';
		}
		
		if (command[0] == 'f') { // Forward
			x += n;
			d += n * aim;
		} else if (command[0] == 'd') { // Down
			aim += n;
		} else if (command[0] == 'u') { // Up
			aim -= n;
		} else {
			return -1;
		}
	}

	return x*d;
}

)

lib := MCL.FromC(c)

obj := StrSplit(RTrim(FileOpen("input2.txt", "r").Read(), "`r`n"), "`n", "`r")

MsgBox, % DllCall(lib.part1, "Ptr", &obj, "CDecl Int")
MsgBox, % DllCall(lib.part2, "Ptr", &obj, "CDecl Int")

