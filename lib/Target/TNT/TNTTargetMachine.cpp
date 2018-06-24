//===-- TNTTargetMachine.cpp - Define TargetMachine for TNT ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Top-level implementation for the TNT target.
//
//===----------------------------------------------------------------------===//

#include "TNTTargetMachine.h"
#include "TNT.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeTNTTarget() {
  // Register the target.
  RegisterTargetMachine<TNTTargetMachine> X(TheTNTTarget);
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

TNTTargetMachine::TNTTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         CodeModel::Model CM,
                                         CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, "e-m:e-p:16:16-i32:16:32-a:16-n8:16", TT, CPU, FS,
                        Options, getEffectiveRelocModel(RM), CM, OL),
      TLOF(make_unique<TargetLoweringObjectFileELF>()),
      // FIXME: Check DataLayout string.
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

TNTTargetMachine::~TNTTargetMachine() {}

namespace {
/// TNT Code Generator Pass Configuration Options.
class TNTPassConfig : public TargetPassConfig {
public:
  TNTPassConfig(TNTTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  TNTTargetMachine &getTNTTargetMachine() const {
    return getTM<TNTTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *TNTTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TNTPassConfig(this, PM);
}

bool TNTPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createTNTISelDag(getTNTTargetMachine(), getOptLevel()));
  return false;
}

void TNTPassConfig::addPreEmitPass() {
  // Must run branch selection immediately preceding the asm printer.
  addPass(createTNTBranchSelectionPass(), false);
}
