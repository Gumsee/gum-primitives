#
# Source
#
set(SRC
  "Primitives/Bone.cpp"
  "Primitives/Curve.cpp"
  "Primitives/SkeletalAnimation.cpp"
  "Primitives/UniqueID.cpp"
  "Primitives/MeshGenerators/Arc.cpp"
  "Primitives/MeshGenerators/Cube.cpp"
  "Primitives/MeshGenerators/Plane.cpp"
  "Primitives/MeshGenerators/Capsule.cpp"
  "Primitives/MeshGenerators/Cylinder.cpp"
  "Primitives/MeshGenerators/Sphere.cpp"
  "Primitives/Mesh.cpp"
)
add_library(${PROJECT_NAME} STATIC ${SRC})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/)

 
if(GUMESSENTIALS_FOUND)
    include_directories(${GUMESSENTIALS_INCLUDE_DIRS})
else()
    message(FATAL_ERROR Library for GUMESSENTIALS cannot not found)
endif() 
if(GUMSYSTEM_FOUND)
    include_directories(${GUMSYSTEM_INCLUDE_DIRS})
else()
    message(FATAL_ERROR Library for GUMSYSTEM cannot not found)
endif() 
if(GUMMATHS_FOUND)
    include_directories(${GUMMATHS_INCLUDE_DIRS})
else()
    message(FATAL_ERROR Library for GUMMATHS cannot not found)
endif()

if(GUM_PRIMITIVES_MESH_UP_Z)
  add_definitions(-DGUM_PRIMITIVES_MESH_UP_Z)
endif()

install(
    FILES gum-primitives.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
) 

file(GLOB HEADERS Primitives/*.h)
install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Primitives/
)

install(FILES ${COMBINED_LIB}
    DESTINATION ${CMAKE_INSTALL_LIBDIR})


configure_package_config_file("Config.cmake.in"
    "${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_LIBDIR
)


### Install Config and ConfigVersion files
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

export(PACKAGE ${PROJECT_NAME})

