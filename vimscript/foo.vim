let g:tot=''
function! s:OnEvent(job_id, data, event) dict
  if a:event == 'stdout'
	let str = join(a:data)."\n"
  elseif a:event == 'stderr'
	let str = join(a:data)."\n"
  else
	let str = "\nexited"
	echo g:tot
	let g:tot=''
  endif
  let g:tot=g:tot.str

endfunction
let s:callbacks = {
\ 'on_stdout': function('s:OnEvent'),
\ 'on_stderr': function('s:OnEvent'),
\ 'on_exit': function('s:OnEvent')
\ }
let cmd="g++ -Wall test.cpp -o test"
call jobstart(cmd, s:callbacks)
