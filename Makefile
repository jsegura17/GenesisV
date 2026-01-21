# Makefile para GenesisV - Proyecto OpenGL básico
# Compatible con MinGW/MSYS2

# Compilador
CXX = g++
WINDRES = windres

# Directorios
SRCDIR = .
OBJDIR = .
BINDIR = .

# Archivos fuente
SOURCES = GenesisV.cpp GenesisCORE.cpp
OBJECTS = $(SOURCES:.cpp=.o)
RESOURCE = GenesisV_private.res

# Nombre del ejecutable
TARGET = GenesisV.exe

# Flags del compilador
CXXFLAGS = -Wall -O2 -DWIN32 -DNDEBUG -D_WINDOWS -D_MBCS
LDFLAGS = -mwindows
LIBS = -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32

# Regla por defecto
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS) $(RESOURCE)
	$(CXX) $(OBJECTS) $(RESOURCE) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar recurso
$(RESOURCE): GenesisV_private.rc GenesisV.ico
	$(WINDRES) -i GenesisV_private.rc -o $(RESOURCE) -O coff

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(RESOURCE) $(TARGET)

# Recompilar todo
rebuild: clean all

.PHONY: all clean rebuild
