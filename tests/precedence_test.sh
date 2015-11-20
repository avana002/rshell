#!/bin/sh

cd ..
cd src

echo "Testing command: (ls)"

./rshell <<'EOF'
(ls)
exit
EOF

echo "Testing command: ( ls )"

./rshell <<'EOF'
( ls )
exit
EOF

echo "Testing command: ( echo A || echo B ) && echo C"

./rshell <<'EOF'
( echo A || echo B ) && echo C
exit
EOF

echo "Testing command: echo A || ( echo B && echo C )"

./rshell <<'EOF'
echo A || ( echo B && echo C )
exit
EOF
