# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-src")
  file(MAKE_DIRECTORY "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-build"
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix"
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/tmp"
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/src/libfmt-populate-stamp"
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/src"
  "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/src/libfmt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/src/libfmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/antho/flycast/devilutionX/dreamcast-build-fresh/_deps/libfmt-subbuild/libfmt-populate-prefix/src/libfmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
