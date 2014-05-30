#---------------+
#    env        |
#---------------+
set BUNDLE /usr/local/bundle/config.fish
[ -f $BUNDLE ]; and source $BUNDLE

set -x GOPATH $HOME/Source/go
set -x PATH   $PATH $GOPATH/bin


#---------------+
#    alias      |
#---------------+
function c  --description 'Clear screen'
  clear
end

function df --description 'Print sizes in human readable'
  command df -h $argv
end

function man --description 'Use vim viewer to display manpage'
  command man $argv | col -b | command view -c 'set ft=man ts=8 nomod nolist' -
end

function rm --description 'Remove interactively'
  command rm -i $argv
end

function reset_launchpad --description 'Reset launchpad apps'
  set db (find ~/Library/Application\ Support/Dock/ -type f ! -name 'desktoppicture.db')
  rm -f $db; and killall -HUP Dock
end

function reset_appstore --description 'Resolve a failed download, "Use Purchases Page to download again"'
  rm -rf $TMPDIR/../C/com.apple.appstore
end

function simple_httpd --description 'Start the SimpleHTTPServer module of Python'
  python -m SimpleHTTPServer 18086
end

function ssh_tunnel --description 'SSH tunnel to AWS EC2'
  echo 'Serving on port 18081...'
  while [ true ]
    ssh -CnNT -D 18081 -i .ssh/tokyo-ec2.pem ubuntu@tokyo-ec2.aws
    sleep 10
  end
end
