cmake_minimum_required(VERSION 2.8.2)

project(googletest NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    "/home/pieter/googletest"
  # https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "/home/pieter/GitHub/Control-Surface/build/googletest/googletest-src"
  BINARY_DIR        "/home/pieter/GitHub/Control-Surface/build/googletest/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
