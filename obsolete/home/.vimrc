
set background=dark

" shell
map <F3> :split <BAR> ConqueTerm bash <Enter> 
" remove trailing slash
map <F4> :%s/\s\+$//
" TODO
" map <F4> <C-w>10-

" scons
autocmd BufReadPre SConstruct set filetype=python
autocmd BufReadPre SConscript set filetype=python

" Sets the autoindent spacing to 4 spaces. setlocal to limit this to the current (C++) buffer. 
setlocal shiftwidth=4

" Sets the spacing for tab characters to 4 spaces.
setlocal softtabstop=4

" Always use spaces; never use tab characters.
setlocal expandtab

" Limit the length of a line to 78 characters. Standard 4-6 actually specifies up to 110. 
setlocal textwidth=78

" Set the C indent configuration.
"
"    :0: Align case labels with the enclosing switch.
"     l1: Indent statements relative to the case label, not anything following.
"     g0: Align C++ scope (private/public) labels with the enclosing class.
"     (0: Align lines after "(foo" next to the unclosed parenthesis.
"     u0: Same as above for the next level of parentheses deeper.
"     W2s: Indent lines following a line-terminating unclosed parenthesis by two shiftwidths (8 spaces) 
" setlocal cino=:0,l1,g0,(0,u0,Ws

" Allow comments to start with two asterisks for Doxygen. 
""setlocal comments^=s2:/**,mb:*,ex:*/

" Highlights lines using the Doxygen \todo. 
syntax match cTodo /\todo/

fixdel
