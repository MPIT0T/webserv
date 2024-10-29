# TODOs in the Codebase

[main] ./.github/workflows/main.yml:1 name: TODO Scanner
[main] ./.github/workflows/main.yml:22       - name: Debug Branch and TODO Collection
[main] ./.github/workflows/main.yml:26           echo "# TODOs in the Codebase" > todo.md
[main] ./.github/workflows/main.yml:29           # Use grep to search for TODO comments, format each line, and append to todo.md
[main] ./.github/workflows/main.yml:30           grep -r -n "TODO" --exclude-dir={.git,node_modules,build} . | while IFS=: read -r filepath line todo; do
[main] ./.github/workflows/main.yml:46             git commit -m "Update TODO list [skip ci]"
[main] ./srcs/server/Server.cpp:68 			std::cerr << e.what() << std::endl; // TODO respond with the appropriate error
[main] ./srcs/server/Server.cpp:74 			std::cerr << e.what() << std::endl; // TODO respond with the appropriate error
[main] ./todo.md:1 # TODOs in the Codebase
