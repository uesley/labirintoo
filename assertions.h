#ifndef ASSERTIONS_H
#define ASSERTIONS_H

void assertTrue(int var) {
    if (!var) {
        printf("esperado: true, encontrado: %d", var);
        exit(1);
    }
    printf(".");
}

void assertFalse(int var) {
    if (var) {
        printf("esperado: false, encontrado: %d", var);
        exit(1);
    }
    printf(".");
}

void assertEquals(int expected, int value) {
    if (value != expected) {
        printf("esperado: %d, encontrado: %d", expected, value);
        exit(1);
    }
    printf(".");
}

void assertGreaterThan(int expected, int value) {
    if (value <= expected) {
        printf(", esperado maior que %d, encontrado: %d", expected, value);
        exit(1);
    }
    printf(".");
}

#endif /* ASSERTIONS_H */

