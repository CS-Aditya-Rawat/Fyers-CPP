cmake_minimum_required(VERSION 3.10.2)

project(fyers-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(${wxWidgets_USE_FILE})

set(source_dir "${PROJECT_SOURCE_DIR}/src")
set(include_dir "${PROJECT_SOURCE_DIR}/include")

file (GLOB source_files "${source_dir}/*.cpp")
file (GLOB include_files "${include_dir}/*.h")
include_directories(${include_dir})

add_executable(fyers-cpp ${source_files})

target_link_libraries(fyers-cpp
    PRIVATE
    ${wxWidgets_LIBRARIES}
    nlohmann_json::nlohmann_json
    cpprestsdk::cpprest
    jwt-cpp::jwt-cpp
    /usr/local/lib/libTgBot.a
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
)
