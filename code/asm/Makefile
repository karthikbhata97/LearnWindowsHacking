hw-asm:
	nasm -fwin64 .\hello_world.asm
	"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\link.exe" /subsystem:console  /entry:main .\hello_world.obj "C:\Program Files (x86)\Windows Kits\10\lib\10.0.19041.0\um\x64\kernel32.lib"

clean:
	del hello_world.obj
	del hello_world.exe
  
