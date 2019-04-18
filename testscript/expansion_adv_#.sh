SUCCESS="\033[1;32m\t\tSUCCESS\033[1;37m"
ERROR="\033[1;31m\t\t****ERROR****\033[1;37m"
echo "                   *#*                    "
echo "echo \${HOME#/U}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#/U}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#/U}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#*/U}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#*/U}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#*/U}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#/U*}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#/U*}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#/U*}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#/}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#/}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#/}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#*/}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#*/}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#*/}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#/*}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#/*}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#/*}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${HOME#lo}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${HOME#lo}" | ./21sh)
CMD_BASH=$(echo "echo \${HOME#lo}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${PEPE#lo}"
echo "------------------------------------------"
CMD_21sh=$(echo "echo \${PEPE#lo}" | ./21sh)
CMD_BASH=$(echo "echo \${PEPE#lo}" | /bin/bash)
if [ $CMD_21sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_21sh"
        echo "$CMD_BASH"
fi
sleep 0.5
#echo "-----------------------------------------"
#echo "test autre"
#echo "-----------------------------------------"
#echo "echo '$HOME'" | ./21sh
#echo "echo '$HOME'" | /bin/bash
#echo "-----------------------------------------"