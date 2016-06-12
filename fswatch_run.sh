#fswatch -e ".*\.o"  -e ".*\.pb.cc" -e ".*\.pb.h" -e article_client -e article_server .
fswatch  -o ./tests/**/*.c ./tests/*.c  ./src/**/*.c | xargs -n1 -I{} ./autorun.sh
