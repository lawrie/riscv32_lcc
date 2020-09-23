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
make clobber
make lburg
make CC="$CROSS_COMPILE" rcc
make CC="$CROSS_COMPILE" lcc
make CC="$CROSS_COMPILE" u_cpp
make clean
cd bin/libs
make clean
cd ../../..
tar -c -f riscv32_lcc.tar ../riscv32_lcc/lib ../riscv32_lcc/examples ../riscv32_lcc/binutils/bin ../riscv32_lcc/lcc/bin/include ../riscv32_lcc/lcc/bin/lcc ../riscv32_lcc/lcc/bin/rcc ../riscv32_lcc/lcc/bin/ucpp

