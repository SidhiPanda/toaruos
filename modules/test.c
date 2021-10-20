#include <kernel/printf.h>
#include <kernel/module.h>
#include <kernel/assert.h>
#include <kernel/misc.h>

static int init(int argc, char * argv[]) {
	dprintf("Hello, modules.\n");
	dprintf("Received %d arguments.\n", argc);

	if (argc > 1 && !strcmp(argv[1], "--traceback")) {
		arch_dump_traceback();
	} else if (argc > 1 && !strcmp(argv[1], "--fail")) {
		return 1;
	} else if (argc > 1 && !strcmp(argv[1], "--crash")) {
		*(volatile int*)0x60000000 = 42;
	} else if (argc > 1 && !strcmp(argv[1], "--assert")) {
		assert(0 && "Intentional failure.");
	}

	return 0;
}

static int fini(void) {
	return 0;
}

struct Module metadata = {
	.name = "test",
	.init = init,
	.fini = fini,
};

