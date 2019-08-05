cmake_minimum_required(VERSION 3.14)
project(bob_arp_send)

set(CMAKE_CXX_STANDARD 17)

add_executable(bob_arp_send main.cpp NetworkHeader.h SendARPAgent.cpp SendARPManager.cpp)

SET(CMAKE_MODULE_PATH "/home/junghyun397/CLionProjects/bob-pacp-test")

find_package(PCAP REQUIRED)

target_link_libraries(bob_arp_send ${PCAP_LIBRARY})