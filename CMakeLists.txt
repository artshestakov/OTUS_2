cmake_minimum_required(VERSION 3.12)

project(homework_2 VERSION ${VER_REVISION})

add_executable(homework_2
    main.cpp
)

target_include_directories(homework_2
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS homework_2 RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT art.shestakov@icloud.com)
include(CPack)
