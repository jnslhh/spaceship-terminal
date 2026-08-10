ifeq ($(origin CXX),default)
CXX = g++
endif

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

CPPFLAGS ?=
CXXSTD ?= -std=c++17
CXXFLAGS ?= -O2 -Wall -Wextra
LDFLAGS ?=

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
LDLIBS ?= -lncurses
else
LDLIBS ?= -lncursesw
endif

TARGET = spaceship
SOURCES = main.cpp

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXSTD) $(CXXFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

install: $(TARGET)
	install -d "$(DESTDIR)$(BINDIR)"
	install -m 755 $(TARGET) "$(DESTDIR)$(BINDIR)/$(TARGET)"

uninstall:
	rm -f "$(DESTDIR)$(BINDIR)/$(TARGET)"

clean:
	rm -f $(TARGET)
