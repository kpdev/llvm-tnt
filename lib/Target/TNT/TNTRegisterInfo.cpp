//===-- TNTRegisterInfo.cpp - TNT Register Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TNT implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "TNTRegisterInfo.h"
#include "TNT.h"
#include "TNTMachineFunctionInfo.h"
#include "TNTTargetMachine.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "TNT-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "TNTGenRegisterInfo.inc"

// FIXME: Provide proper call frame setup / destroy opcodes.
TNTRegisterInfo::TNTRegisterInfo()
  : TNTGenRegisterInfo(TNT::PC) {}

const MCPhysReg*
TNTRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  const TNTFrameLowering *TFI = getFrameLowering(*MF);
  const Function* F = MF->getFunction();
  static const MCPhysReg CalleeSavedRegs[] = {
    TNT::FP, TNT::R5, TNT::R6, TNT::R7,
    TNT::R8, TNT::R9, TNT::R10, TNT::R11,
    0
  };
  static const MCPhysReg CalleeSavedRegsFP[] = {
    TNT::R5, TNT::R6, TNT::R7,
    TNT::R8, TNT::R9, TNT::R10, TNT::R11,
    0
  };
  static const MCPhysReg CalleeSavedRegsIntr[] = {
    TNT::FP,  TNT::R5,  TNT::R6,  TNT::R7,
    TNT::R8,  TNT::R9,  TNT::R10, TNT::R11,
    TNT::R12, TNT::R13, TNT::R14, TNT::R15,
    0
  };
  static const MCPhysReg CalleeSavedRegsIntrFP[] = {
    TNT::R5,  TNT::R6,  TNT::R7,
    TNT::R8,  TNT::R9,  TNT::R10, TNT::R11,
    TNT::R12, TNT::R13, TNT::R14, TNT::R15,
    0
  };

  // TODO: XXX
  return CalleeSavedRegs;

  //if (TFI->hasFP(*MF))
  //  return (F->getCallingConv() == CallingConv::TNT_INTR ?
  //          CalleeSavedRegsIntrFP : CalleeSavedRegsFP);
  //else
  //  return (F->getCallingConv() == CallingConv::TNT_INTR ?
  //          CalleeSavedRegsIntr : CalleeSavedRegs);

}

BitVector TNTRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  const TNTFrameLowering *TFI = getFrameLowering(MF);

  // Mark 4 special registers with subregisters as reserved.
  Reserved.set(TNT::PCB);
  Reserved.set(TNT::SPB);
  Reserved.set(TNT::SRB);
  Reserved.set(TNT::CGB);
  Reserved.set(TNT::PC);
  Reserved.set(TNT::SP);
  Reserved.set(TNT::SR);
  Reserved.set(TNT::CG);

  // Mark frame pointer as reserved if needed.
  if (TFI->hasFP(MF)) {
    Reserved.set(TNT::FPB);
    Reserved.set(TNT::FP);
  }

  return Reserved;
}

const TargetRegisterClass *
TNTRegisterInfo::getPointerRegClass(const MachineFunction &MF, unsigned Kind)
                                                                         const {
  return &TNT::GR16RegClass;
}

void
TNTRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  MachineInstr &MI = *II;
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MBB.getParent();
  const TNTFrameLowering *TFI = getFrameLowering(MF);
  DebugLoc dl = MI.getDebugLoc();
  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();

  unsigned BasePtr = (TFI->hasFP(MF) ? TNT::FP : TNT::SP);
  int Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex);

  // Skip the saved PC
  Offset += 2;

  if (!TFI->hasFP(MF))
    Offset += MF.getFrameInfo()->getStackSize();
  else
    Offset += 2; // Skip the saved FP

  // Fold imm into offset
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (MI.getOpcode() == TNT::ADD16ri) {
    // This is actually "load effective address" of the stack slot
    // instruction. We have only two-address instructions, thus we need to
    // expand it into mov + add
    const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();

    MI.setDesc(TII.get(TNT::MOV16rr));
    MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);

    if (Offset == 0)
      return;

    // We need to materialize the offset via add instruction.
    unsigned DstReg = MI.getOperand(0).getReg();
    if (Offset < 0)
      BuildMI(MBB, std::next(II), dl, TII.get(TNT::SUB16ri), DstReg)
        .addReg(DstReg).addImm(-Offset);
    else
      BuildMI(MBB, std::next(II), dl, TII.get(TNT::ADD16ri), DstReg)
        .addReg(DstReg).addImm(Offset);

    return;
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
}

unsigned TNTRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TNTFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? TNT::FP : TNT::SP;
}
