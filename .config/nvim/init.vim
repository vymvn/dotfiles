set number
set mouse=a
set autoindent
set tabstop=4
set smarttab

call plug#begin()

Plug 'preservim/nerdtree'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'https://github.com/vim-airline/vim-airline.git'
Plug 'https://github.com/tpope/vim-commentary.git'

call plug#end()


nnoremap <C-t> :NERDTreeToggle<CR>
inoremap <expr> <Tab> pumvisible() ? coc#_select_confirm() : "<Tab>"
