template=~/cp/template.cpp
makefile=~/cp/.makefile

for x in {a..n}
do
	file_name=$(printf ${x}.cpp)	
	cp "$template" "$file_name"
done

cp "$makefile" ./makefile
touch in out

