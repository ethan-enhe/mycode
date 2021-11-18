".clang-format
"BasedOnStyle: google
"IndentWidth: 4
"
"call mkdir(stdpath('config'),'p')
"exe 'edit' stdpath('config').'/init.vim'
"
"set runtimepath^=~/.vim runtimepath+=~/.vim/after
"let &packpath = &runtimepath
"source ~/.vimrc


" Basic

set guifont=Consolas:h14
set backspace=indent,eol,start
set guioptions=
set winaltkeys=no
if has('nvim')
	try
		call rpcnotify(1, 'Gui', 'Option', 'Tabline', 0)
		call rpcnotify(1, 'Gui', 'Option', 'Popupmenu', 0)
	catch
	endtry
endif


let g:iswindows = 0
if(has("win32") || has("win64") || has("win95") || has("win16"))
	let g:iswindows = 1
endif
let g:usecoc = 1

set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
set number
"set relativenumber
set ruler
set showcmd
set mouse=a
set laststatus=2
set scrolloff=2
set clipboard+=unnamedplus

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
" manual	手工折叠
" indent	使用缩进表示折叠
" expr	  使用表达式定义折叠
" syntax	使用语法定义折叠
" diff	  对没有更改的文本进行折叠
" marker	使用标记进行折叠, 默认标记是 {{{ 和 }}}
set foldmethod=marker
"set foldlevel=99

" AUTO
set autochdir
set autowrite
set autoread
set hlsearch
set incsearch

