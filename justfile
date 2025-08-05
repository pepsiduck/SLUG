run:
    clear
    make -C build -j16
    mv build/SLUG SLUG

setup:
    mkdir -p build/
    cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
