# makefile
# Created by IBM WorkFrame/2 MakeMake at 16:08:21 on 8 June 1997
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES: .c .obj 

.all: \
    convert.exe

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ti /Fo"%|dpfF.obj" /C %s

convert.exe: \
    convert.obj
    @echo " Link::Linker "
    icc.exe @<<
     /B" /de /NOE setargv.obj"
     /Feconvert.exe 
     convert.obj
<<

convert.obj: \
    convert.c
