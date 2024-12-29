set(target ${PROJECT_NAME})
set(sources src/snake.c src/game.c src/main.c)

add_executable(${target} ${sources})

target_link_libraries(${target} PRIVATE ncge)

include(compiler/warnings-c)
compiler_warnings_install(${target})
