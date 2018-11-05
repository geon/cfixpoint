#include "fix.h"

#define makeFixWrap(numBits, fractionBits) \
makeFixWrapDeclaration(numBits, fractionBits) { \
	FixTypeName(numBits, fractionBits) b; \
	b.value = a; \
	return b; \
}

#define makeFixWrapNoFrac(numBits, fractionBits) \
makeFixWrapDeclaration(numBits, fractionBits) { \
	return a; \
}

makeFixWrap(16, 16)
makeFixWrap(16, 8)
makeFixWrap(32, 16)
makeFixWrapNoFrac(32, 0)
makeFixWrapNoFrac(16, 0)

#define makeFixUnwrap(numBits, fractionBits) \
makeFixUnwrapDeclaration(numBits, fractionBits) { \
	return a.value; \
}

#define makeFixUnwrapNoFrac(numBits, fractionBits) \
makeFixUnwrapDeclaration(numBits, fractionBits) { \
	return a; \
}

makeFixUnwrap(16, 16);
makeFixUnwrap(16, 8);
makeFixUnwrap(32, 16);
makeFixUnwrapNoFrac(32, 0);
makeFixUnwrapNoFrac(16, 0);

#define makeFixFromFloat(numBits, fractionBits) \
makeFixFromFloatDeclaration(numBits, fractionBits) { \
	return FixFunctionName(numBits, fractionBits, wrap)(a * (1 << fractionBits)); \
}

makeFixFromFloat(16, 16);
makeFixFromFloat(16, 8);
makeFixFromFloat(32, 16);
makeFixFromFloat(32, 0);
makeFixFromFloat(16, 0);

#define makeFixToFloat(numBits, fractionBits) \
makeFixToFloatDeclaration(numBits, fractionBits) { \
	return FixFunctionName(numBits, fractionBits, unwrap)(a) / ((float) (1 << fractionBits)); \
}

makeFixToFloat(16, 16);
makeFixToFloat(16, 8);
makeFixToFloat(32, 16);
makeFixToFloat(32, 0);
makeFixToFloat(16, 0);

#define makeFixMakeFromFix(numBits, fractionBits, fromNumBits, fromFractionBits) \
makeFixMakeFromFixDeclaration(numBits, fractionBits, fromNumBits, fromFractionBits) { \
	if (numBits < fromNumBits) { \
		FixStorageTypeName(fromNumBits) unwrapped = FixFunctionName(fromNumBits, fromFractionBits, unwrap)(a); \
		if (fractionBits < fromFractionBits) { \
			return FixFunctionName(numBits, fractionBits, wrap)(unwrapped >> (fromFractionBits - fractionBits)); \
		} else { \
			return FixFunctionName(numBits, fractionBits, wrap)(unwrapped << (fractionBits - fromFractionBits)); \
		} \
	} else { \
		FixStorageTypeName(numBits) unwrapped = FixFunctionName(fromNumBits, fromFractionBits, unwrap)(a); \
		if (fractionBits < fromFractionBits) { \
			return FixFunctionName(numBits, fractionBits, wrap)(unwrapped >> (fromFractionBits - fractionBits)); \
		} else { \
			return FixFunctionName(numBits, fractionBits, wrap)(unwrapped << (fractionBits - fromFractionBits)); \
		} \
	} \
}

makeFixMakeFromFix(16, 16, 16, 8);
makeFixMakeFromFix(16, 16, 32, 16);
makeFixMakeFromFix(16, 8, 16, 16);
makeFixMakeFromFix(16, 8, 32, 16);
makeFixMakeFromFix(32, 16, 16, 16);
makeFixMakeFromFix(32, 16, 16, 8);

#define makeFixAdd(aNumBits, aFractionBits, bNumBits, bFractionBits) \
makeFixAddDeclaration(aNumBits, aFractionBits, bNumBits, bFractionBits) { \
	FixStorageTypeName(aNumBits) aUnwrapped = FixFunctionName(aNumBits, aFractionBits, unwrap)(a); \
	FixStorageTypeName(bNumBits) bUnwrapped = FixFunctionName(bNumBits, bFractionBits, unwrap)(b); \
	if (aFractionBits < bFractionBits) { \
		return FixFunctionName(aNumBits, aFractionBits, wrap)(aUnwrapped + (bUnwrapped >> (bFractionBits - aFractionBits))); \
	} else { \
		return FixFunctionName(aNumBits, aFractionBits, wrap)(aUnwrapped + (bUnwrapped << (aFractionBits - bFractionBits))); \
	} \
}

makeFixAdd(16, 16, 16, 16);
makeFixAdd(16, 16, 16, 8);
makeFixAdd(16, 16, 32, 16);
makeFixAdd(16, 8, 16, 8);
makeFixAdd(16, 8, 16, 16);
makeFixAdd(16, 8, 32, 16);
makeFixAdd(32, 16, 32, 16);
makeFixAdd(32, 16, 16, 16);
makeFixAdd(32, 16, 16, 8);
