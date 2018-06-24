//==-- TNT.h - Top-level interface for TNT representation --*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM TNT backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_TNT_TNT_H
#define LLVM_LIB_TARGET_TNT_TNT_H

#include "MCTargetDesc/TNTMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace TNTCC {
  // TNT specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,

    COND_INVALID = -1
  };
}

namespace llvm {
  class TNTTargetMachine;
  class FunctionPass;
  class formatted_raw_ostream;

  FunctionPass *createTNTISelDag(TNTTargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createTNTBranchSelectionPass();

} // end namespace llvm;

#endif
