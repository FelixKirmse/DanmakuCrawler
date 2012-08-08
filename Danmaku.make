# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/Danmaku
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/Danmaku
  DEFINES   += -DDEBUG
  INCLUDES  += -Isrc/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -g -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lboost_filesystem -lboost_serialization -Llib
  LIBS      += -lBlackDragonEngine
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += lib/libBlackDragonEngine.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/Danmaku
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/Danmaku
  DEFINES   += -DNDEBUG
  INCLUDES  += -Isrc/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -O2 -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s -lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lboost_filesystem -lboost_serialization -Llib
  LIBS      += -lBlackDragonEngine
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += lib/libBlackDragonEngine.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/DanmakuGame.o \
	$(OBJDIR)/TileCode.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/EncounterRate.o \
	$(OBJDIR)/Spell.o \
	$(OBJDIR)/Spells.o \
	$(OBJDIR)/GameStateManager.o \
	$(OBJDIR)/Party.o \
	$(OBJDIR)/MainMenu.o \
	$(OBJDIR)/TargetSelectMenu.o \
	$(OBJDIR)/BattleMenu.o \
	$(OBJDIR)/IngameMenu.o \
	$(OBJDIR)/SpellSelectMenu.o \
	$(OBJDIR)/MapGen.o \
	$(OBJDIR)/MapCell.o \
	$(OBJDIR)/TitleScreen.o \
	$(OBJDIR)/Ingame.o \
	$(OBJDIR)/Menu.o \
	$(OBJDIR)/Battle.o \
	$(OBJDIR)/CharGraphics.o \
	$(OBJDIR)/Character.o \
	$(OBJDIR)/OverworldPlayer.o \
	$(OBJDIR)/Stats.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Danmaku
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning Danmaku
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/DanmakuGame.o: src/Danmaku/DanmakuGame.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TileCode.o: src/Danmaku/TileCode.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: src/Danmaku/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/EncounterRate.o: src/Danmaku/Helpers/EncounterRate.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Spell.o: src/Danmaku/Spells/Spell.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Spells.o: src/Danmaku/Spells/Spells.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/GameStateManager.o: src/Danmaku/Managers/GameStateManager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Party.o: src/Danmaku/Managers/Party.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MainMenu.o: src/Danmaku/Menus/MainMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TargetSelectMenu.o: src/Danmaku/Menus/TargetSelectMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/BattleMenu.o: src/Danmaku/Menus/BattleMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/IngameMenu.o: src/Danmaku/Menus/IngameMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SpellSelectMenu.o: src/Danmaku/Menus/SpellSelectMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MapGen.o: src/Danmaku/TileMap/MapGen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MapCell.o: src/Danmaku/TileMap/MapCell.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TitleScreen.o: src/Danmaku/GameStates/TitleScreen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Ingame.o: src/Danmaku/GameStates/Ingame.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Menu.o: src/Danmaku/GameStates/Menu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Battle.o: src/Danmaku/GameStates/Battle.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CharGraphics.o: src/Danmaku/Entities/CharGraphics.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Character.o: src/Danmaku/Entities/Character.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/OverworldPlayer.o: src/Danmaku/Entities/OverworldPlayer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Stats.o: src/Danmaku/Entities/Stats.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
