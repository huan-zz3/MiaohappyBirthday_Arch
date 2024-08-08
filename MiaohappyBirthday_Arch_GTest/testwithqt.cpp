#include "testwithqt.h"



TEST_F(TestwithQt, Cout){
    EXPECT_EQ(lh_->getNowLocation(), "Dongguan, Guangdong");
}



