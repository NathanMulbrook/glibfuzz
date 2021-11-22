rm *.profraw
rm default.profdata
./fuzz_cos corpus/ -runs=1 -detect_leaks=0
rm coverage_txt.txt
rm coverage_HTML.html
/usr/bin/llvm-profdata merge -sparse *.profraw -o default.profdata
/usr/bin/llvm-cov show ./fuzz_cos  -format=html  -use-color -instr-profile=default.profdata > coverage_HTML.html
/usr/bin/llvm-cov report ./fuzz_cos -instr-profile=default.profdata > coverage_txt.txt

