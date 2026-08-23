set(kritafieldlabcore_SOURCES
    NodeDescriptor.cpp
    FieldGraph.cpp
    FieldGraphEvaluator.cpp
    FieldGraphSampler.cpp
    FieldGraphValidator.cpp
)

kis_add_library(kritafieldlabcore STATIC ${kritafieldlabcore_SOURCES})
target_link_libraries(kritafieldlabcore PUBLIC Qt::Core)
target_include_directories(
    kritafieldlabcore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

set(kritafieldlab_SOURCES
    FieldLabPlugin.cpp
    FieldLabDocker.cpp
)

kis_add_library(kritafieldlab MODULE ${kritafieldlab_SOURCES})
target_link_libraries(kritafieldlab kritaui kritafieldlabcore)
install(TARGETS kritafieldlab DESTINATION ${KRITA_PLUGIN_INSTALL_DIR})

add_subdirectory(tests)
