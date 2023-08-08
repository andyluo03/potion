CXX = clang++
INCLUDES=-Iinclude
CXXFLAGS = -std=c++20

# Linking Commands

exec: include/http_request.cc include/server.cc include/handler.cc sample_server.cc
	$(CXX) $(CXXFLAGS) $^ 

.DEFAULT_GOAL := exec