//===-- TNTMCTargetDesc.cpp - TNT Target Descriptions ---------------===//
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

#include "TNTMCTargetDesc.h"
#include "InstPrinter/TNTInstPrinter.h"
#include "TNTMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "TNTGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TNTGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TNTGenRegisterInfo.inc"

static MCInstrInfo *createTNTMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTNTMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTNTMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTNTMCRegisterInfo(X, TNT::PC);
  return X;
}

static MCSubtargetInfo *
createTNTMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createTNTMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCInstPrinter *createTNTMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new TNTInstPrinter(MAI, MII, MRI);
  return nullptr;
}

extern "C" void LLVMInitializeTNTTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<TNTMCAsmInfo> X(TheTNTTarget);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTNTTarget, createTNTMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTNTTarget,
                                    createTNTMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTNTTarget,
                                          createTNTMCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheTNTTarget,
                                        createTNTMCInstPrinter);
}
