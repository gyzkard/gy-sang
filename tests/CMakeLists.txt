file(GLOB test-sources CONFIGURE_DEPENDS *.cpp)

add_custom_target(gysang-test)

enable_testing()

foreach (source IN LISTS test-sources)
  get_filename_component(test "${source}" NAME_WE)

  add_executable(gysang-test-${test} ${source} ${ARGN})
  add_test(gysang-test-${test} gysang-test-${test})

  set_property(TARGET gysang-test-${test} PROPERTY CXX_STANDARD ${GYSANG_CPP_STD})
  target_compile_features(gysang-test-${test} INTERFACE cxx_std_11)
  target_link_libraries(gysang-test-${test} PRIVATE gysang)
  target_link_libraries(gysang-test-${test} PRIVATE gympl)
  add_dependencies(gysang-test gysang-test-${test})
endforeach()
