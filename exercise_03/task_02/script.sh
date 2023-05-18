URL=https://de.wikipedia.org/wiki/Fußball-Bundesliga_2022/23

#wget $URL -O page.html

line_where_table_begins=$(cat page.html | head --lines=500 | egrep -n "<table class.*wikitable sortable.*" | cut -d ":" -f 1)
line_where_table_ends=$(cat page.html | head --lines=1200 | egrep -n "</th></tr></tbody></table>" | cut -d ":" -f 1)
number_of_lines=$(($line_where_table_ends - $line_where_table_begins + 1 ))

table=$(cat page.html | head --lines=$line_where_table_ends | tail --line=$number_of_lines | tee "01-table.txt" )

formatted_table=$(echo "$table" | sed 's/th/td/g')



lines_with_place_and_teams=$(echo "$formatted_table"  | grep -Ezo '<td style="text-align:center;">.*\d\d?\.\n+</td>''|''<a href="/wiki/[^"]+" title="[^"]+">[^<]+</a>' | tee "02-lines_with_place_and_teams.txt" ) 

unformatted_place_and_teams=$(echo "$lines_with_place_and_teams" | sed  's/&#x2002;//g' | sed -E 's/<[^>]*>//g' | tee "03-unformatted_place_and_teams.txt" )


echo "$unformatted_place_and_teams"

