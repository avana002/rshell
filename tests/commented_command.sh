#!/bin/sh

cd ~/rshell/src

echo "Testing command: ls # -l"

./rshell <<'EOF'
ls # -l
exit
EOF

