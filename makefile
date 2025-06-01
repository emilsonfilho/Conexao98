# Executáveis
TARGET_APP = app
TARGET_SERVER = server

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# Fontes
MAIN_APP = main.cpp
MAIN_SERVER = $(SRC_DIR)/server/main_server.cpp

# Todos os .cpp (exceto mains)
SRCS_COMMON = $(filter-out $(MAIN_APP) $(MAIN_SERVER), $(shell find $(SRC_DIR) -name '*.cpp'))

# Objetos
OBJS_COMMON = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS_COMMON))
OBJ_APP = $(OBJ_DIR)/main.o
OBJ_SERVER = $(OBJ_DIR)/server/main_server.o

# Compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -I$(INC_DIR) -std=c++17

# Alvo principal
all: $(TARGET_APP) $(TARGET_SERVER)

# Regras para os executáveis
$(TARGET_APP): $(OBJ_APP) $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_SERVER): $(OBJ_SERVER) $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar qualquer .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# main.cpp especial fora do src/
$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET_APP) $(TARGET_SERVER)

# Atalhos pra rodar
run-app: $(TARGET_APP)
	./$(TARGET_APP)

run-server: $(TARGET_SERVER)
	./$(TARGET_SERVER)