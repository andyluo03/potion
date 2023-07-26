CXX = g++
INCLUDES=-Iinclude
CXXFLAGS = -std=c++20
OPLEV = -o1

# Linking Commands

exec: include/connection.cc include/http_request.cc include/server.cc sample_server.cc
	$(CXX) $(CXXFLAGS) $^ $(OPLEV)

.DEFAULT_GOAL := exec