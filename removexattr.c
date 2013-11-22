#include <string.h>
#include "mex.h"

/* removexattr(const char *path, const char *name, int options);
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  char *path = NULL, *name = NULL;
  int retval;
  
  if (nrhs!=2)
    mexErrMsgTxt ("Invalid number of input arguments");
  
  if (mxIsEmpty(prhs[0]) || !mxIsChar(prhs[0]))
    mexErrMsgTxt ("Invalid input argument #1");
  
  if (mxIsEmpty(prhs[1]) || !mxIsChar(prhs[1]))
    mexErrMsgTxt ("Invalid input argument #2");
  
  path = mxArrayToString(prhs[0]);
  name = mxArrayToString(prhs[1]);
  
  retval = removexattr(path, name, NULL);
  
  mxFree(path);
  mxFree(name);
  
  if (retval<0)
    mexErrMsgTxt ("Failed to remove extended attribute");
  else
    plhs[0] = mxCreateDoubleScalar(retval);
  
  return;
}
