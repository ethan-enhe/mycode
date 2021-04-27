echo "set runtimepath^=~/.vim runtimepath+=~/.vim/after\nlet &packpath = &runtimepath\nsource ~/.vimrc" >> init.vim
mkdir -p ~/.config/nvim
mv init.vim ~/.config/nvim/init.vim

wget blog-e.tk/file/vimrc
wget blog-e.tk/file/plug.vim
mkdir -p  ~/.vim/autoload/
mv plug.vim  ~/.vim/autoload/plug.vim
mv vimrc ~/.vimrc
