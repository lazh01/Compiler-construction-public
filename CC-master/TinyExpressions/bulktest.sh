for i in $( ls Tests/ | grep src); do
            echo \|----- Test: $i -----\|
            echo
            ./compiler <Tests/$i \n
            echo
            echo \|----- end: $i ------\|
            echo
            echo
        done
