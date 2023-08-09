CXX = clang++
INCLUDES=-Iinclude
CXXFLAGS = -std=c++20
OPLEV = -O2

# Linking Commands

exec: include/http_request.cc include/server.cc include/handler.cc sample_server.cc 
	$(CXX) $(CXXFLAGS) $^ $(OPLEV)


.DEFAULT_GOAL := exec