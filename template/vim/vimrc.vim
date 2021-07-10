"set runtimepath^=~/.vim runtimepath+=~/.vim/after
"let &packpath = &runtimepath
"source ~/.vimrc


" Basic

if has("gui_running")
	set guifont=Consolas:h14
	set backspace=indent,eol,start
	set guioptions=
endif

set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
set number
set ruler
set showcmd
set mouse=a
set laststatus=2

" Indent+Cursor
set smartindent
if &filetype == 'cpp'
	set cindent
endif
set ts=4
set sw=4
" 代码折叠
set foldenable
" 折叠方法
" manual    手工折叠
" indent    使用缩进表示折叠
" expr      使用表达式定义折叠
" syntax    使用语法定义折叠
" diff      对没有更改的文本进行折叠
" marker    使用标记进行折叠, 默认标记是 {{{ 和 }}}
set foldmethod=marker
set foldlevel=99

" AUTO
set autochdir
set autowrite
set autoread
set hlsearch
set incsearch
" MAP
"inoremap ' ''<LEFT>
"inoremap " ""<LEFT>
"inoremap ( ()<LEFT>
"inoremap [ []<LEFT>
"inoremap { {}<LEFT>
inoremap jj <ESC>
tnoremap jj <c-\><c-n>
tnoremap <ESC> <c-\><c-n>
map <c-a> :!cat '%' \| clip.exe<cr>
map <c-c> "+y


let mapleader=" "
set makeprg=g++\ -Wall\ -std=c++11\ -O2\ %<.cpp\ -o\ %<
map <leader>/ :bel 10sp term://curl cht.sh/cpp/
map <leader>, :cp<CR>
map <leader>. :cn<CR>
map <F8> :call RunCode()<CR>
map <F9> :call CompileCode()<CR>
map <F10> :NERDTreeToggle<CR>

func! CompileCode()
    exec "w"
	"exec "ccl"
	exec "make"
	"exec "redraw!"
	"exec "cw 8"
endfunction
func! RunCode()
    exec "w"
    if &filetype == 'cpp'
		"exec "ccl"
		if has('nvim')
			exec "bel 10sp term://./%<"
		else
			exec "!./%<"
		endif
    elseif &filetype == 'python'
		if has('nvim')
			exec "bel 10sp term://python3 %"
		else
			exec "!python3 %"
		endif
    endif
endfunction


" PLUG
call plug#begin('~/.vim/plugged')
Plug 'https://hub.fastgit.org/itchyny/lightline.vim'
Plug 'https://hub.fastgit.org/scrooloose/nerdtree'
Plug 'https://hub.fastgit.org/morhetz/gruvbox'
Plug 'https://hub.fastgit.org/tomasr/molokai'
Plug 'https://hub.fastgit.org/jiangmiao/auto-pairs'
call plug#end()



" COLOR
syntax enable
let g:gruvbox_invert_indent_guides = '1'
color gruvbox
set background=dark
set noshowmode
let g:lightline = {
      \ 'colorscheme': 'gruvbox',
	  \ 'component': {
      \   'readonly': '%{&readonly?"":""}',
      \ },
      \ 'separator':    { 'left': '', 'right': '' },
      \ 'subseparator': { 'left': '', 'right': '' },
      \ }
highlight Normal guibg=NONE ctermbg=None
