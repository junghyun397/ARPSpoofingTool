cmake_minimum_required(VERSION 3.14)
project(bob_arp_send)

set(CMAKE_CXX_STANDARD 17)

add_executable(ARPSpoofingTool main.cpp network/NetworkHeader.h network/arp/SendARPAgent.cpp network/arp/SendARPManager.cpp network/NetTools.cpp network/ARPAttackAgent.cpp)

SET(CMAKE_MODULE_PATH "//home/junghyun397/CLionProjects/ARPSpoofingTool")

find_package(PCAP REQUIRED)

target_link_libraries(ARPSpoofingTool ${PCAP_LIBRARY})