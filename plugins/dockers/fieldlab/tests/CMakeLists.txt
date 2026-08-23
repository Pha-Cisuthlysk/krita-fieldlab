kis_add_test(
    FieldGraphTest.cpp
    ../FieldGraph.cpp
    ../FieldGraphEvaluator.cpp
    ../FieldGraphValidator.cpp
    ../NodeDescriptor.cpp
    TEST_NAME FieldGraphTest
    LINK_LIBRARIES Qt::Core Qt::Test
)

target_include_directories(FieldGraphTest PRIVATE ..)
