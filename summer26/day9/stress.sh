P=b
make ${P} b_slow.cpp gen || exit 1
for ((i = 1; ; i++)) do
	./gen $i > in
	./${P} < in > out
	./${P}2 < in > out2
	if (! cmp -s out out2) then
		echo "-->ent"
		cat in
		echo "-->s1"
		cat out
		echo "-->s2"
		cat out2
		break;
	fi
	echo $i
done
