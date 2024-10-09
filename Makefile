CXX = g++

SRC = src/spyware.cpp src/keylog.cpp src/screenshot.cpp

TARGET = spyware

CHILKAT_INCLUDE = /home/kali/Downloads/chilkat-x86_64-linux-gcc/include
CHILKAT_LIB = /home/kali/Downloads/chilkat-x86_64-linux-gcc/lib

CXXFLAGS = -I$(CHILKAT_INCLUDE)

LDFLAGS_DYNAMIC = -L$(CHILKAT_LIB) -lchilkat -lX11 -lpng -lXi
LDFLAGS_STATIC = -L$(CHILKAT_LIB) -lchilkat -Wl,-Bstatic -lX11 -lpng -lXi -Wl,-Bdynamic

BUILD_TYPE ?= dynamic

# build static failed so dont use it
all: $(TARGET)

$(TARGET): $(SRC)
	@if [ "$(BUILD_TYPE)" = "dynamic" ]; then \
		$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS) $(LDFLAGS_DYNAMIC); \
	else \
		$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS) $(LDFLAGS_STATIC); \
	fi

clean:
	rm -f $(TARGET)
