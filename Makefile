OBJ_DIR := obj
SRC_DIR := src
BLD_DIR := build
INC_DIR := inc

OBJS := $(OBJ_DIR)/Ranking.o $(OBJ_DIR)/Team.o
JSONS := $(OBJ_DIR)/Ranking.o.json $(OBJ_DIR)/Team.o.json
TARGET := $(BLD_DIR)/FBS_Ranking.exe
CLANGD_JSON := compile_commands.json

CXX := clang++.exe
CXX_FLAGS := -I$(INC_DIR)

ifdef DEBUG
	CXX_FLAGS := -g
else
	CXX_FLAGS :=
endif

$(TARGET): $(OBJS) $(CLANGD_JSON)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $@

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -MJ $@.json -I$(INC_DIR) $(CXX_FLAGS) -c $< -o $@

$(CLANGD_JSON): $(OBJS)
	touch $@
	echo "[" >> $@
	cat $(JSONS) >> $@
	echo "]" >> $@


.PHONY: clean rebuild
clean:
	rm -f $(CLANGD_JSON)
	rm -rf $(OBJ_DIR)
	rm -rf $(BLD_DIR)
	mkdir $(OBJ_DIR)
	mkdir $(BLD_DIR)

rebuild: clean $(TARGET)