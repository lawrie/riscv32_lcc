/*
  * malloc for RISC_V / LCC standard libary. Edited from 4.2BSD:
  *
  * malloc.c (Caltech) 2/21/82
  * Chris Kingsley, kingsley@cit-20.
  *
  * This is a very fast storage allocator.  It allocates blocks of a small 
  * number of different sizes, and keeps free lists of each size.  Blocks that
  * don't exactly fit are passed up to the next larger size.  In this 
  * implementation, the available sizes are 2^n-4 (or 2^n-12) bytes long.
  * This is designed for use in a program that uses vast quantities of memory,
  * but bombs when it runs out. 
  */

#include <sys/types.h>
#include <errno.h>

#define NULL ((void*)0)

/*
  * The overhead on a block is at least 4 bytes.  When free, this space
  * contains a pointer to the next free block, and the bottom two bits must
  * be zero.  When in use, the first byte is set to MAGIC, and the second
  * byte is the size index.  The remaining bytes are for alignment.
  * If range checking is enabled and the size of the block fits
  * in two bytes, then the top two bytes hold the size of the requested block
  * plus the range checking words, and the header word MINUS ONE.
  */
union	overhead {
  union	overhead *ov_next;	/* when free */
  struct {
    u_char	ovu_magic;	/* magic number */
    u_char	ovu_index;	/* bucket # */
  } ovu;
#define	ov_magic	ovu.ovu_magic
#define	ov_index	ovu.ovu_index
};

#define	MAGIC		0xff		/* magic # on accounting info */

/*
  * nextf[i] is the pointer to the next free block of size 2^(i+3).  The
  * smallest allocatable block is 8 bytes.  The overhead information
  * precedes the data area returned to the user.
  */
#define	NBUCKETS 30
static	union overhead *nextf[NBUCKETS];
void *sbrk(unsigned);

/*
  * Allocate more memory to the indicated bucket.
  */
static void
morecore(int bucket)
{
  union overhead *op;
  int rnu;       /* 2^rnu bytes will be requested */
  int nblks;     /* become nblks blocks of the desired size */
  int siz;

  /* take 2k unless the block is bigger than that */
  rnu = (bucket <= 8) ? 11 : bucket + 3;
  nblks = 1 << (rnu - (bucket + 3));  /* how many blocks to get */
  if (rnu < bucket)
    rnu = bucket;
  op = (union overhead *)sbrk(1 << rnu);
  /* no more room! */
  if ((int)op == -1)
    return;
  /*
   * Round up to minimum allocation size boundary
   * and deduct from block count to reflect.
   */
  if ((int)op & 7) {
    op = (union overhead *)(((int)op + 8) &~ 7);
    nblks--;
  }
  /*
   * Add new memory allocated to that on
   * free list for this hash bucket.
   */
  nextf[bucket] = op;
  siz = 1 << (bucket + 3);
  while (--nblks > 0) {
    op->ov_next = (union overhead *)((caddr_t)op + siz);
    op = (union overhead *)((caddr_t)op + siz);
  }
}

void *
malloc(unsigned nbytes)
{
  union overhead *p;
  int bucket = 0;
  unsigned shiftr;

  /*
   * Convert amount of memory requested into
   * closest block size stored in hash buckets
   * which satisfies request.  Account for
   * space used per block for accounting.
   */
  nbytes += sizeof (union overhead);
  nbytes = (nbytes + 3) &~ (unsigned)3; 
  shiftr = (nbytes - 1) >> 2;
  /* apart from this loop, this is O(1) */
  while (shiftr >>= 1)
    bucket++;
  /*
   * If nothing in hash bucket right now,
   * request more memory from the system.
   */
  if (nextf[bucket] == NULL)    
    morecore(bucket);
  if ((p = (union overhead *)nextf[bucket]) == NULL)
    return (NULL);
  /* remove from linked list */
  nextf[bucket] = nextf[bucket]->ov_next;
  p->ov_magic = MAGIC;
  p->ov_index= bucket;
  return ((void *)(p + 1));
}

void
free(char *cp)
{   
  int size;
  union overhead *op;

  if (cp == NULL)
    return;
  op = (union overhead *)((caddr_t)cp - sizeof (union overhead));
  /* sanity */
  if (op->ov_magic != MAGIC)
    return;
  size = op->ov_index;
  op->ov_next = nextf[size];
  nextf[size] = op;
}

void *
realloc(cp, nbytes)
  char *cp; 
  unsigned nbytes;
{   
  u_int onb;
  union overhead *op;
  char *res;
  int i;

  if (cp == NULL)
    return (malloc(nbytes));
  if (nbytes == 0) {
    free(cp);
    return NULL;
  }
  op = (union overhead *)((caddr_t)cp - sizeof (union overhead));
  if (op->ov_magic == MAGIC) {
    i = op->ov_index;
  } else
    return NULL;

  onb = (1 << (i + 3)) - sizeof (*op);
  /* avoid the copy if same size block */
  if (nbytes <= onb && nbytes > (onb >> 1) - sizeof(*op))
    return(cp);
  if ((res = malloc(nbytes)) == NULL)
    return (NULL);
  if (cp != res)			/* common optimization */
    bcopy(cp, res, (nbytes < onb) ? nbytes : onb);

  free(cp);
  return (res);
}

void* _brk(void*);
static unsigned long heap_end;
#define ERRVAL ((unsigned long)(-1))

int
brk(void* newbrk)
{
  if (heap_end == 0) {
          heap_end = (unsigned long)_brk(0);
  }

      if (_brk(newbrk) != newbrk) {
    errno = ENOMEM;
          return -1;
  }

  heap_end = (unsigned long)newbrk;
  return 0;
}

void *
sbrk(unsigned incr)
{
  if (heap_end == 0) {
          heap_end = (unsigned long)_brk(0);
  }

  if ((unsigned long)_brk((void*)(heap_end + incr)) != (heap_end + incr)) {
    errno = ENOMEM;
    return (void *)ERRVAL;
  }

  heap_end += incr;
  return (void *)(heap_end - incr);
}

/*
  * syscall _brk(void*)
  *

_brk:
  mv x10,x12
  li x17,214
  ecall
  jalr x0,x1,0
*/
