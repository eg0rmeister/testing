#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <iostream>
#include <fstream>

int main() {
    llvm::LLVMContext context;
    llvm::Module module("llvm_example", context);
    llvm::IRBuilder<> builder(context);

    // Define the printf function signature
    std::vector<llvm::Type *> printfArgs;
    printfArgs.push_back(builder.getInt8Ty()->get(context, 8)); // Use i8* instead of ptr
    printfArgs.push_back(builder.getInt32Ty());
    auto printfType = llvm::FunctionType::get(builder.getInt32Ty(), printfArgs, true);
    auto *printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", &module);

    // Define the main function
    auto mainFuncType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    auto *mainFunc = llvm::Function::Create(mainFuncType, llvm::Function::ExternalLinkage, "main", &module);
    auto *mainBlock = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainBlock);

    // Call printf with "Hello world"
    auto *formatStr = builder.CreateGlobalString("Hello world\n");
    std::vector<llvm::Value *> printfArgsV;
    printfArgsV.push_back(formatStr);
    printfArgsV.push_back(builder.getInt32(0)); // Dummy argument for "%d" in printf format
    builder.CreateCall(printfFunc, printfArgsV, "printfCall");

    // Return 0 from main
    builder.CreateRet(builder.getInt32(0));

    // Save LLVM IR to a file
    std::error_code ec;
    llvm::raw_fd_ostream outputFile("llvm_example.ll", ec, llvm::sys::fs::OpenFlags());

    if (!ec) {
        module.print(outputFile, nullptr);
        outputFile.flush();
        outputFile.close();
        std::cout << "LLVM IR written to llvm_example.ll" << std::endl;
    } else {
        std::cerr << "Error writing to llvm_example.ll: " << ec.message() << std::endl;
    }

    return 0;
}
