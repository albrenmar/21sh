COUNT=1
rm /Users/mjose/Projects/42sh/testscript/logs/TOTAL_LEAKS.txt
while read TEST
	do
		echo "$TEST" >> /Users/mjose/Projects/42sh/testscript/logs/TOTAL_LEAKS.txt
		echo "$TEST 1>/Users/mjose/Projects/42sh/testscript/logs/test_display_$COUNT.txt 2>/Users/mjose/Projects/42sh/testscript/logs/test_display_errors_$COUNT.txt" | valgrind --leak-check=full ./42sh 2>./logs/test_leaks_$COUNT.txt
		LEAKS=$(cat ./logs/test_leaks_$COUNT.txt | grep "definitely lost:")
		echo "$LEAKS" >> /Users/mjose/Projects/42sh/testscript/logs/TOTAL_LEAKS.txt
		LEAKS=$(cat ./logs/test_leaks_$COUNT.txt | grep "indirectly lost:")
		echo "$LEAKS" >> /Users/mjose/Projects/42sh/testscript/logs/TOTAL_LEAKS.txt
		ERRORS=$(cat ./logs/test_leaks_$COUNT.txt | grep "ERROR SUMMARY:")
		echo "$ERRORS" >> /Users/mjose/Projects/42sh/testscript/logs/TOTAL_LEAKS.txt
		COUNT=$((COUNT+1))
	done <<< "`cat ./massive_attack`"