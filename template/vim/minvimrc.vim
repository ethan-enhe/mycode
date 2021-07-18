set nu
set ts=4
set sw=4
set mouse=a
set cindent
set hls
color evening

inoremap jj <esc>
inoremap " ""<left>
inoremap ( ()<left>
inoremap { {}<left>
inoremap [ []<left>

map <f9> :!g++ -O2 -Wall -fsanitize=address % -o %<<cr>
map <f8> :!time ./%<<cr>