" MAP
if !g:usecoc
	inoremap ' ''<LEFT>
	inoremap " ""<LEFT>
	inoremap ( ()<LEFT>
	inoremap [ []<LEFT>
	inoremap { {}<LEFT>
endif
inoremap jj <ESC>
tnoremap jj <c-\><c-n>
tnoremap <ESC> <c-\><c-n>
map <c-a> :!cat '%' \| clip.exe<cr>
map <c-c> "+y


let mapleader=" "
let &makeprg=(g:iswindows?"g++":"clang++\ -fsanitize=address")."\ -O2\ -std=c++11\ %\ -o\ %<"
map <leader>/ :bel 10sp term://curl cht.sh/cpp/
map <leader>t :0 r ~/code/template/other/cf.cpp<cr>
map <F8> :call RunCode()<CR>
map <F9> :call CompileCode()<CR>
"map <F10> :NERDTreeToggle<CR>
func! CompileCode()
	exec "w"
	exec "make"
endfunction
func! RunCode()
	exec "w"
	let s:pre=has("nvim")?"bel 10sp term://":"!"
	if &filetype == 'cpp'
		let s:suf=g:iswindows?"%<.exe":"time ./%<"
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
"Plug 'https://hub.fastgit.org/scrooloose/nerdtree'
Plug 'https://hub.fastgit.org/itchyny/lightline.vim'
Plug 'https://hub.fastgit.org/luochen1990/rainbow'
Plug 'https://hub.fastgit.org/overcache/NeoSolarized'
Plug 'https://hub.fastgit.org/morhetz/gruvbox'
Plug 'https://hub.fastgit.org/crusoexia/vim-monokai'

if g:usecoc
	Plug 'https://hub.fastgit.org/neoclide/coc.nvim', {'branch': 'release'}
else
	Plug 'https://hub.fastgit.org/skywind3000/vim-auto-popmenu'
	Plug 'https://hub.fastgit.org/w0rp/ale'
	Plug 'https://hub.fastgit.org/maximbaz/lightline-ale'
endif
"Plug 'https://hub.fastgit.org/octol/vim-cpp-enhanced-highlight'
"Plug 'https://hub.fastgit.org/SirVer/ultisnips'
call plug#end()



" COLOR
let g:rainbow_active = 1
color gruvbox
syntax enable

set termguicolors
set background=dark
set noshowmode
let g:lightline = {
	  \ 'colorscheme': 'gruvbox',
	  "\ 'colorscheme': 'solarized',
	  \ 'active': {
	  \   'left': [ [ 'mode', 'paste' ],
	  \             [ 'cocstatus', 'readonly', 'filename', 'modified' ] ]
	  \ },
	  \ 'component_function': {
	  \   'cocstatus': 'coc#status'
	  \ },
	  \ }
"highlight Normal guibg=NONE ctermbg=None
"autocmd vimenter * NERDTree
"autocmd BufNewFile *.cpp 0 r ~/code/template/other/cf.cpp


if g:usecoc
	"{{{ coc.nvim
	let g:coc_global_extensions = ['coc-clangd', 'coc-pairs','coc-snippets']
	autocmd FileType * let b:coc_pairs_disabled = ['<']
	" Use autocmd to force lightline update.
	autocmd User CocStatusChange,CocDiagnosticChange call lightline#update()

	" TextEdit might fail if hidden is not set.
	set hidden

	" Some servers have issues with backup files, see #649.
	set nobackup
	set nowritebackup

	" Give more space for displaying messages.
	set cmdheight=2

	" Having longer updatetime (default is 4000 ms = 4 s) leads to noticeable
	" delays and poor user experience.
	set updatetime=300

	" Don't pass messages to |ins-completion-menu|.
	set shortmess+=c

	" Always show the signcolumn, otherwise it would shift the text each time
	" diagnostics appear/become resolved.
	if has("nvim-0.5.0") || has("patch-8.1.1564")
	  " Recently vim can merge signcolumn and number column into one
	  set signcolumn=number
	else
	  set signcolumn=yes
	endif

	" Use tab for trigger completion with characters ahead and navigate.
	" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
	" other plugin before putting this into your config.
	let g:coc_snippet_next = '<tab>'
	inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
	inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

	function! s:check_back_space() abort
	  let col = col('.') - 1
	  return !col || getline('.')[col - 1]  =~# '\s'
	endfunction

	" Use <c-space> to trigger completion.
	if has('nvim')
	  inoremap <silent><expr> <c-space> coc#refresh()
	else
	  inoremap <silent><expr> <c-@> coc#refresh()
	endif

	" Make <CR> auto-select the first completion item and notify coc.nvim to
	" format on enter, <cr> could be remapped by other vim plugin
	inoremap <silent><expr> <cr> pumvisible() ? coc#_select_confirm()
								  \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

	" Use `[g` and `]g` to navigate diagnostics
	" Use `:CocDiagnostics` to get all diagnostics of current buffer in location list.
	nmap <silent> [g <Plug>(coc-diagnostic-prev)
	nmap <silent> ]g <Plug>(coc-diagnostic-next)

	" GoTo code navigation.
	nmap <silent> gd <Plug>(coc-definition)
	nmap <silent> gy <Plug>(coc-type-definition)
	nmap <silent> gi <Plug>(coc-implementation)
	nmap <silent> gr <Plug>(coc-references)

	" Use K to show documentation in preview window.
	nnoremap <silent> K :call <SID>show_documentation()<CR>

	function! s:show_documentation()
	  if (index(['vim','help'], &filetype) >= 0)
		execute 'h '.expand('<cword>')
	  elseif (coc#rpc#ready())
		call CocActionAsync('doHover')
	  else
		execute '!' . &keywordprg . " " . expand('<cword>')
	  endif
	endfunction

	" Highlight the symbol and its references when holding the cursor.
	autocmd CursorHold * silent call CocActionAsync('highlight')

	" Symbol renaming.
	nmap <leader>rn <Plug>(coc-rename)

	" Formatting selected code.
	xmap <leader>f  <Plug>(coc-format-selected)
	nmap <leader>f  <Plug>(coc-format-selected)


	augroup mygroup
	  autocmd!
	  " Setup formatexpr specified filetype(s).
	  autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
	  " Update signature help on jump placeholder.
	  autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
	augroup end

	" Applying codeAction to the selected region.
	" Example: `<leader>aap` for current paragraph
	xmap <leader>a  <Plug>(coc-codeaction-selected)
	nmap <leader>a  <Plug>(coc-codeaction-selected)

	" Remap keys for applying codeAction to the current buffer.
	nmap <leader>ac  <Plug>(coc-codeaction)
	" Apply AutoFix to problem on the current line.
	nmap <leader>qf  <Plug>(coc-fix-current)

	" Map function and class text objects
	" NOTE: Requires 'textDocument.documentSymbol' support from the language server.
	xmap if <Plug>(coc-funcobj-i)
	omap if <Plug>(coc-funcobj-i)
	xmap af <Plug>(coc-funcobj-a)
	omap af <Plug>(coc-funcobj-a)
	xmap ic <Plug>(coc-classobj-i)
	omap ic <Plug>(coc-classobj-i)
	xmap ac <Plug>(coc-classobj-a)
	omap ac <Plug>(coc-classobj-a)

	" Remap <C-f> and <C-b> for scroll float windows/popups.
	if has('nvim-0.4.0') || has('patch-8.2.0750')
	  nnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
	  nnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
	  inoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<Right>"
	  inoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<Left>"
	  vnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
	  vnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
	endif

	" Use CTRL-S for selections ranges.
	" Requires 'textDocument/selectionRange' support of language server.
	nmap <silent> <C-s> <Plug>(coc-range-select)
	xmap <silent> <C-s> <Plug>(coc-range-select)

	" Add `:Format` command to format current buffer.
	command! -nargs=0 Format :call CocAction('format')

	" Add `:Fold` command to fold current buffer.
	command! -nargs=? Fold :call     CocAction('fold', <f-args>)

	" Add `:OR` command for organize imports of the current buffer.
	command! -nargs=0 OR   :call     CocAction('runCommand', 'editor.action.organizeImport')

	" Mappings for CoCList
	" Show all diagnostics.
	nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
	" Manage extensions.
	nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
	" Show commands.
	nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
	" Find symbol of current document.
	nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
	" Search workspace symbols.
	nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
	" Do default action for next item.
	nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
	" Do default action for previous item.
	nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
	" Resume latest coc list.
	nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>
	"}}}
else
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
		  \	 'linter_checking': 'right',
		  \	 'linter_infos': 'right',
		  \	 'linter_warnings': 'warning',
		  \	 'linter_errors': 'error',
		  \	 'linter_ok': 'right',
		  \ }
	let g:lightline.active = { 'right': [[ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ]] }

	let g:lightline.active = {
			\ 'right': [ [ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ],
			\			[ 'lineinfo' ],
			\			[ 'percent' ],
			\			[ 'fileformat', 'fileencoding', 'filetype'] ] }
	" }}}
	" {{{vap
	" enable this plugin for filetypes, '*' for all files.
	let g:apc_enable_ft = {'*':1}

	" source for dictionary, current or other loaded buffers, see ':help cpt'
	set cpt=.,k,w,b,i,d

	" don't select the first item.
	set completeopt=menu,menuone,noselect

	" suppress annoy messages.
	set shortmess+=c
	" }}}
endif
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
