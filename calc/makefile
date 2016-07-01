CCXX=g++
CXXFLAGS=-Iinclude -Isrc/hdr -Isrc
LDFLAGS=

CXXSRCS:=$(wildcard src/*.cpp)
CXXOBJS:=$(patsubst src/%.cpp, obj/%.o, $(CXXSRCS))
CXXHDRS:=$(wildcard src/*.hpp src/hdr/*.hpp include/*.hpp)

fractalier-gen : $(CXXOBJS)
	$(CCXX) -o $@ -g $(CXXFLAGS) $(CXXOBJS) $(LDFLAGS)

$(CXXOBJS) : $(CXXSRCS) $(CXXHDRS)
	$(CCXX) -o $@ $^ $(CXXFLAGS) $(CXXHDRS)
