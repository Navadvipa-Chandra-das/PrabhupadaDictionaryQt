rem C:\PostgreSQL\15\bin\pg_dump.exe -d PrabhupadaDictionary -U "Navadvipa Chandra das" -W -b -c --column-inserts --inserts --disable-triggers --if-exists --no-unlogged-table-data -S "Navadvipa Chandra das" -f C:\C\PrabhupadaDictionary\SQL\PrabhupadaDictionary.sql
set now=%TIME:~0,-3%
set now=%now::=.%
set now=%now: =0%
set now=_%DATE:~-4%.%DATE:~3,2%.%DATE:~0,2%_%now%
"C:\PRG\7-Zip\7z.exe" -t7z -scsUTF-8 a PrabhupadaDictionary%now%.7z -ir@PrabhupadaDictionary.inc -xr@PrabhupadaDictionary.exc
copy PrabhupadaDictionary%now%.7z D:\Arhive\PrabhupadaDictionary.7z
copy PrabhupadaDictionary%now%.7z E:\Arhive\PrabhupadaDictionary.7z
