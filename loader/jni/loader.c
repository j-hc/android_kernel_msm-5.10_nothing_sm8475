#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/system_properties.h>
#include <unistd.h>

static bool prop_get_set(const char* name) {
    char val[8];
    if (!__system_property_get(name, val)) return false;
    if (__system_property_set(name, val) == -1) return false;
    return true;
}

int main(void) {
    if (syscall(SYS_delete_module, "goodix_core", O_TRUNC) != 0) {
        fprintf(stderr, "e1: %s\n", strerror(errno));
    }
    // xxd -i
    if (syscall(SYS_init_module, GOODIX_KO, GOODIX_KO_LEN, "") != 0) {
        fprintf(stderr, "e2: %s\n", strerror(errno));
        return 1;
    }

    sleep(2);

    if (!prop_get_set("sys.touch.fod_en.enable")) {
        fprintf(stderr, "g1: %s\n", strerror(errno));
    }
    if (!prop_get_set("sys.touch.single_en.enable")) {
        fprintf(stderr, "g2: %s\n", strerror(errno));
    }

    printf("Loaded!\n");
    printf("by j-hc (github.com/j-hc)");

    return 0;
}
