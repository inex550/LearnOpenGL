.PHONY: all clean rebuild

GXX=g++
CARGS=-Wall -Werror -Wextra

OPEN_GL_LIBS=-lopengl32 -lglu32 -lglfw3 -lgdi32

INCS=-IInclude
LIBS=-LLibs

SRC_COMMON=src/*.c src/common.cpp

OUT_BIN=build/prog.exe

hello_triangle:
	${GXX} ${CARGS} ${SRC_COMMON} src/hello_triangle.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

shaders:
	${GXX} ${CARGS} ${SRC_COMMON} src/shaders.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_1:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_1.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_2:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_2.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

ex_5_8_3:
	${GXX} ${CARGS} ${SRC_COMMON} src/exercices/ex_5_8_3.cpp ${OPEN_GL_LIBS} ${INCS} ${LIBS} -o ${OUT_BIN}

clean:
	rm -rf build/*

rebuild: clean all