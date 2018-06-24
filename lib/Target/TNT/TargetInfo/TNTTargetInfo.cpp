//===-- TNTTargetInfo.cpp - TNT Target Implementation ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TNT.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target llvm::TheTNTTarget;

extern "C" void LLVMInitializeTNTTargetInfo() { 
  RegisterTarget<Triple::tnt> 
    X(TheTNTTarget, "TNT", "TNT [experimental target for Standard Capital Group Inc]");
}
