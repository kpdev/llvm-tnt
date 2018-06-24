//===-- TNTRegisterInfo.td - TNT Register defs -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the TNT register file
//===----------------------------------------------------------------------===//

class TNTReg<bits<4> num, string n> : Register<n> {
  field bits<4> Num = num;
  let Namespace = "TNT";
}

class TNTRegWithSubregs<bits<4> num, string n, list<Register> subregs> 
  : RegisterWithSubRegs<n, subregs> {
  field bits<4> Num = num;
  let Namespace = "TNT";
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

def PCB  : TNTReg<0,  "r0">;
def SPB  : TNTReg<1,  "r1">;
def SRB  : TNTReg<2,  "r2">;
def CGB  : TNTReg<3,  "r3">;
def FPB  : TNTReg<4,  "r4">;
def R5B  : TNTReg<5,  "r5">;
def R6B  : TNTReg<6,  "r6">;
def R7B  : TNTReg<7,  "r7">;
def R8B  : TNTReg<8,  "r8">;
def R9B  : TNTReg<9,  "r9">;
def R10B : TNTReg<10, "r10">;
def R11B : TNTReg<11, "r11">;
def R12B : TNTReg<12, "r12">;
def R13B : TNTReg<13, "r13">;
def R14B : TNTReg<14, "r14">;
def R15B : TNTReg<15, "r15">;

def subreg_8bit : SubRegIndex<8> { let Namespace = "TNT"; }

let SubRegIndices = [subreg_8bit] in {
def PC  : TNTRegWithSubregs<0,  "r0",  [PCB]>;
def SP  : TNTRegWithSubregs<1,  "r1",  [SPB]>;
def SR  : TNTRegWithSubregs<2,  "r2",  [SRB]>;
def CG  : TNTRegWithSubregs<3,  "r3",  [CGB]>;
def FP  : TNTRegWithSubregs<4,  "r4",  [FPB]>;
def R5  : TNTRegWithSubregs<5,  "r5",  [R5B]>;
def R6  : TNTRegWithSubregs<6,  "r6",  [R6B]>;
def R7  : TNTRegWithSubregs<7,  "r7",  [R7B]>;
def R8  : TNTRegWithSubregs<8,  "r8",  [R8B]>;
def R9  : TNTRegWithSubregs<9,  "r9",  [R9B]>;
def R10 : TNTRegWithSubregs<10, "r10", [R10B]>;
def R11 : TNTRegWithSubregs<11, "r11", [R11B]>;
def R12 : TNTRegWithSubregs<12, "r12", [R12B]>;
def R13 : TNTRegWithSubregs<13, "r13", [R13B]>;
def R14 : TNTRegWithSubregs<14, "r14", [R14B]>;
def R15 : TNTRegWithSubregs<15, "r15", [R15B]>;
}

def GR8 : RegisterClass<"TNT", [i8], 8,
   // Volatile registers
  (add R12B, R13B, R14B, R15B, R11B, R10B, R9B, R8B, R7B, R6B, R5B,
   // Frame pointer, sometimes allocable
   FPB,
   // Volatile, but not allocable
   PCB, SPB, SRB, CGB)>;

def GR16 : RegisterClass<"TNT", [i16], 16,
   // Volatile registers
  (add R12, R13, R14, R15, R11, R10, R9, R8, R7, R6, R5,
   // Frame pointer, sometimes allocable
   FP,
   // Volatile, but not allocable
   PC, SP, SR, CG)>;
