set ts=4 sw=4
set cin
set hls is
set mouse=a
set sm mat=2

map <f9> :!g++ -Wall -O2 -fsanitize=address,undefined % -o %<<cr>
map <f8> :!./%<<cr>

"optional
syntax on
let mapleader = ','
map <leader><f8> :!./%< < test.in<cr>
imap <c-n> <nop>
imap <c-p> <nop>
inoremap <c-p> <nop>
map <F1> <nop>
imap <F1> <nop>
