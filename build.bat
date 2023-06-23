@echo off
pushd build
cl  /Zi ../xor.cpp /nologo
xor.exe 
popd
