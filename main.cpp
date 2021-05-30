#include <iostream>
#include "SeqFile_FL/SeqFile_FL.h"
//#include "ISAM/ISAM.h"
int main () {

    SeqFile test("out");
    test.test();
    Botella b1("1","1","1","1","1","1","1","1","1");
    b1.toString2();
    test.add(b1);
    return 0;
}

