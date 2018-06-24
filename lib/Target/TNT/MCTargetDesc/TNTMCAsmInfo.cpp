//===-- TNTMCAsmInfo.cpp - TNT asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the TNTMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "TNTMCAsmInfo.h"
using namespace llvm;

void TNTMCAsmInfo::anchor() { }

TNTMCAsmInfo::TNTMCAsmInfo(const Triple &TT) {
  PointerSize = CalleeSaveStackSlotSize = 2;

  CommentString = ";";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;
}
