@echo off
pushd bin\Release
@echo Runnning the project in Release mode...
cmake --build .
popd