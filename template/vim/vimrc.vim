"{
"	"clangd.semanticHighlighting": true,
"	"coc.preferences.semanticTokensHighlights": false,
"	"diagnostic.errorSign": "✘",
"	"diagnostic.warningSign": "",
"	"diagnostic.infoSign": "",
"	"diagnostic.hintSign": "•",
"	  "suggest.completionItemKindLabels": {
"		"keyword": "\uf1de",
"		"variable": "\ue79b",
"		"value": "\uf89f",
"		"operator": "\u03a8",
"		"constructor": "\uf0ad",
"		"function": "\u0192",
"		"reference": "\ufa46",
"		"constant": "\uf8fe",
"		"method": "\uf09a",
"		"struct": "\ufb44",
"		"class": "\uf0e8",
"		"interface": "\uf417",
"		"text": "\ue612",
"		"enum": "\uf435",
"		"enumMember": "\uf02b",
"		"module": "\uf40d",
"		"color": "\ue22b",
"		"property": "\ue624",
"		"field": "\uf9be",
"		"unit": "\uf475",
"		"event": "\ufacd",
"		"file": "\uf723",
"		"folder": "\uf114",
"		"snippet": "\ue60b",
"		"typeParameter": "\uf728",
"		"default": "\uf29c"
"	},
"  "suggest.labelMaxLength": 50
"}
"
"~/.clang-format
" IndentWidth: 4
" TabWidth: 4
" UseTab: ForContinuationAndIndentation
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
" set relativenumber
"set cul
"set cuc
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
" set inccommand=nosplit
set diffopt+=vertical

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
nnoremap bp :bp<CR>
nnoremap bn :bn<CR>
nnoremap bo :enew<CR>
nnoremap bd :bd<CR>
nnoremap bl :ls<CR>
" nnoremap <F10> :NERDTreeToggle<CR>

let mapleader=" "
map <leader>/ :bel 10sp term://curl cht.sh/cpp/
map <leader>t :r ~/code/template/other/cf.cpp<cr>
map <F8> :call RunCode()<CR>
map <F9> :call CompileCode('-O2')<CR>
map <leader><F9> :call CompileCode('-O2 -Wall -fsanitize=address,undefined')<CR>
"map <F10> :NERDTreeToggle<CR>
map <F10> :MarkdownPreviewToggle<CR>
map<c-c> :Commentary<CR>
autocmd FileType cpp setlocal commentstring=//%s

let s:res=""
function! s:OnEvent(job_id, data, event) dict
	if a:event == 'exit'
		echo s:res."finished."
		let s:res=""
	else
		let s:res =s:res.join(a:data,"\n")
	endif
endfunction
let s:callbacks = {
\ 'on_stdout': function('s:OnEvent'),
\ 'on_stderr': function('s:OnEvent'),
\ 'on_exit': function('s:OnEvent')
\ }

func! CompileCode(copt)
	exec "w"
	" exec "make"
	echo "compiling... ".a:copt
	let cpl=jobstart((g:iswindows?"g++ -Wl,-stack=536870912":"clang++")."\ ".a:copt."\ ".expand("%")."\ -o\ ".expand("%<"),s:callbacks)
endfunction
func! RunCode()
	exec "w"
	let s:pre=has("nvim")?"bel 10sp term://":"!"
	if &filetype == 'cpp'
		let s:suf=g:iswindows?expand('%<').'.exe':'\\time -f \"\\n----\\n\%Mkb \%Us\" ./'.expand('%<')
	elseif &filetype == 'python'
		let s:suf='python3 '.expand('%')
	elseif &filetype == 'lua'
		let s:suf='lua '.expand('%')
	endif
	exec s:pre.s:suf
endfunction
if empty(glob(stdpath('config')."/autoload/"))
	exec "!curl -fLo ".stdpath('config')."/autoload/plug.vim --create-dirs https://ethan_enhe.coding.net/p/code/d/code/git/raw/master/template/vim/plug.vim"
endif

" PLUG
let g:mirror='https://github.com.cnpmjs.org/'
call plug#begin()
" Plug g:mirror.'scrooloose/nerdtree'
Plug g:mirror.'luochen1990/rainbow'
Plug g:mirror.'morhetz/gruvbox'
Plug g:mirror.'tomasr/molokai'
Plug g:mirror.'rakr/vim-one'
Plug g:mirror.'joshdick/onedark.vim'
Plug g:mirror.'chriskempson/base16-vim'
Plug g:mirror.'ryanoasis/vim-devicons'
Plug g:mirror.'tpope/vim-surround'
Plug g:mirror.'tpope/vim-commentary'
Plug g:mirror.'vim-airline/vim-airline'
Plug g:mirror.'vim-airline/vim-airline-themes'
Plug g:mirror.'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}
" Plug g:mirror.'Yggdroot/indentLine'

if g:usecoc
	Plug g:mirror.'ethan-enhe/vim-snippets/'
	Plug g:mirror.'neoclide/coc.nvim', {'branch': 'release'}
	Plug g:mirror.'jackguo380/vim-lsp-cxx-highlight'
else

	" Plug g:mirror.'jayli/vim-easycomplete'
	" Plug g:mirror.'skywind3000/vim-auto-popmenu'
	" Plug g:mirror.'w0rp/ale'
endif
call plug#end()

" COLOR
let g:indentLine_char_list = ['|', '¦', '┆', '┊']
let g:rainbow_active = 1
let base16colorspace=256
let g:rehash256 = 1
let g:molokai_original = 1
" let g:one_allow_italics = 1 " I love italic for comments
" let g:gruvbox_italic=1
let g:gruvbox_sign_column='bg0'
" let g:gruvbox_number_column='bg1'
" let g:gruvbox_color_column='bg0'
let g:gruvbox_vert_split='bg0'
" let g:gruvbox_invert_signs=1

