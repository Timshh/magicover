cmake_minimum_required (VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Magicover")

find_package(nlohmann_json QUIET)
if (NOT nlohmann_json_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
    )

    FetchContent_GetProperties(nlohmann_json)
    if (NOT nlohmann_json_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(nlohmann_json)
    endif()
endif()

add_executable (Magicover "core/main.cpp" "core/rings/ring.cpp" "core/rings/ring.h" "core/creatures/enemy.cpp" "core/creatures/enemy.h" "core/creatures/boss.cpp" "core/creatures/boss.h" "core/creatures/creature.h" "core/creatures/creature.cpp" "core/res_manager.cpp" "core/res_manager.h" "core/creatures/mage.h" "core/creatures/mage.cpp" "core/stats.h")
target_link_libraries(Magicover PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(
    TARGET Magicover POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:Magicover>/data
    COMMENT "Copying data to build directory"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Magicover PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Magicover PRIVATE 
    core
    core/creatures
    data
    core/rings
)