set ts=4
set sw=4
set mouse=a
set cin
set hls
set is
set nu

inoremap jj <esc>
inoremap " ""<left>
inoremap ( ()<left>
inoremap { {}<left>
inoremap [ []<left>

map <f9> :!g++ -Wall -fsanitize=address,undefined % -o %<<cr>
map <f8> :!\time -f "\n\%M \%U" ./%<<cr>
