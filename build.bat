@echo off
pushd build\build-release
@echo Compiling and building the project in Release mode...
cmake --build .
popd