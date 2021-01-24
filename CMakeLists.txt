cmake_minimum_required(VERSION 3.10)

project(score_process VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)

add_compile_definitions(CPPHTTPLIB_OPENSSL_SUPPORT)

add_executable(score_process source/main.cc
							 source/scoreboard.cc
							 source/steam_api.cc
							 )

target_link_libraries(score_process OpenSSL::SSL
									OpenSSL::Crypto)

target_include_directories(score_process PUBLIC
                          "${PROJECT_SOURCE_DIR}/source"
						  "${PROJECT_SOURCE_DIR}/third_party"
						   ${OPENSSL_INCLUDE_DIR}
                          )