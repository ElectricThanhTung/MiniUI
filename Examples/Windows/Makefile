
#####################################################################################################################
#                                                Project Information                                                #
#####################################################################################################################
PROJECT_NAME    :=  Windows_MiniUI
BUILD_DIR       :=  Build
OBJECT_DIR      :=  $(BUILD_DIR)/Obj
BIN_DIR         :=  $(BUILD_DIR)/Bin


#####################################################################################################################
#                                                Compiler Information                                               #
#####################################################################################################################
CC              :=  C:/MinGW/bin/g++.exe

MINIUI_TOOL     :=  ../../Tool/MiniUI/bin/Debug/MiniUI.exe

DEF             :=  -DMINIUI_BGR888

LIBS            :=  -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

FLAGS           :=  -m32                                                                                            \
                    -fdiagnostics-color=always                                                                      \
                    -g

LDFLAGS         :=  


#####################################################################################################################
#                                                Source Information                                                 #
#####################################################################################################################
MINIUI_CONFIG   :=  ../../MiniUI/miniui_config.xml

INCLUDES      	:=  ../../MiniUI/Types/Inc                                                                          \
                    ../../MiniUI/Fonts/Inc                                                                          \
                    ../../MiniUI/Controls/Inc                                                                       \
                    $(OBJECT_DIR)                                                                                   \
                    User/Inc

SOURCES       	:=  ../../MiniUI/Types/Src/miniui_bitmap.cpp                                                        \
                    ../../MiniUI/Types/Src/miniui_collections.cpp                                                   \
                    ../../MiniUI/Types/Src/miniui_color.cpp                                                         \
                    ../../MiniUI/Types/Src/miniui_common.cpp                                                        \
                    ../../MiniUI/Types/Src/miniui_font.cpp                                                          \
                    ../../MiniUI/Types/Src/miniui_graphics.cpp                                                      \
                    ../../MiniUI/Types/Src/miniui_line.cpp                                                          \
                    ../../MiniUI/Types/Src/miniui_alignment.cpp                                                     \
                    ../../MiniUI/Types/Src/miniui_orientation.cpp                                                   \
                    ../../MiniUI/Types/Src/miniui_pen.cpp                                                           \
                    ../../MiniUI/Types/Src/miniui_point.cpp                                                         \
                    ../../MiniUI/Types/Src/miniui_rect.cpp                                                          \
                    ../../MiniUI/Types/Src/miniui_size.cpp                                                          \
                    ../../MiniUI/Types/Src/miniui_thickness.cpp                                                     \
                    ../../MiniUI/Controls/Src/miniui_button.cpp                                                     \
                    ../../MiniUI/Controls/Src/miniui_control.cpp                                                    \
                    ../../MiniUI/Controls/Src/miniui_label.cpp                                                      \
                    ../../MiniUI/Controls/Src/miniui_progressbar.cpp                                                \
                    ../../MiniUI/Controls/Src/miniui_richtextbox.cpp                                                \
                    ../../MiniUI/Controls/Src/miniui_stackpanel.cpp                                                 \
                    ../../MiniUI/Controls/Src/miniui_textbox.cpp                                                    \
                    ../../MiniUI/Controls/Src/miniui_user_control.cpp                                               \
                    ../../MiniUI/Controls/Src/miniui_window.cpp                                                     \
                    ../../MiniUI/Fonts/Src/time_new_roman.cpp                                                       \
                    User/Src/main.cpp                                                                               \
                    User/Src/test.xml


#####################################################################################################################
#                                                Init Variables                                                     #
#####################################################################################################################
INCLUDES        :=  $(addprefix -I,$(INCLUDES))

OBJECTS         :=  $(notdir $(SOURCES))

OBJECTS         :=  $(OBJECTS:.c=.c.o)
OBJECTS         :=  $(OBJECTS:.cpp=.cpp.o)
OBJECTS         :=  $(OBJECTS:.xml=.xml.cpp.o)
OBJECTS         :=  $(addprefix $(OBJECT_DIR)/,$(OBJECTS))

BUILD_DIRS      :=  $(OBJECT_DIR) $(BIN_DIR)

XML_CPP         :=  $(filter %.xml.cpp,$(OBJECTS:.o=))

vpath %.c $(sort $(dir $(SOURCES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.xml $(sort $(dir $(SOURCES)))


#####################################################################################################################
#                                                Makefile Rules                                                     #
#####################################################################################################################
.SUFFIXES:

all: $(BIN_DIR)/$(PROJECT_NAME).exe

$(BUILD_DIRS):
	@mkdir -p $@
	@echo Created $@

$(OBJECT_DIR)/%.xml.cpp: %.xml Makefile | $(BUILD_DIRS)
	@rm -f $@
	@echo Generating $@ form $<
	@$(MINIUI_TOOL) $< -c $(MINIUI_CONFIG) -o $@

$(OBJECT_DIR)/%.c.o: %.c Makefile | $(BUILD_DIRS)
	@echo Compiling $<
	@$(CC) -c $(FLAGS) $(INCLUDES) $(DEF) $< -o $@

$(OBJECT_DIR)/%.cpp.o: $(OBJECT_DIR)/%.cpp Makefile | $(BUILD_DIRS)
	@echo Compiling $<
	@$(CC) -c $(FLAGS) $(INCLUDES) $(DEF) $< -o $@

.PRECIOUS $(OBJECT_DIR)/%.cpp.o: %.cpp Makefile | $(XML_CPP) $(BUILD_DIRS)
	@echo Compiling $<
	@$(CC) -c $(FLAGS) $(INCLUDES) $(DEF) $< -o $@

$(BIN_DIR)/$(PROJECT_NAME).exe: $(OBJECTS)
	@echo Linking object...
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	@echo Done

clean:
	@rm -fR $(BUILD_DIR)

rebuild:
	@make --no-print-directory clean
	@make --no-print-directory -j
