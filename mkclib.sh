CROSS_COMPILE="~/Ulx3sSmp/buildroot/output/host/bin/riscv32-linux-gcc -march=rv32im -mabi=ilp32"
cd binutils
make MAKE="make CC=\"gcc -m32\"" clean install
cd ../lcc
make clean all
cd ..





