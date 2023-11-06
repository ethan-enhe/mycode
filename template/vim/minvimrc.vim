set ts=4 sw=4
set cin
set hls is
set mouse=a
set sm mat=2
color desert

inoremap jj <esc>

map <f9> :!g++ -Wall -O2 -fsanitize=address,undefined % -o %<<cr>
map <f8> :!\time -f "M: \%M T: \%U" ./%<<cr>
