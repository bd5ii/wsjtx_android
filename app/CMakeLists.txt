# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# FFTW
set(FFTW_OUT CMakeFiles/native-lib.dir/fftw)
set(ENABLE_LONG_DOUBLE ON CACHE BOOL "use double")
set(ENABLE_FLOAT ON CACHE BOOL "use float")
add_subdirectory(external/fftw-3.3.7 ${FFTW_OUT} EXCLUDE_FROM_ALL)

# Fortran setup
set(WSJT_LOC ../../wsjt/branches/wsjtx-1.8)

set(FORTRAN_MODULES
    ${WSJT_LOC}/lib/crc.f90
    ${WSJT_LOC}/lib/timer_module.f90
    ${WSJT_LOC}/lib/packjt.f90)

set(FORTRAN_FILES
    ${WSJT_LOC}/lib/indexx.f90
    ${WSJT_LOC}/lib/four2a.f90
    ${WSJT_LOC}/lib/db.f90
    ${WSJT_LOC}/lib/twkfreq.f90
    ${WSJT_LOC}/lib/deg2grid.f90
    ${WSJT_LOC}/lib/grid2deg.f90
    ${WSJT_LOC}/lib/geodist.f90
    ${WSJT_LOC}/lib/azdist.f90
    ${WSJT_LOC}/lib/fix_contest_msg.f90
    ${WSJT_LOC}/lib/to_contest_msg.f90
    ${WSJT_LOC}/lib/fmtmsg.f90
    ${WSJT_LOC}/lib/bpdecode144.f90
    ${WSJT_LOC}/lib/unpackmsg144.f90
    ${WSJT_LOC}/lib/determ.f90
    ${WSJT_LOC}/lib/shell.f90
    ${WSJT_LOC}/lib/pctile.f90
    ${WSJT_LOC}/lib/polyfit.f90
    ${WSJT_LOC}/lib/update_recent_calls.f90
    ${WSJT_LOC}/lib/fsk4hf/genft8.f90
    ${WSJT_LOC}/lib/fsk4hf/genft8refsig.f90
    ${WSJT_LOC}/lib/fsk4hf/encode174.f90
    ${WSJT_LOC}/lib/fsk4hf/osd174.f90
    ${WSJT_LOC}/lib/fsk4hf/baseline.f90
    ${WSJT_LOC}/lib/fsk4hf/twkfreq1.f90
    ${WSJT_LOC}/lib/fsk4hf/bpdecode174.f90
    ${WSJT_LOC}/lib/fsk4hf/extractmessage174.f90
    ${WSJT_LOC}/lib/fsk4hf/ft8_downsample.f90
    ${WSJT_LOC}/lib/fsk4hf/chkcrc12.f90
    ${WSJT_LOC}/lib/fsk4hf/chkcrc12a.f90
    ${WSJT_LOC}/lib/fsk4hf/sync8.f90
    ${WSJT_LOC}/lib/fsk4hf/sync8d.f90
    ${WSJT_LOC}/lib/fsk4hf/subtractft8.f90
    ${WSJT_LOC}/lib/fsk4hf/genft8.f90
    ${WSJT_LOC}/lib/fsk4hf/ft8b.f90)

set(FORTRAN_CC ${CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN}/bin/arm-linux-androideabi-gfortran)

foreach(FCOMPILE ${FORTRAN_MODULES})
    string(REPLACE ".f90" ".o" FLINK ${FCOMPILE})
    get_filename_component(FLINK ${FLINK} NAME)
    string(CONCAT FLINK "CMakeFiles/native-lib.dir/fortran/" ${FLINK})
    list(APPEND FORTRAN_MOD_LINK ${FLINK})
    add_custom_command(OUTPUT ${FLINK}
        COMMAND ${FORTRAN_CC} -c -o ${FLINK} ../../../../${FCOMPILE}
        DEPENDS ${FCOMPILE})
endforeach()

foreach(FCOMPILE ${FORTRAN_FILES})
    string(REPLACE ".f90" ".o" FLINK ${FCOMPILE})
    get_filename_component(FLINK ${FLINK} NAME)
    string(CONCAT FLINK "CMakeFiles/native-lib.dir/fortran/" ${FLINK})
    list(APPEND FORTRAN_LINK ${FLINK})
    add_custom_command(OUTPUT ${FLINK}
        COMMAND ${FORTRAN_CC} -c -o ${FLINK} ../../../../${FCOMPILE}
        DEPENDS ${FCOMPILE} ${FORTRAN_MOD_LINK})
endforeach()

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(${WSJT_LOC}/boost)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp
             ${WSJT_LOC}/lib/crc12.cpp
             ${FORTRAN_MOD_LINK}
             ${FORTRAN_LINK}
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       gfortran
                       fftw3l )