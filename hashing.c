int insert(int hash[][3],int mod ,int key)
{
    int index,last , newindex;
    index = key %mod ;

    if(hash[index][1]== 0 )
    {
        hash[index][1]==key;
        hash[index][2]==-1;
        return 1;
    }
    else
    {  
        last = index;
        while(hash[last][2] != -1 && hash[hash[last][2]][1] % mod == index)
        {
            //last of the same chain having same index
            last = hash[last][2];//moves to next chained index
        }
       //we got last index of chain to link it if new key having same index is added

        // finding empty space by linear probbing
        for(int i =1 ;i<mod ; i++)
        {
            newindex = (index +1)% mod;
             
            if(hash[newindex][1]==0)
            {
                hash[newindex][1] = key;
                hash[newindex][2] = -1;

                //checking is last index element having same index or not
                if(hash[last][1] % mod == index )
                {
                    hash[last][2] = newindex;
                } 
                else
                {
                    for(int j =index + 1;j<mod;j++)
                    {
                        if ( hash[j][1] %mod == index && hash[j][2] == -1 && j != newindex)
                        {
                            hash[j][2] = newindex;
                            break;
                        }
                    }
                }
               return 1;
            }
            
        }
    }
    return 0;
}