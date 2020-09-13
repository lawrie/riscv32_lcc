#include <string.h>

#ifndef LCCDIR
#define LCCDIR "/riscv32_lcc/lcc/bin"
#endif

char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };

char inputs[256] = "";

char *cpp[] = {
       LCCDIR "/ucpp",
	"-DLANGUAGE_C",
	"-D_LANGUAGE_C",
	"-DUNIX",
	"-D_UNIX",
	"-Dunix",
    "-zI",
	"$1",			/* preprocessor include directory */
	"$2",			/* preprocessor input file */
        "-o",
	"$3",			/* preprocessor output file */
	0
};

char *com[] =  {
	LCCDIR "/rcc",
	"-target=riscv32",
	"$1",			/* other options handed through */
	"$2",			/* compiler input file */
	"$3",			/* compiler output file */
	"",
	0
};

char *include[] = { "-I" LCCDIR "/include", 0 };

char *as[] = {
	LCCDIR "/../../binutils/bin/as",
	"-o", "$3",		/* assembler output file */
	"$1",			/* other options handed through */
	"$2",			/* assembler input file */
	0
};

char *ld[] = {
	LCCDIR "/../../binutils/bin/ld",
	"-e",
	"-o", "$3",		/* linker output file */
        "-l", LCCDIR "/../../lib/c.lib",
        "$1",			/* other options handed through */
	LCCDIR "/../../lib/crt0.o",
	"$2",
	0
};

extern char *concat(char *, char *);

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/ucpp");
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat(&arg[8], "/rcc");
                as[0] = concat(&arg[8], "/../../binutils/bin/as");
                ld[0] = concat(&arg[8], "/../../binutils/bin/ld");
		ld[5] = concat(&arg[8], "/../../lib/c.lib");
		ld[7] = concat(&arg[8], "/../../lib/crt0.o");
	} else if (strcmp(arg,"-g")==0);
        else
		return 0;
	return 1;
}
