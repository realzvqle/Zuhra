SRC = src/window/*.c src/renderer/*.c src/renderer/properties/*.c src/renderer/topbar/*.c src/networking/*.c
TARGET = zuhra.exe
LIBS = raylib/raylibdll.lib raylib/raylib.lib lua/liblua54.a winhttp.lib 


all: debug

debug:
	cl $(SRC) src/debug/main.c $(LIBS) naett/*.c tinycthread/*.c /Fe:$(TARGET)
	rm *.obj

release:
	cl /c $(SRC) src/release/main.c naett/*.c tinycthread/*.c
	link *.obj $(LIBS) /SUBSYSTEM:WINDOWS /OUT:$(TARGET)
	rm *.obj
