#include "cons.h"

struct dictionary_entry dict[TABLE_SIZE];

unsigned hash(unsigned prefix, unsigned newchar){
  
  if (LINEAR)   
    return (0); 
  else
    return ((prefix * newchar) % TABLE_SIZE);
}
  


// Searches the dictionary for a match for the phrase (prefix, newchar).

// When hash return 0 the search is a simple linear scan of the dictionary,
// from the start to the end.

// Otherwise it searches starting from "index" returned by hash() in steps
// of "offset". The size of the dictionary is a prime number larger than
// MAX_CODE, so all entries will eventually be examined if necessary.

// See cons.h for the definitions.

unsigned int findPhrase(unsigned prefix, unsigned newchar)
{
unsigned index;
unsigned offset;

index = hash(prefix, newchar);


offset = index+1;


 for (; ;)   {
   if (dict[index].code == UNUSED)
     return index;

   if ( (dict[index].prefixcode == prefix) && (dict[index].character == (char) newchar) )
     return index;
   
     index = (index+offset);
     if (index >= TABLE_SIZE) index -= TABLE_SIZE; // Wrap around 


    }
}




