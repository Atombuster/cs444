#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef CTEST_ENABLE
#include "ctest.h"
#endif
#include "block.h"
#include "image.h"

#ifdef CTEST_ENABLE

void test_image_open(void){
    CTEST_ASSERT(image_open("test.txt", 0) != -1, "testing if file can be created/opened");
    image_close();
    CTEST_ASSERT(image_open("test.txt", 1) != -1, "testing if file can be created/overwritten");
    image_close();
}
void test_image_close(void){
    image_open("test.txt", 0);
    CTEST_ASSERT(image_close() != -1, "testing if file can be closed");
    CTEST_ASSERT(image_close() == -1, "testing if file is already closed");
}
//note to self ask how to write better test for bread, bwrite in class.
void test_bread(void){
    unsigned char block[4096];
    image_open("test.txt", 0);
    CTEST_ASSERT(bread(1, block) != NULL, "testing if bread works");
    image_close();

}
void test_bwrite(void){
    //I thinks this works
    unsigned char block[4096];
    image_open("test.txt", 0);
    bwrite(1, block);
    CTEST_ASSERT(bread(1, block) != NULL, "testing if bwrite works");
    image_close();


}

int main(void){
    printf("test, the test\n");
    CTEST_VERBOSE(1);

    test_image_open();
    test_image_close();
    test_bread();
    test_bwrite();

    CTEST_RESULTS();

    CTEST_EXIT();

}




#else
int main(void){
    printf("main\n");
    image_open("Foo.txt", 0);
    image_close();
}

#endif