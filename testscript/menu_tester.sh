#!/bin/bash
cp ../42sh .
clear
select CHECK in ALL SIMPLE ADVANCED EXIT
    do
        clear
        if [ "$CHECK" == 'ALL' ] ||
           [ "$CHECK" == 'SIMPLE' ]
            then
                source expansion_simple.sh
        fi
        if [ "$CHECK" == 'ALL' ]
            then
                echo "------------------------------------------"
                echo "         test expansions advanced         "
                source expansion_adv_%.sh
                source expansion_adv_#.sh
                source expansion_adv_start#.sh
                source expansion_adv_+.sh
                source expansion_adv_\?.sh
        elif [ "$CHECK" == 'ADVANCED' ]
            then
                clear
                source menu_exp_advanced.sh
        elif [ "$CHECK" == 'EXIT' ]
            then
                exit
        fi
            sleep 1
            echo "\n\n"
            read -p "****PRESS ANY KEY****"
            clear
            sh menu_tester.sh
            exit
    done