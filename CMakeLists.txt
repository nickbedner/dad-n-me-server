cmake_minimum_required(VERSION 3.12)
project(DadNMeServer LANGUAGES C VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX "d")

file(GLOB_RECURSE dad_n_me_SRC
        include/*.h
        src/*.c)
        
# Check if building for static library or standalone server
option(DAD_N_ME_SERVER_STATIC_LIBRARY "Build static library" OFF)
if(DAD_N_ME_SERVER_STATIC_LIBRARY)
        add_library(DadNMeServer STATIC ${dad_n_me_SRC})
else()
        add_executable(DadNMeServer ${dad_n_me_SRC})
endif()

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DCHECK_MEMORY_LEAKS=1)
        message("Debug build.")
else()
        add_definitions(-DCUSTOM_ALLOCATOR=1)
endif()

set_target_properties(DadNMeServer
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_definitions(-DSIMD_SSE2=1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")

# /MDd
if (WIN32)
        #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -fopenmp -qopenmp-link=static")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -fopenmp")
endif ()

# -fsanitize=address
if(APPLE)
        add_subdirectory(lib/MoltenVK buildmoltenvk)
        find_package(OpenMP)
        if (OPENMP_FOUND)
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        endif()
endif()

if(UNIX AND NOT APPLE)
        # for Linux, BSD, Solaris, Minix
        find_package(OpenMP)
        if (OPENMP_FOUND)
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        endif()
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

set(DAD_N_ME_SERVER_BUILD_LIBRARIES
        DadNMeServer
        mimalloc-static)

if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES "Clang")
        STRING(REPLACE " " "\ " PATH_NO_SPACE "$ENV{ProgramFiles}")
        set(DAD_N_ME_SERVER_BUILD_LIBRARIES ${DAD_N_ME_SERVER_BUILD_LIBRARIES} "${PATH_NO_SPACE}/LLVM/lib/libomp.lib" "${PATH_NO_SPACE}/LLVM/lib/libiomp5md.lib")
endif ()

target_link_libraries(${DAD_N_ME_SERVER_BUILD_LIBRARIES})
#target_link_libraries(DadNMeServer m)

set(includeList
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/cstorage/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/cthreads/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uber-math/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/mimalloc/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/cxml-parser/include
        ${OpenMP_CXX_LIBRARIES})

target_include_directories(DadNMeServer PUBLIC ${includeList})