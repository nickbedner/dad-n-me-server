cmake_minimum_required(VERSION 3.12)

set(ignoreMe "${CMAKE_CXX_COMPILER}")
set(CMAKE_C_STANDARD 11)

project(DadNMeServer LANGUAGES C VERSION 0.1.0)

file(GLOB_RECURSE dad_n_me_SRC
        include/*.h
        src/*.c)

#add_executable(DadNMeServer ${dad_n_me_SRC})
# Start with library then standalone server
add_library(DadNMeServer STATIC ${dad_n_me_SRC})

if (WIN32)
# Add OpenMP
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:AVX2")
else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1 -mavx2")
        if (APPLE)
                set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include" CACHE INTERNAL "OpenMP flags for Xcode toolchain.")
                set(OpenMP_C_LIB_NAMES "omp" CACHE INTERNAL "OpenMP lib name for Xcode toolchain.")
                set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.dylib" CACHE INTERNAL "OpenMP lib name for Xcode toolchain.")
        endif()

        find_package(OpenMP REQUIRED)
        #if (OPENMP_FOUND)
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        #endif()
endif()

# If building with game no reason to include mimalloc twice
if (NOT TARGET mimalloc-static)
        set(MI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
        set(MI_BUILD_OBJECT OFF CACHE BOOL "" FORCE)
        set(MI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
        add_subdirectory(lib/mimalloc buildmimalloc)
        string(REPLACE " -w" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif() 

if(APPLE)
        target_link_libraries(DadNMeServer OpenMP::OpenMP_C)
endif()

if(UNIX AND NOT APPLE)
        target_link_libraries(DadNMeServer m)
endif()

set(DAD_N_ME_BUILD_LIBRARIES mimalloc-static)

target_link_libraries(${DAD_N_ME_BUILD_LIBRARIES})
#target_link_libraries(DadNMeServer m)

set(includeList
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/cstorage/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/cthreads/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uber-math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/mimalloc/include
        ${OpenMP_CXX_LIBRARIES})

target_include_directories(DadNMeServer PUBLIC ${includeList})