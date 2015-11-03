#!/bin/sh

cd ~/rshell/src

echo "Testing command: ls ; ls"

./rshell <<'EOF'
ls ; ls
exit
EOF

echo "Testing command: ls && ls"

./rshell <<'EOF'
ls && ls
exit
EOF

echo "Testing command: ls || ls"

./rshell <<'EOF'
ls || ls
exit
EOF

echo "Testing command: ls ; ls ; ls ; ls ; ls"

./rshell <<'EOF'
ls ; ls ; ls ; ls ; ls
exit
EOF

echo "Testing command: ls || ls || ls || ls || ls"

./rshell << 'EOF'
ls || ls || ls || ls || ls
exit
EOF
