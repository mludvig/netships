#!/usr/bin/awk
BEGIN{sum=0} 

/total/{sum+=$1} 

END{printf("\nAll source files have %d lines\n\n",sum)}
