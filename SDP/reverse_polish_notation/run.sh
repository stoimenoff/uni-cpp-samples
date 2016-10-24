treesdir='trees'
if [ ! -d $treesdir ]; then
  mkdir $treesdir
fi

filename='expr'
base='tree'
iter="0"
end='.pdf'
while read expression; do
	iter=$((iter + 1))
	echo "$expression" > tmp
	./a.out < tmp > test.dot
	dot test.dot -Tpdf > $treesdir/$base$iter$end
done < $filename
rm tmp
rm test.dot