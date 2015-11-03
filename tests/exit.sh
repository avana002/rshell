#!/bin/sh

cd ~/rshell/src

echo "Testing command: exit"

./rshell <<'EOF'
exit
EOF

echo "Testing command: ls ; exit"

./rshell <<'EOF'
ls ; exit
EOF

echo "Testing command: ls && exit"

./rshell <<'EOF'
ls && exit
EOF

echo "Testing command: ls || exit && ls"

./rshell <<'EOF'
ls || exit && ls
exit
EOF
