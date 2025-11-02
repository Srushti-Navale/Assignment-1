int chaininsert(int hash[][3], int mod, int key)
{
    int index = key % mod;
    int prev, newIndex;

    // Case 1: Direct position empty
    if (hash[index][1] == 0)
    {
        hash[index][1] = key;
        hash[index][2] = -1;
        return 1;
    }

    // Case 2: Collision → find end of chain for this index
    prev = index;
    while (hash[prev][2] != -1 && (hash[ hash[prev][2] ][1] % mod) == index)
    {
        prev = hash[prev][2];   // move to next node of chain
    }

    // Case 3: Find empty slot using linear probing
    for (int i = 1; i < mod; i++)
    {
        newIndex = (index + i) % mod;

        if (hash[newIndex][1] == 0)   // Found empty slot
        {
            hash[newIndex][1] = key;
            hash[newIndex][2] = -1;

            // If previous node belongs to same chain, attach new node
            if (hash[prev][1] % mod == index)
            {
                hash[prev][2] = newIndex;
            }
            else
            {
                // Find last node of this chain pointing to -1
                for (int j = index + 1; j < mod; j++)
                {
                    if (hash[j][1] % mod == index && hash[j][2] == -1 && j != newIndex)
                    {
                        hash[j][2] = newIndex;
                        break;
                    }
                }
            }

            return 1;  // insert success
        }
    }

    return 0; // Table full → no space
}
