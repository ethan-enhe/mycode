set ts=4
set sw=4
set cin
set hls is
set sm mat=2
set mouse=a
color desert

inoremap jj <esc>

map <f9> :!g++ -Wall -fsanitize=address,undefined % -o %<<cr>
map <f8> :!time ./%<<cr>
