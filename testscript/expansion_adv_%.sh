echo "                    %                     "
echo "echo \${HOME%se}"
echo "------------------------------------------"
echo "echo \${HOME%se}" | ./42sh
echo "echo \${HOME%se}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME%*se}"
echo "------------------------------------------"
echo "echo \${HOME%*se}" | ./42sh
echo "echo \${HOME%*se}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME%se*}"
echo "------------------------------------------"
echo "echo \${HOME%se*}" | ./42sh
echo "echo \${HOME%se*}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME%lo}"
echo "------------------------------------------"
echo "echo \${HOME%lo}" | ./42sh
echo "echo \${HOME%lo}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${PEPE%lo}"
echo "------------------------------------------"
echo "echo \${PEPE%lo}" | ./42sh
echo "echo \${PEPE%lo}" | /bin/bash
sleep 0.5
#echo "-----------------------------------------"
#echo "test autre"
#echo "-----------------------------------------"
#echo "echo '$HOME'" | ./42sh
#echo "echo '$HOME'" | /bin/bash
#echo "-----------------------------------------"