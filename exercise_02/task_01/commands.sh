# Datei erzeugen mit zufälligen Bits
dd if=/dev/urandom of=test_file bs=1M count=1

# Links erzeugen
ln test_file test_hard_link
ln -s test_file test_soft_link


# Archiv erzeugen
tar -cf archiv_file_and_hard_link.tar test_file test_hard_link
tar -cf archiv_file_and_softlink.tar test_file test_soft_link


echo "Comparing files:"
ls -la test*

# No difference in size
echo "Comparing archives:"
ls -la archiv*
