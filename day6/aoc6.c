
#define UNICODE

#include <mcl.h>
#include <oaidl.h>
#include "ahk.h"
#define NULL 0


// Taken from cJson.ahk
void comobjset(IDispatch *pObj, BSTR key, VARIANT *value)
{
	// Get the DispID for DISPATCH_PROPERTYPUT
	DISPID dispid = 0;
	pObj->lpVtbl->GetIDsOfNames(pObj, NULL, &key, 1, 0, &dispid);

	// Set the property
	DISPPARAMS dispparams = {
		.cArgs = 1,
		.cNamedArgs = 0,
		.rgvarg = value};
	pObj->lpVtbl->Invoke(pObj, dispid, NULL, 0, DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);

	// Decrement the reference count of the object given by pfnGetObj
	if (value->vt == VT_DISPATCH)
	{
		value->pdispVal->lpVtbl->Release(value->pdispVal);
	}
	else if (value->vt == VT_I4 && (value->llVal > 2147483647 || value->llVal < -2147483648)) // Fix integer overflow
	{
		Field *field;
		if (obj_get_field_str((Object *)pObj, key, &field))
		{
			field->iValue = value->llVal;
		}
	}
}

// Taken from cJson.ahk
void comobjset_i(IDispatch *pObj, unsigned int key, VARIANT *value)
{
	// A buffer large enough to fit the longest uint64_t (18446744073709551615) plus null terminator
	short str[21];
	str[20] = 0;

	unsigned int n = key;

	// Extract the decimal values
	int i = 20;
	do
	{
		str[--i] = (short)(key % 10 + '0');
		key /= 10;
	} while (key != 0);

	comobjset(pObj, &str[i], value);
}

MCL_EXPORT(part1);
int part1(Object* input) {
    VARIANT baby = {.vt = VT_I4, .llVal = 8};

    for (int i = 0; i < 80; i++) {
        int fish_count = input->cFields;
        for (int j = 0; j < fish_count; j++)
        if (input->pFields[j].iValue == 0) {
            comobjset_i((IDispatch*)input, input->cFields+1, &baby);
            input->pFields[j].iValue = 6;
        } else {
            input->pFields[j].iValue--;
        }
    }

    return input->cFields;
}

MCL_EXPORT(part2);
int64_t part2(Object* input, Object* schools) {

    // Put initial fish set into appropriate schools
    for (int i = 0; i < input->cFields; i++) {
        int cycle = input->pFields[i].iValue;
        schools->pFields[cycle].iValue++;
    }

    // Over the first 256 days
    for (int day = 0; day < 256; day++) {
        int64_t breeding_fish = schools->pFields[0].iValue;
        for (int school_index = 1; school_index <= 8; school_index++) {
            schools->pFields[school_index-1].iValue = schools->pFields[school_index].iValue;
        }
        schools->pFields[6].iValue += breeding_fish;
        schools->pFields[8].iValue = breeding_fish;
    }

    int64_t sum = 0;
    for (int school_index = 0; school_index <= 8; school_index++) {
        sum += schools->pFields[school_index].iValue;
    }

    return sum;
}