qt6_add_library(backend STATIC)
qt_add_qml_module(backend
    URI Backend
    VERSION 1.0
    RESOURCE_PREFIX "/"
    SOURCES
        backend.cpp backend.h
        berry.cpp berry.h
        berrylistmodel.h berrylistmodel.cpp
        poffin.h poffin.cpp
        poffinstatsmodel.h poffinstatsmodel.cpp
        serializable.h
    RESOURCES
        data/backend.json
)

target_link_libraries(backend PRIVATE
    Qt6::Gui
)

add_subdirectory(Test)
