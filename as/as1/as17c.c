/* translated from as17.s */

/* void _combin(r0, r3, r5)
 *  value     : r0,r3
 *  reference : r5
 */
combin(r0, r3, r5) int r0; int r3; int* r5;{
  int local1;
  int local2;

  local1 = r0;
  local1 = local1 | r3;

  local1 = (040) & local1;
  r0     = (037) & r0;
  r3     = (037) & r3;

  if(r0 > r3){
    local2 = r0;
    r0 = r3;
    r3 = local2;
  }

  /* 1: */
  if(r0 == 0){ 
    r5++;
    r3 = 0;
  }else if(*(r5++) != 0 || r0 == r3){
    r3 = 1;
  }

  r3 = r3 | local1;

  return; 
}

