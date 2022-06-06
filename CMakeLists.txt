# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(T1)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(GlobusM2 GlobusM2.cc ${sources} ${headers} include/SensitiveDetector.hh src/SensitiveDetector.cc)
target_link_libraries(GlobusM2 ${Geant4_LIBRARIES})

set(EXAMPLET1_SCRIPTS
  run.mac
  vis.mac
  init_vis.mac
  3121_Unix.csv
  )
set( CMAKE_BUILD_TYPE Debug )

foreach(_script ${EXAMPLET1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/GDML/ ${PROJECT_BINARY_DIR}/GDML/ )

add_custom_target(T1 DEPENDS GlobusM2)

install(TARGETS GlobusM2 DESTINATION bin)


