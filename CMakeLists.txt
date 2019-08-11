cmake_minimum_required(VERSION 3.14)
project(ARPSpoofingTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ARPSpoofingTool main.cpp
        network/NetworkHeader.h
        network/arp/ARPSession.cpp
        network/arp/ARPSessionManager.cpp
        network/NetTools.cpp
        network/ARPSpoofingAgent.cpp)

SET(CMAKE_MODULE_PATH "//home/junghyun397/CLionProjects/bob_arp_send")

find_package(PCAP REQUIRED)

target_link_libraries(ARPSpoofingTool ${PCAP_LIBRARY})