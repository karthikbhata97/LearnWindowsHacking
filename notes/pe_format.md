# PE Format 
- Ref: https://docs.microsoft.com/en-us/windows/win32/debug/pe-format

- InDepth: https://www.delphibasics.info/home/delphibasicsarticles/anin-depthlookintothewin32portableexecutablefileformat-part1

Two types:
- DOS compatible
- PE32: 32 bit address space
- PE32+: 64 bit address space

Parts of PE:
- Headers
- Data directories
- Section table


- Section headers
  - Characeristics
- Imports
  - DLL comes to picture
    - Static vs Dynamic
    - Microservice architecture
    - IAT helps in doscovering
  - Binding


- Imports table doesn't mean other DLLs are not used
  - Indirect
  - LoadLibrary
