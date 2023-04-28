dd if=/dev/urandom of=testfile bs=1M count=1 #Datei erzeugen mit zufälligen Bits
ln testfile testlink #Hardlink testlink auf testfile erzeugen
tar -cf archiv.tar teslink testfile #Das Archiv ist etwas größer als 1MB
ln -s testfile testlink2
tar -cf archiv2.tar teslink2 testfile #Das Archiv ist genauso groß wie das erste
