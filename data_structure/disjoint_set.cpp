#include "common_header.h"

#include "disjoint_set.h"


#ifdef WANT_TESTS
TEST(DisjointSet_ArrayTest, SanityTest) {
    DisjointSet_Array disjoint_set{5};

    EXPECT_EQ(2u, disjoint_set.Find(2));

    disjoint_set.Union(disjoint_set.Find(1), disjoint_set.Find(0));
    disjoint_set.Union(disjoint_set.Find(1), disjoint_set.Find(3));

    EXPECT_EQ(disjoint_set.Find(1), disjoint_set.Find(3));
    EXPECT_EQ(disjoint_set.Find(0), disjoint_set.Find(3));
    EXPECT_NE(disjoint_set.Find(1), disjoint_set.Find(2));
    EXPECT_NE(disjoint_set.Find(4), disjoint_set.Find(2));
}
#endif
