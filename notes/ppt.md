# Intro
- Static analysis
  - Analysing the code without running it.
  - Reverse engineering
  - Ghidra, IDA, Binja
- Dynamic analysis
  - Analysing the program at runtime
  - Process monitoring
  - Procmon, Procexp

# Analysing a binary
- What is PE?
  - Executable file format on windows. Linux has ELF.
  - https://docs.microsoft.com/en-us/windows/win32/debug/pe-format
  - DLLs vs EXE
    - Both follow PE format
    - EXE has an entrypoint which can acts as a starting point of process.
    - Process will own the entire virtual address space
    - DLLs let code break into modules and can be shared between processes.
    - DLL is loaded into address space of process it will be used

# PE-bear
- https://github.com/hasherezade/pe-bear-releases/releases/
- https://github.com/hasherezade

# Dumpbin
- This is a commandline tool that is a part of Windows SDK
- /headers
- /exports
- /imports

# Assembly
- x86
  - Intel came up with this architecture. Derived from 8086 microprocessors
  - 32 bit 
- x64
  - AMD came up with this. Hence generally referred as AMD64
  - 64 bit
  - Backward compatible with x86
- Intel Itanium
  - Remember me?
  - https://en.wikipedia.org/wiki/Itanium

- Hello World in assembly
  - x86 calling convention: https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170
  - x64 calling convention: https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170

# Ghidra
- https://ghidra-sre.org/
- Reverse engineering
- Decompiler
- Python Scripting: https://class.malware.re/2021/03/08/ghidra-scripting.html

# Example 1

# Example 2

# Example 3
