kis_add_test(
    FieldGraphTest.cpp
    TEST_NAME FieldGraphTest
    LINK_LIBRARIES Qt::Test kritafieldlabcore
)

option(
    FIELDLAB_ENABLE_FASTNOISE2_SPIKE
    "Build the isolated Field Lab FastNoise2 compatibility probe"
    OFF
)

if(FIELDLAB_ENABLE_FASTNOISE2_SPIKE)
    find_package(FastNoise2 1.1.1 CONFIG REQUIRED)

    kis_add_test(
        FastNoise2Probe.cpp
        TEST_NAME FastNoise2Probe
        LINK_LIBRARIES Qt::Test FastNoise2::FastNoise
    )
endif()
