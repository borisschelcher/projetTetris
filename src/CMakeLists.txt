cmake_minimum_required(VERSION 3.7)

project(project_tetric LANGUAGES C)


find_package(SDL2 REQUIRED)


function(ADD_PRG)

	set(options OPTIONAL)
	set(oneValueArgs TARGET )
	set(multiValueArgs SOURCES)
	cmake_parse_arguments(ADD_PRG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

	add_executable(${ADD_PRG_TARGET} "")
	target_sources(${ADD_PRG_TARGET} PUBLIC ${ADD_PRG_SOURCES})
	if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
		target_include_directories(${ADD_PRG_TARGET} PUBLIC /usr/include/SDL2)
		target_link_libraries(${ADD_PRG_TARGET} PUBLIC SDL2 SDL2main)
	else()
		target_link_libraries(${ADD_PRG_TARGET} PUBLIC SDL2::SDL2 SDL2::SDL2main)
	endif()
	target_compile_definitions(${ADD_PRG_TARGET} PUBLIC _USE_MATH_DEFINES)

endfunction()


ADD_PRG(TARGET project_tetric SOURCES tetric.c  game_manager.c game_manager.h window_manager.h window_manager.c board.c board.h shapes.h piece.c piece.h player.h player.c printer.c printer.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MenuV1.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/grilleTetris.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/grille2P.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreBleu.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
	
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreGris.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreJaune.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreOrange.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreRouge.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreVert.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/spriteCarreViolet.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tetris_ascii.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

