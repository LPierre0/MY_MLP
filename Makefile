# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -Wall -Wextra

# Nom de l'exécutable
TARGET = neuratNetwork

# Liste des fichiers source
SRCS = src/main.cpp src/display.cpp src/neuron.cpp src/utils.cpp src/network.cpp src/stb_image.cpp

# Liste des headers
HEADERS = src/display.h src/neuron.h src/utils.h src/network.h includes/stb_image.h

# Liste des fichiers objets générés
OBJS = $(SRCS:.cpp=.o)

# Règle de construction de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle de construction des fichiers objets
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(OBJS)
	$(CXX) test.cpp -o test
# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET) $(OBJS)

# Déclaration des cibles ne générant pas de fichiers
.PHONY: all clean
