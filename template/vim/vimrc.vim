"set runtimepath^=~/.vim runtimepath+=~/.vim/after
"let &packpath = &runtimepath
"source ~/.vimrc


" Basic

if has("gui_running")
	set guifont=Consolas:h14
	set backspace=indent,eol,start
	set guioptions=
endif

let g:iswindows = 0
if(has("win32") || has("win64") || has("win95") || has("win16"))
	let g:iswindows = 1
endif

set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
set number
set ruler
set showcmd
set mouse=a
set laststatus=2
set scrolloff=2

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
"set foldlevel=99

" AUTO
set autochdir
set autowrite
set autoread
set hlsearch
set incsearch

" MAP
inoremap ' ''<LEFT>
inoremap " ""<LEFT>
inoremap ( ()<LEFT>
inoremap [ []<LEFT>
inoremap { {}<LEFT>
inoremap jj <ESC>
tnoremap jj <c-\><c-n>
tnoremap <ESC> <c-\><c-n>
map <c-a> :!cat '%' \| clip.exe<cr>
map <c-c> "+y


let mapleader=" "
set makeprg=clang++\ -O2\ -fsanitize=address\ -std=c++11\ %\ -o\ %<
map <leader>/ :bel 10sp term://curl cht.sh/cpp/
map <F8> :call RunCode()<CR>
map <F9> :call CompileCode()<CR>
map <F10> :NERDTreeToggle<CR>

func! CompileCode()
    exec "w"
	exec "make"
endfunction
func! RunCode()
    exec "w"
	let s:pre=has("nvim")?"bel 10sp term://":"!"
    if &filetype == 'cpp'
		let s:suf=g:iswindows?"\%<.exe":"\./%<"
    elseif &filetype == 'python'
		let s:suf="python3 %"
    endif
	exec s:pre.s:suf
endfunction
if empty(glob(stdpath('config')."/autoload/"))
	exec "!curl -fLo ".stdpath('config')."/autoload/plug.vim --create-dirs https://ethan_enhe.coding.net/p/code/d/code/git/raw/master/template/vim/plug.vim"
endif

" PLUG
call plug#begin()
Plug 'https://hub.fastgit.org/itchyny/lightline.vim'
Plug 'https://hub.fastgit.org/scrooloose/nerdtree'
Plug 'https://hub.fastgit.org/morhetz/gruvbox'
Plug 'https://hub.fastgit.org/luochen1990/rainbow'
Plug 'https://hub.fastgit.org/overcache/NeoSolarized'
Plug 'https://hub.fastgit.org/w0rp/ale'
Plug 'https://hub.fastgit.org/maximbaz/lightline-ale'
"Plug 'https://hub.fastgit.org/octol/vim-cpp-enhanced-highlight'
"Plug 'https://hub.fastgit.org/SirVer/ultisnips'
call plug#end()



" COLOR
let base16colorspace=256
let g:rainbow_active = 1
color gruvbox
syntax enable

set termguicolors
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
"highlight Normal guibg=NONE ctermbg=None
autocmd BufNewFile *.cpp 0 r ~/code/template/other/cf.cpp


" ale-setting {{{
let g:ale_set_highlights = 0
"自定义error和warning图标
let g:ale_sign_error = '>>'
let g:ale_sign_warning = '--'
"显示Linter名称,出错或警告等相关信息
let g:ale_echo_msg_error_str = 'E'
let g:ale_echo_msg_warning_str = 'W'
let g:ale_echo_msg_format = '[%linter%] %s [%severity%]'
"打开文件时不进行检查
"let g:ale_lint_on_enter = 0

"普通模式下，sp前往上一个错误或警告，sn前往下一个错误或警告
nmap sp <Plug>(ale_previous_wrap)
nmap sn <Plug>(ale_next_wrap)
"<Leader>s触发/关闭语法检查
nmap <Leader>s :ALEToggle<CR>
"<Leader>d查看错误或警告的详细信息
nmap <Leader>d :ALEDetail<CR>
"使用clang对c和c++进行语法检查，对python使用pylint进行语法检查
let g:ale_linters = {
\   'c++': ['clang'],
\   'c': ['clang'],
\}
let g:lightline.component_expand = {
      \  'linter_checking': 'lightline#ale#checking',
      \  'linter_infos': 'lightline#ale#infos',
      \  'linter_warnings': 'lightline#ale#warnings',
      \  'linter_errors': 'lightline#ale#errors',
      \  'linter_ok': 'lightline#ale#ok',
      \ }
let g:lightline.component_type = {
      \     'linter_checking': 'right',
      \     'linter_infos': 'right',
      \     'linter_warnings': 'warning',
      \     'linter_errors': 'error',
      \     'linter_ok': 'right',
      \ }
let g:lightline.active = { 'right': [[ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ]] }

let g:lightline.active = {
		\ 'right': [ [ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ],
		\            [ 'lineinfo' ],
	    \            [ 'percent' ],
	    \            [ 'fileformat', 'fileencoding', 'filetype'] ] }
" }}}
" {{{ snippets

" Trigger configuration. You need to change this to something other than <tab> if you use one of the following:
" - https://github.com/Valloric/YouCompleteMe
" - https://github.com/nvim-lua/completion-nvim
let g:UltiSnipsExpandTrigger="<tab>"
let g:UltiSnipsJumpForwardTrigger="<tab>"
let g:UltiSnipsJumpBackwardTrigger="<S-tab>"

" If you want :UltiSnipsEdit to split your window.
let g:UltiSnipsEditSplit="vertical"
" }}}
" {{{ vim-cpp-enhanced-highlight
let g:cpp_class_scope_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_concepts_highlight = 1
let g:cpp_experimental_simple_template_highlight = 1
let g:cpp_posix_standard = 1
" }}}
