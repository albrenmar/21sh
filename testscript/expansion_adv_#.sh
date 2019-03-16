echo "                    #                     "
echo "echo \${HOME#/U}"
echo "------------------------------------------"
echo "echo \${HOME#/U}" | ./42sh
echo "echo \${HOME#/U}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#*/U}"
echo "------------------------------------------"
echo "echo \${HOME#*/U}" | ./42sh
echo "echo \${HOME#*/U}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#/U*}"
echo "------------------------------------------"
echo "echo \${HOME#/U*}" | ./42sh
echo "echo \${HOME#/U*}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#lo}"
echo "------------------------------------------"
echo "echo \${HOME#lo}" | ./42sh
echo "echo \${HOME#lo}" | /bin/bash
sleep 0.5
echo "------------------------------------------"
echo "echo \${PEPE#lo}"
echo "------------------------------------------"
echo "echo \${PEPE#lo}" | ./42sh
echo "echo \${PEPE#lo}" | /bin/bash
sleep 0.5
#echo "-----------------------------------------"
#echo "test autre"
#echo "-----------------------------------------"
#echo "echo '$HOME'" | ./42sh
#echo "echo '$HOME'" | /bin/bash
#echo "-----------------------------------------"