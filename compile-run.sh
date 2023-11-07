#!/bin/bash

# Function to compile with emcc
compile() {
    emcc -std=c++17 -IEmpirical/include/ -Os --js-library Empirical/include/emp/web/library_emp.js \
    -s EXPORTED_FUNCTIONS="['_main', '_empCppCallback', '_empDoCppCallback']" \
    -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s NO_EXIT_RUNTIME=1 AEAnimate.cpp -o AEAnimate.js
}

# Function to start the HTTP server in the background
run_server() {
    # Kill any previously running server
    pkill -f "python3 -m http.server"

    # Start a new HTTP server in the background
    python3 -m http.server &
    SERVER_PID=$!
}

# Initial compile and server start
compile
run_server

# Loop to wait for the user to press 'r' to recompile and refresh server
while true; do
    read -p "Press 'r' and Enter to recompile and refresh the server: " input
    if [[ "$input" == "r" ]]; then
        # Kill the running server
        if [[ -n $SERVER_PID ]]; then
            kill $SERVER_PID
        fi
        # Recompile and restart server
        compile
        run_server
        echo "Recompilation and server refresh done."
    fi
done
