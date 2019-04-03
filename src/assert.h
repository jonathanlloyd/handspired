#ifndef ASSERT_H
#define ASSERT_H

#define STR(x) #x
#define ASSERT(expression) if (!(expression)) { printf("Assertion \"%s\" failed. %s line %d\n", STR(expression), __FILE__, __LINE__); exit(1);}

#endif
