set(LLVM_TARGET_DEFINITIONS TNT.td)

tablegen(LLVM TNTGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TNTGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TNTGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TNTGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM TNTGenCallingConv.inc -gen-callingconv)
tablegen(LLVM TNTGenSubtargetInfo.inc -gen-subtarget)
add_public_tablegen_target(TNTCommonTableGen)

add_llvm_target(TNTCodeGen
  TNTBranchSelector.cpp
  TNTISelDAGToDAG.cpp
  TNTISelLowering.cpp
  TNTInstrInfo.cpp
  TNTFrameLowering.cpp
  TNTMachineFunctionInfo.cpp
  TNTRegisterInfo.cpp
  TNTSubtarget.cpp
  TNTTargetMachine.cpp
  TNTAsmPrinter.cpp
  TNTMCInstLower.cpp
  )

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
