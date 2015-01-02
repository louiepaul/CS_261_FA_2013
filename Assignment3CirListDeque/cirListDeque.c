/*
 * circListDeque.c
 *
 *  Created on: Oct 23, 2013
 *      Author: Ian Paul
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q)
{
  	/* FIXME: you must write this */
	q->Sentinel = (struct DLink *)malloc(sizeof(struct DLink));//allocate sentinel
	assert(q->Sentinel != 0);//make sure allocation worked

	q->Sentinel->prev = q->Sentinel;//sentinel's previous pointer points to null
	q->Sentinel->next = q->Sentinel; //sentinel's back pointer has a next pointer to null

	q->size = 0;
}

/*
 create a new circular list deque

 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* FIXME: you must write this */
	//need to check is size is 0, if so we create the first link
    struct DLink *newLink = (struct DLink *) malloc(sizeof(struct DLink));
    assert(newLink != 0);

    newLink->value = val;

    return newLink;

	/*temporary return value..you may need to change it*/

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	/* FIXME: you must write this */
	//I would think that you would just add a link and have the sentinel's next pointer to the link we create
	//but it looks like the requirements are asking for us to add a link after the lnk passed in?
	//if so it woudl just be lnk->next = new; ?
	//how would you have the lnks next link have it's prev pointer to the new link, lnk->next->prev = new; ???
	//new->next = lnk->next; //new link gets assigned the lnks next
	//new->prev = lnk;
    struct DLink *newLink = _createLink(v);
    newLink->next = lnk->next;
    newLink->prev = lnk;
    newLink->value = v;

    lnk->next->prev = newLink;
    lnk->next = newLink;


    q->size++;

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	 _addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	 _addLinkAfter(q, q->Sentinel, val);

}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	/*temporary return value..you may need to change it*/

	return(q->Sentinel->next->value);//return the link the sentinel's next points to
	//return(1);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	/*temporary return value..you may need to change it*/
	//return(1);

	//assert(q->Sentinel->prev != 0);//first make sure q is not empty

	return(q->Sentinel->prev->value);//return the link the sentinel's prev points to
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	/* FIXME: you must write this */

	lnk->next->prev = lnk->prev;
	lnk->prev->next = lnk->next;
	free(lnk);
	q->size--;

	//would we use a temp link that is assigned the lnk passed in?
	//need to have the sentinels previous pointer now point to the lnks previous link
	//need to have the lnks previous link to have it's next pointer point to the sentinel
	//need to decrement the size right?

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	/* FIXME: you must write this */

	_removeLink (q, q->Sentinel->next);
	//call on remove link and point to sentintels->next

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	/* FIXME: you must write this */
	//assert (!isEmptyListDeque(q));
	_removeLink(q, q->Sentinel->prev);
	//call on removeLink and point to the sentinels prev
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */

	while(q->size > 0)
		{
			_removeLink(q, q->Sentinel->next);
		}


}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	/* FIXME: you must write this */
	if(q->size == 0)
		return(1);
	else
		return(0);

	/*temporary return value..you may need to change it*/

}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */

	struct DLink* temp = q->Sentinel->next;

	printf("The link values are:\n");
	while (temp != q->Sentinel)
	{
		printf("%f\n",temp->value);
		temp = temp->next;
	}
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */


	struct cirListDeque* newQ = createCirListDeque();
    while(!isEmptyCirListDeque(q))
    {
        addBackCirListDeque(newQ, backCirListDeque(q));
        removeBackCirListDeque(q);
    }
    q->Sentinel = newQ->Sentinel;
    q->size = newQ->size;
    free(newQ);


}
