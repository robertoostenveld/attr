#include <string.h>
#include "mex.h"

/* setxattr(const char *path, const char *name, void *value, size_t size,
 * u_int32_t position, int options);
 */

#define MAXLEN 1024

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *path = NULL, *name = NULL, *value = NULL;
  int retval, size = MAXLEN;
  
  if (nrhs!=3)
    mexErrMsgTxt ("Invalid number of input arguments");
  
  if (mxIsEmpty(prhs[0]) || !mxIsChar(prhs[0]))
    mexErrMsgTxt ("Invalid input argument #1");
  
  if (mxIsEmpty(prhs[1]) || !mxIsChar(prhs[1]))
    mexErrMsgTxt ("Invalid input argument #2");
  
  if (mxIsEmpty(prhs[2]) || !mxIsChar(prhs[2]))
    mexErrMsgTxt ("Invalid input argument #3");
  
  size = mxGetM(prhs[2]) * mxGetN(prhs[2]);
  if (size>(MAXLEN-1))
    mexErrMsgTxt ("Attibute value is too long");
  
  path  = mxArrayToString(prhs[0]);
  name  = mxArrayToString(prhs[1]);
  value = mxArrayToString(prhs[2]);
  
  retval = setxattr(path, name, (void *)value, size, 0, NULL);
  
  mxFree(path);
  mxFree(name);
  mxFree(value);
  
  if (retval<0)
    mexErrMsgTxt ("Failed to set extended attribute");
  else
    plhs[0] = mxCreateDoubleScalar(retval);
  return;
}
