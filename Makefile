CXX = clang++
INCLUDES=-Iinclude
CXXFLAGS = -std=c++20

# Linking Commands

exec: include/connection.cc include/http_request.cc include/server.cc sample_server.cc
	$(CXX) $(CXXFLAGS) $^ 

.DEFAULT_GOAL := exec