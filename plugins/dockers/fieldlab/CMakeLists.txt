set(kritafieldlab_SOURCES
    FieldLabPlugin.cpp
    FieldLabDocker.cpp
    NodeDescriptor.cpp
    FieldGraph.cpp
    FieldGraphEvaluator.cpp
)

kis_add_library(kritafieldlab MODULE ${kritafieldlab_SOURCES})
target_link_libraries(kritafieldlab kritaui)
install(TARGETS kritafieldlab DESTINATION ${KRITA_PLUGIN_INSTALL_DIR})