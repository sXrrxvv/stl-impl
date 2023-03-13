#ifndef IMPLEMENTING_STL_TEST_OBJECTS_H
#define IMPLEMENTING_STL_TEST_OBJECTS_H
struct noDefCtor{
    noDefCtor() = delete;
};

struct noDefCtorWithMember : noDefCtor{
    int first;
};
#endif //IMPLEMENTING_STL_TEST_OBJECTS_H
