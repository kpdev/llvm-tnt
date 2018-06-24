//===-- TNTELFObjectWriter.cpp - TNT ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TNTMCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class TNTELFObjectWriter : public MCELFObjectTargetWriter {
public:
  TNTELFObjectWriter(uint8_t OSABI);

  ~TNTELFObjectWriter() override;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

TNTELFObjectWriter::TNTELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, ELF::EM_TNT,
                              /*HasRelocationAddend*/ false) {}

TNTELFObjectWriter::~TNTELFObjectWriter() {}

unsigned TNTELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  // determine the type of the relocation
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("invalid fixup kind!");
  case FK_SecRel_8:
    return ELF::R_X86_64_64;
  case FK_SecRel_4:
    return ELF::R_X86_64_PC32;
  case FK_Data_8:
    return IsPCRel ? ELF::R_X86_64_PC64 : ELF::R_X86_64_64;
  case FK_Data_4:
    return IsPCRel ? ELF::R_X86_64_PC32 : ELF::R_X86_64_32;
  }
}

MCObjectWriter *llvm::createTNTELFObjectWriter(raw_pwrite_stream &OS,
                                               uint8_t OSABI, bool IsLittleEndian) {
  MCELFObjectTargetWriter *MOTW = new TNTELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, IsLittleEndian);
}
