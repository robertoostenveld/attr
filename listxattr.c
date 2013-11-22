#include <string.h>
#include <stdlib.h>
#include "mex.h"

/* listxattr(const char *path, char *namebuf, size_t size, int options);
 *
 */

#define MAXLEN 1024

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *path = NULL, *namebuf = NULL, *name;
  int size, ssize, num = 0, i;
  
  if (nrhs!=1)
    mexErrMsgTxt ("Invalid number of input arguments");
  
  if (mxIsEmpty(prhs[0]) || !mxIsChar(prhs[0]))
    mexErrMsgTxt ("Invalid input argument #1");
  
  path = mxArrayToString(prhs[0]);
  
  size = 1;
  ssize = MAXLEN;
  while (ssize>=size) {
    size *= MAXLEN;
    if (namebuf)
      namebuf = realloc(namebuf, size);
    else
      namebuf = malloc(size);
    memset(namebuf, 0, size);
    ssize = listxattr(path, (void *)namebuf, size-1, NULL);
  }
  
  mxFree(path);
  
  for (i=0; i<ssize; i++)
    num += (namebuf[i]==0);
  
  plhs[0] = mxCreateCellMatrix(1, num);
  
  name = namebuf;
  for(i=0; i<num; i++) {
    mxSetCell(plhs[0], i, mxCreateString(name));
    name += strlen(name)+1;
  }
  
  free(namebuf);
  
  if (ssize<0)
    mexErrMsgTxt ("Failed to get extended attribute");
  
  return;
}
