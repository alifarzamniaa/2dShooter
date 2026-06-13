@echo off
pushd build\build-debug
@echo Compiling and building the project in debug mode...
cmake --build .
popd