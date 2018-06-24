//===-- TNTMCAsmInfo.h - TNT asm properties --------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the TNTMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_TNT_MCTARGETDESC_TNTMCASMINFO_H
#define LLVM_LIB_TARGET_TNT_MCTARGETDESC_TNTMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class TNTMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit TNTMCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif
