#!/bin/bash
set -e

VCPKG_DIR="$PWD/externals/vcpkg"

echo "Initializing the project and building..."
echo "checking vcpkg..."

if [ ! -f "$VCPKG_DIR/vcpkg" ]; then
    echo "vcpkg not found... cloning vcpkg now"
    git clone https://github.com/microsoft/vcpkg.git externals/vcpkg
    pushd "$VCPKG_DIR"
    ./bootstrap-vcpkg.sh
    popd
fi

echo "vcpkg is ready."
echo "Installing dependencies..."
"$VCPKG_DIR/vcpkg" install sdl3 sdl3-image sdl3-mixer sdl3-ttf --triplet x64-linux

rm -rf build/build-debug build/build-release
mkdir -p build

echo "Configuring Debug..."
cmake -B build/build-debug \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DVCPKG_TARGET_TRIPLET=x64-linux

echo "Configuring Release..."
cmake -B build/build-release \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DVCPKG_TARGET_TRIPLET=x64-linux

echo "Creating build.sh for building in release..."
cat > build.sh << 'EOF'
#!/bin/sh
set -e
CURRENTDIR="$PWD"
cd build/build-release
echo "Compiling and building project in Release Mode..."
cmake --build .
cd "$CURRENTDIR"
EOF
echo "Created build.sh successfully."

echo "Creating build.sh for building in debug..."
cat > buildd.sh << 'EOF'
#!/bin/sh
set -e
CURRENTDIR="$PWD"
cd build/build-debug
echo "Compiling and building project in debug Mode..."
cmake --build .
cd "$CURRENTDIR"
EOF
echo "Created buildd.sh successfully."

echo "Creating run.sh for running the program in Release..."
cat > run.sh << 'EOF'
#!/bin/sh
set -e
CURRENTDIR="$PWD"
cd bin/Release
echo "Running the project in Release Mode..."
./2dShooter
cd "$CURRENTDIR"
EOF
echo "Created run.sh successfully."

echo "Creating rund.sh for running the program in Debug..."
cat > rund.sh << 'EOF'
#!/bin/sh
set -e
CURRENTDIR="$PWD"
cd bin/Debug
echo "Running the project in Debug Mode..."
./2dShooter
cd "$CURRENTDIR"
EOF
echo "Created rund.sh successfully."

chmod +x build.sh
chmod +x buildd.sh
chmod +x run.sh
chmod +x rund.sh

echo "done."