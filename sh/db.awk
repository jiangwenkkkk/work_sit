#!/usr/local/bin/awk

BEGIN{
  is_wrong = 0;
  start = 0;
  ip
  wrong_ip[0]=0
  wrong_pos=1
}


{
    if(match($1,"^[0-9]+.[0-9]+.*"))
    {
        printf $1"----begin\n";
        ip = $1;
        wrong=0
    }
    else
    {
        len = length($5);
        subs = substr($5,1, len-1);
        num = strtonum(subs);
        if (num > 8 && is_wrong==0)
        {

           is_wrong=1
           wrong_ip[wrong_pos] = ip
           wrong_pos++

        }

    }


}


END{
   if (wrong_pos == 0)
    {
       printf "every disk is ok\n"
    }
    else
    {
       for (i = 1; i < wrong_pos; i++)
       {
           printf wrong_ip[i] " is wrong"
       }
    }

}