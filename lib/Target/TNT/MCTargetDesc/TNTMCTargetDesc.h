//===-- TNTMCTargetDesc.h - TNT Target Descriptions -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TNT specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_TNT_MCTARGETDESC_TNTMCTARGETDESC_H
#define LLVM_LIB_TARGET_TNT_MCTARGETDESC_TNTMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;

extern Target TheTNTTarget;

} // End llvm namespace

// Defines symbolic names for TNT registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "TNTGenRegisterInfo.inc"

// Defines symbolic names for the TNT instructions.
#define GET_INSTRINFO_ENUM
#include "TNTGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TNTGenSubtargetInfo.inc"

#endif
