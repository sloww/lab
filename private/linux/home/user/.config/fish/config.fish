#---------------+
#    alias      |
#---------------+
function c  -d 'Clear screen'
    clear
end

function cmake-clang -d 'Use clang as the C/C++ compiler'
    command cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang $argv
end

function df -d 'Print sizes in human readable'
    command df -h $argv
end

function man -d 'Use vim viewer to display manpage'
    command man $argv | col -b | command view -c 'set ft=man ts=8 nomod nolist' -
end

function sudo -d 'Use user env to call sudo'
    command sudo -E $argv
end

function rm -d 'Remove interactively'
    command rm -i $argv
end

# htop can't refresh when TERM is rxvt-unicode-256color
function t  -d 'Resource top usage'
    env TERM=screen htop $argv
end

function ssh -d 'SSH'
    env TERM=screen ssh $argv
end

function start_tunnel -d 'Start SSH tunnel on localhost on port :1314'
  while [ true ]
    echo 'Connect and listen on port 1314...'
    ssh -vvvCTD 1314 linode
    echo 'Retry in 3 seconds...'
    sleep 3
  end
end

function tmux -d 'Start with TERM=screen-256color-bce'
    env TERM=screen-256color-bce tmux $argv
end

function with_proxy -d 'Start under HTTP proxy localhost:1315'
    env http_proxy=localhost:1315 https_proxy=localhost:1315 $argv
end

#---------------+
#    env        |
#---------------+
set -x EDITOR   vim
set -x GOPATH   $HOME/go
set -x PATH     $GOPATH/bin /usr/local/go/bin $PATH

set -x GTK_IM_MODULE    fcitx
set -x QT_IM_MODULE     fcitx
set -x XMODIFIERS       @im=fcitx
set -x XIM              fcitx

#---------------+
#    tmux title |
#---------------+
# Set the tmux window title, depending on whether we are running something, or just prompting
function fish_title -d 'Set tmux title'
    set max_length 19
    if [ "fish" != $_ ] # command as title
        if [ ! -z "$TMUX" ]
            tmux rename-window "$_ $argv"
        end
    else if [ "$PWD" != "$LPWD" ]  # path as title
        set LPWD "$PWD"
        set SUBSTRING (eval echo $PWD | tail -c $max_length)
        if [ (expr length $PWD) -gt $max_length ]
            set SUBSTRING "..$SUBSTRING"
        end
        if [ ! -z "$TMUX" ]
            tmux rename-window "$SUBSTRING"
        end
    end
end

#---------------+
# external conf |
#---------------+
set config_ohio $HOME/.config/fish/config_ohio.fish
if [ -f $config_ohio ]
    source $config_ohio
end


#---------------+
# external conf |
#---------------+
# RVM: curl -L --create-dirs -o ~/.config/fish/functions/rvm.fish https://raw.github.com/lunks/fish-nuggets/master/functions/rvm.fish
