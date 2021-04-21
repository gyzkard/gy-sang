cmake_minimum_required(VERSION 3.8.0)


get_directory_property(is_subproject PARENT_DIRECTORY)
if(NOT is_subproject)
    set(is_standalone YES)
else()
    set(is_standalone NO)
endif()


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compilation data-base
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


#set( CMAKE_MESSAGE_LOG_LEVEL "DEBUG" )
#message(DEBUG "main CMakeLists.txt: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(DEBUG "main CMakeLists.txt: CMAKE_CURRENT_LIST_FILE:  ${CMAKE_CURRENT_LIST_FILE}")
#message(DEBUG "main CMakeLists.txt: CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
#message(DEBUG "main CMakeLists.txt: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(DEBUG "main CMakeLists.txt: CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
#message(DEBUG "main CMakeLists.txt: PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")


include(gysangUpdateVersion)


project(gysang
  HOMEPAGE_URL "https://github.com/gyzkard/gy-sang"
  VERSION ${GYSANG_VERSION_VERSION}
  LANGUAGES CXX)


set(GYSANG_CPP_STD ${CMAKE_CXX_STANDARD} CACHE STRING "C++ Standard. Supported values are 11, 14, 17, 20, 23")
#message(DEBUG "main CMakeLists.txt: GYSANG_CPP_STD: ${GYSANG_CPP_STD}")
#message(DEBUG "main CMakeLists.txt: CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
#message(DEBUG "main CMakeLists.txt: CMAKE_CXX_STANDARD_REQUIRED: ${CMAKE_CXX_STANDARD_REQUIRED}")


include(gysangDoFindGympl)


include(CMakeDependentOption)
include(GNUInstallDirs)
if (is_standalone)
	include(CTest)

	cmake_dependent_option(GYSANG_BUILD_DOCS "Build gysang Docs" ON
	  "CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
	cmake_dependent_option(GYSANG_BUILD_TESTS "Build gysang Tests" ON
	  "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
# target_compile_features(gysang INTERFACE cxx_std_20)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)

install(EXPORT ${PROJECT_NAME}-targets 
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
  NAMESPACE ${PROJECT_NAME}::)
install(
  FILES
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include
    FILES_MATCHING PATTERN *.hpp)


if(GYSANG_BUILD_DOCS)
  include(gysangDoFindDoxygen)
  add_subdirectory(docs)
endif()

if (GYSANG_BUILD_TESTS)
  add_subdirectory(tests)
endif()
