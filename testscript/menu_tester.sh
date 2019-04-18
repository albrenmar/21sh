#!/bin/bash
cp ../21sh .
clear
select CHECK in "COMPIL 21SH" "REMOVE 21SH" "NORM EXPANSIONS" ALL SIMPLE ADVANCED LEAKS EXIT
    do
        clear
        if [ "$CHECK" == "COMPIL 21SH" ]
            then
                cd ..
                make
                cd testscript
                cp ../21sh .
        fi
        if [ "$CHECK" == "REMOVE 21SH" ]
            then
                cd ..
                make fclean
                rm -r 21sh.dSYM
                cd testscript
                rm 21sh
                rm -r 21sh.dSYM
        fi
        if [ "$CHECK" == "NORM EXPANSIONS" ]
            then
                norminette ../srcs/expansions
        fi
        if  [ "$CHECK" == 'SIMPLE' ]
            then
                source menu_exp_simple.sh
        fi
        if  [ "$CHECK" == 'LEAKS' ]
            then
                sh leaks_tester.sh
        fi
        if [ "$CHECK" == 'ALL' ]
            then
                echo "------------------------------------------"
                echo "         test expansions simple         "
                source expansion_sim_~.sh
                source expansion_sim_\$.sh
                echo "------------------------------------------"
                echo "         test expansions advanced         "
                source expansion_adv_%.sh
                source expansion_adv_%\%.sh
                source expansion_adv_#.sh
                source expansion_adv_#\#.sh
                source expansion_adv_start#.sh
                source expansion_adv_+.sh
                source expansion_adv_\?.sh
                source expansion_adv_\=.sh
                source expansion_adv_\-.sh
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