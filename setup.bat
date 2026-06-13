@echo off
set VCPKG_ROOT=
set VCPKG_DIR=%CD%\externals\vcpkg
echo Initializing the project and building...
echo checking vcpkg...
if not exist "%VCPKG_DIR%\vcpkg.exe" (
    echo vcpkg not found... cloning the vcpkg now
    git clone https://github.com/microsoft/vcpkg.git externals\vcpkg
    pushd "%VCPKG_DIR%"
    call bootstrap-vcpkg.bat
    popd
) 
echo vcpkg is ready.
echo Installing dependencies...
call "%VCPKG_DIR%\vcpkg.exe" install sdl3 sdl3-image sdl3-mixer sdl3-ttf --triplet x64-windows
if exist build\build-debug rmdir /s /q build\build-debug
if exist build\build-release rmdir /s /q build\build-release
mkdir build
echo Configuring Debug...
cmake -B build\build-debug ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DVCPKG_TARGET_TRIPLET=x64-windows
echo Configuring Release...
cmake -B build\build-release ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DVCPKG_TARGET_TRIPLET=x64-windows
echo done.