" let g:gruvbox_improved_strings=1
" let g:gruvbox_improved_warnings=1

" autocmd vimenter * hi Normal guibg=NONE ctermbg=NONE
colorscheme gruvbox

syntax enable


set list lcs=tab:\|\ 
set termguicolors
set background=dark
set noshowmode

" let g:airline_theme='onedark'
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 1	  "tabline中当前buffer两端的分隔字符
let g:airline#extensions#whitespace#enabled = 0
let g:airline#extensions#whitespace#symbol = '!'
let g:airline#extensions#tabline#buffer_nr_show=1

" let g:airline_section_z = ' %{strftime("%-I:%M %p")}'


" autocmd BufNewFile *.cpp 0 r ~/code/template/other/cf.cpp

if g:usecoc
	"{{{ coc.nvim
	let g:coc_global_extensions = ['coc-clangd','coc-markdownlint', 'coc-pairs','coc-json','coc-snippets','coc-lists']
	autocmd FileType * let b:coc_pairs_disabled = ['<']
	" Use autocmd to force lightline update.
	"autocmd User CocStatusChange,CocDiagnosticChange call lightline#update()

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
	"inoremap <silent><expr> <cr> pumvisible() ? coc#_select_confirm()
								  \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"
	inoremap <silent><expr> <cr> pumvisible() ? "\<C-y>" : "\<CR>"

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
	nmap <leader>rf <Plug>(coc-refactor)


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
	command! -nargs=? Fold :call	 CocAction('fold', <f-args>)

	" Add `:OR` command for organize imports of the current buffer.
	command! -nargs=0 OR   :call	 CocAction('runCommand', 'editor.action.organizeImport')
	" Add (Neo)Vim's native statusline support.
	" NOTE: Please see `:h coc-status` for integrations with external plugins that
	" provide custom statusline: lightline.vim, vim-airline.
	set statusline^=%{coc#status()}%{get(b:,'coc_current_function','')}

	" Mappings for CoCList
	" Show all diagnostics.
	nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
	" Manage extensions.
	nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
	" Show commands.
	nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
	" Find symbol of current document.
	nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
	nnoremap <silent><nowait> <space>g  :<C-u>CocList grep<cr>
	" Search workspace symbols.
	nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
	" Do default action for next item.
	nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
	" Do default action for previous item.
	nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
	" Resume latest coc list.
	nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>
	"}}}
	"{{{ coc-snippets
	" Use <C-l> for trigger snippet expand.
	imap <C-l> <Plug>(coc-snippets-expand)
	" Use <C-j> for select text for visual placeholder of snippet.
	vmap <C-j> <Plug>(coc-snippets-select)
	" Use <C-j> for jump to next placeholder, it's default of coc.nvim
	let g:coc_snippet_next = '<c-j>'
	" Use <C-k> for jump to previous placeholder, it's default of coc.nvim
	let g:coc_snippet_prev = '<c-k>'
	" Use <C-j> for both expand and jump (make expand higher priority.)
	imap <C-j> <Plug>(coc-snippets-expand-jump)
	" Use <leader>x for convert visual selected code to snippet
	xmap <leader>x  <Plug>(coc-convert-snippet)
	"}}}
else
	" ale-setting {{{
	"let g:ale_set_highlights = 0
	""自定义error和warning图标
	"let g:ale_sign_error = '>>'
	"let g:ale_sign_warning = '--'
	""显示Linter名称,出错或警告等相关信息
	"let g:ale_echo_msg_error_str = 'E'
	"let g:ale_echo_msg_warning_str = 'W'
	"let g:ale_echo_msg_format = '[%linter%] %s [%severity%]'
	""打开文件时不进行检查
	""let g:ale_lint_on_enter = 0

	""普通模式下，sp前往上一个错误或警告，sn前往下一个错误或警告
	"nmap sp <Plug>(ale_previous_wrap)
	"nmap sn <Plug>(ale_next_wrap)
	""<Leader>s触发/关闭语法检查
	"nmap <Leader>s :ALEToggle<CR>
	""<Leader>d查看错误或警告的详细信息
	"nmap <Leader>d :ALEDetail<CR>
	""使用clang对c和c++进行语法检查，对python使用pylint进行语法检查
	"let g:ale_linters = {
	"\   'c++': ['clang'],
	"\   'c': ['clang'],
	"\}
	"let g:lightline.component_expand = {
	"	  \  'linter_checking': 'lightline#ale#checking',
	"	  \  'linter_infos': 'lightline#ale#infos',
	"	  \  'linter_warnings': 'lightline#ale#warnings',
	"	  \  'linter_errors': 'lightline#ale#errors',
	"	  \  'linter_ok': 'lightline#ale#ok',
	"	  \ }
	"let g:lightline.component_type = {
	"	  \	 'linter_checking': 'right',
	"	  \	 'linter_infos': 'right',
	"	  \	 'linter_warnings': 'warning',
	"	  \	 'linter_errors': 'error',
	"	  \	 'linter_ok': 'right',
	"	  \ }
	"let g:lightline.active = { 'right': [[ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ]] }

	"let g:lightline.active = {
	"		\ 'right': [ [ 'linter_checking', 'linter_errors', 'linter_warnings', 'linter_infos', 'linter_ok' ],
	"		\			[ 'lineinfo' ],
	"		\			[ 'percent' ],
	"		\			[ 'fileformat', 'fileencoding', 'filetype'] ] }
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
