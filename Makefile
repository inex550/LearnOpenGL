GXX=g++
CARGS=-Wall

OPEN_GL_LIBS=-lopengl32 -lglu32 -lglfw3 -lgdi32
ASSIMP_LIB=-lassimp

INCS=-IInclude
LIBS=-LLibs

SRC_COMMON=src/*.c src/common.cpp src/core/*.cpp

OUT_BIN=build/prog.exe

hello_triangle:
	${GXX} ${CARGS} ${SRC_COMMON} src/hello_triangle.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

shaders_blinking:
	${GXX} ${CARGS} ${SRC_COMMON} src/shaders_blinking.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

shaders_rainbow:
	${GXX} ${CARGS} ${SRC_COMMON} src/shaders_rainbow.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

textures:
	${GXX} ${CARGS} ${SRC_COMMON} src/textures.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

transforms:
	${GXX} ${CARGS} ${SRC_COMMON} src/transforms.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

light:
	${GXX} ${CARGS} ${SRC_COMMON} src/light.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

light_casters:
	${GXX} ${CARGS} ${SRC_COMMON} src/light_casters.cpp ${OPEN_GL_LIBS} ${ASSIMP_LIB} ${INCS} ${LIBS} -o ${OUT_BIN}

models:
	${GXX} ${CARGS} ${SRC_COMMON} src/models.cpp ${OPEN_GL_LIBS} ${ASSIMP_LIB} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_1:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_1.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_2:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_2.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_3:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_3.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_6_8_2:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_6_8_2.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_7_8_2:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_7_8_2.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}
	
ex_7_8_4:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_7_8_4.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}
	
ex_8_19_2:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_8_19_2.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

clean:
	rm -rf build/*