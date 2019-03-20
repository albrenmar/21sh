SUCCESS="\033[1;32m\t\tSUCCESS\033[1;37m"
ERROR="\033[1;31m\t\t****ERROR****\033[1;37m"
TEST="~"
echo "                   *~*                    "
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="~/"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="~/test"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="test~"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="/~"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="~alsomvil"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="test/~alsomvil/"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="~+"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="~-"
echo "echo $TEST"
echo "------------------------------------------"
CMD_42SH=$(echo "echo $TEST" | ./42sh)
CMD_BASH=$(echo "echo $TEST" | /bin/bash)
if [ $CMD_42SH == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42SH"
        echo "$CMD_BASH"
fi
sleep 0.5