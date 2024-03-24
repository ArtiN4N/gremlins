
for i in {1..10}
do
    magick assets/maps/FULLmap$i.jpg assets/maps/FULLmap$i.png
    rm assets/maps/FULLmap$i.jpg
done