#!/bin/sh

cd ~/rshell/src

echo "Testing command: ls"

./rshell <<'EOF'
ls
exit
EOF

echo "Testing command: ls -l"

./rshell <<'EOF'
ls -l
exit
EOF

echo "Testing command: echo hello world"

./rshell <<'EOF'
echo hello world
exit
EOF
