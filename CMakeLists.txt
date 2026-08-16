cmake_minimum_required (VERSION 3.11)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(PROJECT_NAME "Magicover")
project (${PROJECT_NAME})

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

set (SOURCES "core/main.cpp" 
"core/gamemode/core.cpp" 
"core/rings/ring.cpp" 
"core/creatures/enemy.cpp" 
"core/creatures/boss.cpp" 
"core/creatures/creature.cpp" 
"core/creatures/creatureObserver.cpp" 
"core/resources/res_Manager.cpp" 
"core/creatures/mage.cpp" 
"core/render/consoleUI.cpp"
"core/render/uiController.cpp"
"core/gamemode/mapgenerator.cpp"
"core/gamemode/coreObserver.cpp"
"core/gamemode/battle.cpp"
"core/gamemode/map.cpp"
"core/gamemode/room.cpp"
"core/gamemode/inventory.cpp")
set (HEADERS "core/rings/ring.h" 
"core/creatures/enemy.h" 
"core/creatures/creature.h" 
"core/creatures/creatureObserver.h" 
"core/resources/res_Manager.h" 
"core/creatures/mage.h" 
"core/resources/creature_stats.h" 
"core/resources/ring_stats.h" 
"core/gamemode/core.h"
"core/render/consoleUI.h"
"core/render/uiController.h"
"core/render/uiData.h"
"core/gamemode/mapgenerator.h"
"core/gamemode/coreObserver.h"
"core/gamemode/battle.h"
"core/gamemode/map.h"
"core/gamemode/room.h"
"core/gamemode/mapData.h"
"core/gamemode/inventory.h")

add_executable (${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
    COMMENT "Copying data to build directory"
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    core
    core/creatures
    core/rings
    core/resources
    core/gamemode
    core/render
    data
)