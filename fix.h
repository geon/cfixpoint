#ifndef _FIX_H_
#define _FIX_H_

#include <stdint.h>

#define FixStorageTypeName(numBits) int##numBits##_t
#define FixTypeName(numBits, fractionBits) Fix_##numBits##_##fractionBits
#define FixFunctionName(numBits, fractionBits, functionName) fix##_##numBits##_##fractionBits##_##functionName

#define makeFixTypedef(numBits, fractionBits) \
typedef struct FixTypeName(numBits, fractionBits)  {FixStorageTypeName(numBits) value;} FixTypeName(numBits, fractionBits);

#define makeFixNoFracTypedef(numBits, fractionBits) \
typedef FixStorageTypeName(numBits) FixTypeName(numBits, fractionBits);

makeFixTypedef(16, 16)
makeFixTypedef(16, 8)
makeFixTypedef(32, 16)
makeFixNoFracTypedef(32, 0)
makeFixNoFracTypedef(16, 0)

#define makeFixWrapDeclaration(numBits, fractionBits) \
FixTypeName(numBits, fractionBits) FixFunctionName(numBits, fractionBits, wrap)(FixStorageTypeName(numBits) a)

makeFixWrapDeclaration(16, 16);
makeFixWrapDeclaration(16, 8);
makeFixWrapDeclaration(32, 16);
makeFixWrapDeclaration(32, 0);
makeFixWrapDeclaration(16, 0);

#define makeFixUnwrapDeclaration(numBits, fractionBits) \
FixStorageTypeName(numBits) FixFunctionName(numBits, fractionBits, unwrap)(FixTypeName(numBits, fractionBits) a)

makeFixUnwrapDeclaration(16, 16);
makeFixUnwrapDeclaration(16, 8);
makeFixUnwrapDeclaration(32, 16);
makeFixUnwrapDeclaration(32, 0);
makeFixUnwrapDeclaration(16, 0);

#define makeFixFromFloatDeclaration(numBits, fractionBits) \
FixTypeName(numBits, fractionBits) FixFunctionName(numBits, fractionBits, fromFloat)(float a)

makeFixFromFloatDeclaration(16, 16);
makeFixFromFloatDeclaration(16, 8);
makeFixFromFloatDeclaration(32, 16);
makeFixFromFloatDeclaration(32, 0);
makeFixFromFloatDeclaration(16, 0);

#define makeFixToFloatDeclaration(numBits, fractionBits) \
float FixFunctionName(numBits, fractionBits, toFloat)(FixTypeName(numBits, fractionBits) a)

makeFixToFloatDeclaration(16, 16);
makeFixToFloatDeclaration(16, 8);
makeFixToFloatDeclaration(32, 16);
makeFixToFloatDeclaration(32, 0);
makeFixToFloatDeclaration(16, 0);

#define makeFixMakeFromFixDeclaration(numBits, fractionBits, fromNumBits, fromFractionBits) \
FixTypeName(numBits, fractionBits) FixFunctionName(numBits, fractionBits, makeFromFix##_##fromNumBits##_##fromFractionBits)(FixTypeName(fromNumBits, fromFractionBits) a)

makeFixMakeFromFixDeclaration(16, 16, 16, 8);
makeFixMakeFromFixDeclaration(16, 16, 32, 16);
makeFixMakeFromFixDeclaration(16, 8, 16, 16);
makeFixMakeFromFixDeclaration(16, 8, 32, 16);
makeFixMakeFromFixDeclaration(32, 16, 16, 16);
makeFixMakeFromFixDeclaration(32, 16, 16, 8);

#define makeFixAddDeclaration(aNumBits, aFractionBits, bNumBits, bFractionBits) \
FixTypeName(aNumBits, aFractionBits) FixFunctionName(aNumBits, aFractionBits, add##_##bNumBits##_##bFractionBits)(FixTypeName(aNumBits, aFractionBits) a, FixTypeName(bNumBits, bFractionBits) b)

makeFixAddDeclaration(16, 16, 16, 16);
makeFixAddDeclaration(16, 16, 16, 8);
makeFixAddDeclaration(16, 16, 32, 16);
makeFixAddDeclaration(16, 8, 16, 8);
makeFixAddDeclaration(16, 8, 16, 16);
makeFixAddDeclaration(16, 8, 32, 16);
makeFixAddDeclaration(32, 16, 32, 16);
makeFixAddDeclaration(32, 16, 16, 16);
makeFixAddDeclaration(32, 16, 16, 8);

#endif
