#!/bin/sh

cd ..
cd src

echo "Testing command: test rshell && echo file exists"

./rshell <<'EOF'
test rshell && echo file exists
exit
EOF

echo "Testing command: test -e rshell && echo file exists"

./rshell <<'EOF'
test -e rshell && echo file exists
exit
EOF

echo "Testing command: test -f rshell && echo regular file"

./rshell <<'EOF'
test -f rshell && echo regular file
exit
EOF

echo "Testing command: test -d rshell || echo not directory"

./rshell <<'EOF'
test -d rshell || echo not directory
exit
EOF

echo "Testing command: [ rshell ] && echo file exists"

./rshell <<'EOF'
[ rshell ] && echo file exists
exit
EOF
