#include "stringreplace.h"

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char *str_replace(const char *str, const char *old, const char *newStr)
{
	char *ret, *r;
	const char *p, *q;
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(newStr);
	int samesize = (oldlen == newlen);

	if (!samesize) {
		for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
			count++;
		/* This is undefined if p - str > PTRDIFF_MAX */
		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	} else
		retlen = strlen(str);

	if ((ret = malloc(retlen + 1)) == NULL)
		return NULL;

	r = ret, p = str;
	while (1) {
		/* If the old and new strings are different lengths - in other
					 * words we have already iterated through with strstr above,
					 * and thus we know how many times we need to call it - then we
					 * can avoid the final (potentially lengthy) call to strstr,
					 * which we already know is going to return NULL, by
					 * decrementing and checking count.
					 */
		if (!samesize && !count--)
			break;
		/* Otherwise i.e. when the old and new strings are the same
					 * length, and we don't know how many times to call strstr,
					 * we must check for a NULL return here (we check it in any
					 * event, to avoid further conditions, and because there's
					 * no harm done with the check even when the old and new
					 * strings are different lengths).
					 */
		if ((q = strstr(p, old)) == NULL)
			break;
		/* This is undefined if q - p > PTRDIFF_MAX */
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, newStr, newlen);
		r += newlen;
		p = q + oldlen;
	}
	strcpy(r, p);

	return ret;
}

///*
// * @brief
// * PHP's str_replace ported to C
// * @author Silver Moon (m00n.silv3r@gmail.com)
// * */

//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>

///*
// * Search and replace a string with another string , in a string
// * */
//char *str_replace(char *search , char *replace , char *subject)
//{
//	char  *p = NULL , *old = NULL , *new_subject = NULL ;
//	int c = 0 , search_size;

//	search_size = strlen(search);

//	//Count how many occurences
//	for(p = strstr(subject , search) ; p != NULL ; p = strstr(p + search_size , search))
//	{
//		c++;
//	}

//	//Final size
//	c = ( strlen(replace) - search_size )*c + strlen(subject);

//	//New subject with new size
//	new_subject = malloc( c );

//	//Set it to blank
//	strcpy(new_subject , "");

//	//The start position
//	old = subject;

//	for(p = strstr(subject , search) ; p != NULL ; p = strstr(p + search_size , search))
//	{
//		//move ahead and copy some text from original subject , from a certain position
//		strncpy(new_subject + strlen(new_subject) , old , p - old);

//		//move ahead and copy the replacement text
//		strcpy(new_subject + strlen(new_subject) , replace);

//		//The new start position after this search match
//		old = p + search_size;
//	}

//	//Copy the part after the last search match
//	strcpy(new_subject + strlen(new_subject) , old);

//	return new_subject;
//}
