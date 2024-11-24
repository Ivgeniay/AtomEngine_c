#include <stdio.h> 
#include <core/logger.h>
#include <core/asserts.h>


int main(void) { 

    KFATAL("A test message: %f", 3.14f);
    KERROR("A test message: %f", 3.14f);
    KWARN("A test message: %f", 3.14f);
    KINFO("A test message: %f", 3.14f);
    KDEBUG("A test message: %f", 3.14f);
    KTRACE("A test message: %f", 3.14f);
 
    char c = getchar();
    
    KASSERT(1 == 0);
    KASSERT(1 == 1);
    
    c = getchar();
    
    return 0;
}