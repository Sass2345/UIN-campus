cmake_minimum_required(VERSION 3.25)
project(UINCampus
        VERSION 0.1.0
        DESCRIPTION "Système de gestion académique de l'UIN"
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(UIN_ACTIVER_SANITIZERS "Activer Address Sanitizer et UBSan" OFF)

# Options communes à toutes les cibles
add_library(uincampus_options INTERFACE)
target_compile_features(uincampus_options INTERFACE cxx_std_23)

if(MSVC)
    target_compile_options(uincampus_options INTERFACE /W4 /permissive-)
else()
    target_compile_options(uincampus_options INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

if(UIN_ACTIVER_SANITIZERS AND NOT MSVC)
    target_compile_options(uincampus_options INTERFACE
        -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(uincampus_options INTERFACE
        -fsanitize=address,undefined)
endif()

# Bibliothèque métier
add_library(uincampus_core 
src/version.cpp
src/regles.cpp
src/saisie.cpp )
target_include_directories(uincampus_core PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(uincampus_core PRIVATE UIN_VERSION="${PROJECT_VERSION}")
target_link_libraries(uincampus_core PRIVATE uincampus_options)

# Application
add_executable(uin-campus app/main.cpp)
target_link_libraries(uin-campus PRIVATE uincampus_core uincampus_options)
# --- Tests unitaires (Catch2) ---
enable_testing()
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(uin-campus-tests tests/test_main.cpp)
target_link_libraries(uin-campus-tests PRIVATE Catch2::Catch2WithMain)
target_compile_features(uin-campus-tests PRIVATE cxx_std_23)

include(CTest)
add_test(NAME UnitTests COMMAND uin-campus-tests)
# --- Options de compilation strictes ---
if(MSVC)
    target_compile_options(uin-campus PRIVATE /W4 /WX)
    target_compile_options(uin-campus-tests PRIVATE /W4 /WX)
else()
    target_compile_options(uin-campus PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(uin-campus-tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
# --- Options AddressSanitizer (ASan) ---
option(ENABLE_ASAN "Activer l'analyseur de mémoire AddressSanitizer" ON)

if(ENABLE_ASAN)
    target_compile_options(uin-campus PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(uin-campus PRIVATE -fsanitize=address)
    
    target_compile_options(uin-campus-tests PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(uin-campus-tests PRIVATE -fsanitize=address)
endif()
# --- Options UndefinedBehaviorSanitizer (UBSan) ---
option(ENABLE_UBSan "Activer l'analyseur UndefinedBehaviorSanitizer" ON)

if(ENABLE_UBSan)
    target_compile_options(uin-campus PRIVATE -fsanitize=undefined)
    target_link_options(uin-campus PRIVATE -fsanitize=undefined)
    
    target_compile_options(uin-campus-tests PRIVATE -fsanitize=undefined)
    target_link_options(uin-campus-tests PRIVATE -fsanitize=undefined)
endif()
# Support de clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

