#!/bin/sh

cd ..
cd src

echo "Testing command: ls # -l"

./rshell <<'EOF'
ls # -l
exit
EOF

