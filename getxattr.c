#include <string.h>
#include "mex.h"

/* getxattr(const char *path, const char *name, void *value, size_t size,
 * u_int32_t position, int options);
 */

#define MAXLEN 1024

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *path = NULL, *name = NULL, value[MAXLEN];
  int retval;
  
  if (nrhs!=2)
    mexErrMsgTxt ("Invalid number of input arguments");
  
  if (mxIsEmpty(prhs[0]) || !mxIsChar(prhs[0]))
    mexErrMsgTxt ("Invalid input argument #1");
  
  if (mxIsEmpty(prhs[1]) || !mxIsChar(prhs[1]))
    mexErrMsgTxt ("Invalid input argument #2");
  
  path = mxArrayToString(prhs[0]);
  name = mxArrayToString(prhs[1]);
  
  memset(value, 0, MAXLEN);
  retval = getxattr(path, name, (void *)value, MAXLEN-1, 0, NULL);
  
  mxFree(path);
  mxFree(name);
  
  if (retval<0)
    mexErrMsgTxt ("Failed to get extended attribute");
  else
    plhs[0] = mxCreateString(value);
  
  return;
}
