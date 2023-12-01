#include <fstream>
#include <iostream>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

int main() {
  llvm::LLVMContext context_;
  llvm::Module module_("llvm_example", context_);
  llvm::IRBuilder<> builder_(context_);

  auto function_type =
      llvm::FunctionType::get(llvm::Type::getVoidTy(context_), false);

  // Create main function
  auto function_llvm = llvm::Function::Create(
      function_type, llvm::Function::ExternalLinkage, "main", module_);

  auto entry = llvm::BasicBlock::Create(context_, "entry", function_llvm);

  builder_.SetInsertPoint(entry);

  auto add_function_type = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(context_),
      {builder_.getInt32Ty(), builder_.getInt32Ty()}, false);
  
  //auto add_function = llvm::Function::Create(
  //    add_function_type, llvm::Function::ExternalLinkage, "add", module_);
  
  // builder_.CreateRet(llvm::ConstantInt::get(context_, llvm::APInt()));
  
  // Save LLVM IR to a file
  std::error_code ec;
  llvm::raw_fd_ostream outputFile("llvm_example.ll", ec,
                                  llvm::sys::fs::OpenFlags());

  if (!ec) {
    module_.print(outputFile, nullptr);
    outputFile.flush();
    outputFile.close();
    std::cout << "LLVM IR written to llvm_example.ll" << std::endl;
  } else {
    std::cerr << "Error writing to llvm_example.ll: " << ec.message()
              << std::endl;
  }

  return 0;
}
