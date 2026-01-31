cmake_minimum_required (VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Magicover")

add_executable (Magicover "main.cpp" "ring.cpp" "ring.h" "enemy.cpp" "enemy.h" "boss.cpp" "boss.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Magicover PROPERTY CXX_STANDARD 20)
endif()

