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
call "%VCPKG_DIR%\vcpkg.exe" install sdl3 "sdl3-image[png,jpeg]" sdl3-mixer sdl3-ttf --triplet x64-windows
if exist build\build-debug rmdir /s /q build\build-debug
if exist build\build-release rmdir /s /q build\build-release
mkdir build
echo Configuring Debug...
cmake -B build\build-debug ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DVCPKG_TARGET_TRIPLET=x64-windows^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
echo Configuring Release...
cmake -B build\build-release ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DVCPKG_TARGET_TRIPLET=x64-windows ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo Generating build.bat for building in release mode....
(
echo @echo off
echo echo building project in Release mode...
echo pushd build\build-release
echo cmake --build .
echo popd
) > build.bat

echo Generating buildd.bat for building in debug mode....
(
echo @echo off
echo echo building project in debug mode...
echo pushd build\build-debug
echo cmake --build .
echo popd
) > buildd.bat

echo Generating run.bat for running in release mode....
(
echo @echo off
echo echo Running project in Release mode...
echo pushd bin\Release
echo 2dShooter.exe
echo popd
) > run.bat

echo Generating rund.bat for running in debug mode....
(
echo @echo off
echo echo Running project in Debug mode...
echo pushd bin\Debug
echo 2dShooter.exe
echo popd
) > rund.bat

echo done.
