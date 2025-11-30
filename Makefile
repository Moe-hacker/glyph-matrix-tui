all :
	cc *.c -o gmt -lm
format :
	clang-format -i *.c include/*.h
compass:all
	clear;termux-sensor -c;termux-sensor -d 100 -s "GeoMag Rotation Vector Sensor"|stdbuf -o0 jq -r '."GeoMag Rotation Vector Sensor".values[0:4] | @sh '|./gmt compass
level:all
	clear;termux-sensor -c;termux-sensor -d 100 -s "GeoMag Rotation Vector Sensor"|stdbuf -o0 jq -r '."GeoMag Rotation Vector Sensor".values[0:4] | @sh '|./gmt level