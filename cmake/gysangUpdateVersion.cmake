#message(STATUS "updateVersion: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "updateVersion: CMAKE_CURRENT_LIST_FILE:  ${CMAKE_CURRENT_LIST_FILE}")
#message(STATUS "updateVersion: CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
#message(STATUS "updateVersion: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "updateVersion: GIT_EXECUTABLE: ${GIT_EXECUTABLE}")

include(gysangDoFindGit)
if (NOT Git_FOUND)
  message(FATAL_ERROR "Cannot update version.hpp without git and Git_FOUND is false")
  return()
endif()


# Grab the version numbers:
include(${CMAKE_CURRENT_SOURCE_DIR}/Version.cmake)
set(GYSANG_VERSION_VERSION ${GYSANG_VERSION_MAJOR}.${GYSANG_VERSION_MINOR}.${GYSANG_VERSION_PATCHLEVEL})

# Try to build a new version.hpp
configure_file(version.hpp.in include/gysang/version.hpp @ONLY)
file(STRINGS ${CMAKE_CURRENT_BINARY_DIR}/include/gysang/version.hpp GYSANG_OLD_VERSION_HPP)
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/include/gysang/version.hpp GYSANG_NEW_VERSION_HPP)

#message(STATUS "updateVersion: GYSANG_OLD_VERSION_HPP: ${GYSANG_OLD_VERSION_HPP}")
#message(STATUS "updateVersion: GYSANG_NEW_VERSION_HPP: ${GYSANG_NEW_VERSION_HPP}")

# If the new version.hpp is materially different from the one in the source
# directory, update it, commit, and tag.
if(NOT GYSANG_NEW_VERSION_HPP STREQUAL GYSANG_OLD_VERSION_HPP)
  # Check that docs/release_notes.md and Version.cmake are the only changed file:
  execute_process(
    COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" status --porcelain -uno
    OUTPUT_VARIABLE GYSANG_GIT_STATUS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if ("${GYSANG_GIT_STATUS}" STREQUAL "")
    # or that there's non change at all because there's no commit yet
  else()
    string(REPLACE "\n" ";"  GYSANG_GIT_STATUS ${GYSANG_GIT_STATUS})
    if (NOT "x${GYSANG_GIT_STATUS}" STREQUAL "x M Version.cmake; M docs/release_notes.md")
      #message(FATAL_ERROR "Cannot update version.hpp: the source directory has a dirty status")
	  message(WARNING "Cannot update version.hpp: the source directory has a dirty status. If you're not testing something consider solving this.")
	  return()
    endif()
  endif()
  
  file(
    COPY ${CMAKE_CURRENT_BINARY_DIR}/include/gysang/version.hpp
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/gysang
  )
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" add -u
  #)
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" commit -m "${GYSANG_VERSION_VERSION}"
  #)
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" tag -f -a "${GYSANG_VERSION_VERSION}" -m "${GYSANG_VERSION_VERSION}"
  #)
  find_program(CONAN_EXECUTABLE NAMES conan conan.exe)
  if (NOT "x${CONAN_EXECUTABLE}" STREQUAL "xCONAN_EXECUTABLE-NOTFOUND")
    message(STATUS "Exporting conanfile for new version")
    #execute_process(
    #  COMMAND ${CONAN_EXECUTABLE} create . gysang/${GYSANG_VERSION_VERSION}@gyzkard/stable
    #  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    #)
  endif()
  message(STATUS "Version updated to ${GYSANG_VERSION_VERSION}. Don't forget to:")
  message(STATUS "  git push origin <feature-branch>")
  message(STATUS "and (after that is merged to master) then:")
  message(STATUS "  conan remote add gysang https://api.bintray.com/conan/gysang/gysang")
  message(STATUS "  conan create ${CMAKE_CURRENT_SOURCE_DIR} gysang/${GYSANG_VERSION_VERSION}@gyzkard/stable")
  message(STATUS "  conan upload --all gysang/${GYSANG_VERSION_VERSION}@gyzkard/stable -r=gysang")
endif()
