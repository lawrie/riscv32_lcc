CROSS_COMPILE="~/Ulx3sSmp/buildroot/output/host/bin/riscv32-linux-gcc -march=rv32im -mabi=ilp32"
cd binutils
make MAKE="make CC=\"gcc -m32\"" clean install
cd ../lcc
make clean all
cd ..
mkdir -p lib
cp lcc/bin/libs/c.lib lib
cp lcc/bin/libs/crt0.o lib
cd binutils
make MAKE="make CC=\"$CROSS_COMPILE\"" clean install
make clean
cd ../lcc
make clean
make lburg
make MAKE="make CC=\"$CROSS_COMPILE\"" rcc
make MAKE="make CC=\"$CROSS_COMPILE\"" lcc
make MAKE="make CC=\"$CROSS_COMPILE\"" ucpp
make MAKE="make CC=\"$CROSS_COMPILE\"" cpp
make clean
cd bin/libs
make clean
cd ../../..
tar -c -f riscv32_lcc.tar lib examples binutils/bin lcc/bin/include lcc/bin/lcc lcc/bin/rcc lcc/bin/cpp lcc/bin/ucpp







