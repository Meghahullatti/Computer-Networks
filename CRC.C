#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char rem[50], a[50], s[50], c, msj[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generator polynomial: ");
    scanf("%s", gen);

    printf("Generator polynomial (CRC-CCITT): %s\n", gen);
    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message: ");
    scanf("%s", msj);

    n = strlen(msj);

    // Copy message and append zeros
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = '0';
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    // Division process
    for (i = 0; i < n; i++)
    {
        if (a[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++, t++)
            {
                if (a[t] == gen[j])
                    a[t] = '0';
                else
                    a[t] = '1';
            }
        }
    }

    // Remainder (checksum)
    for (i = 0; i < k; i++)
        rem[i] = a[n + i];
    rem[k] = '\0';

    printf("\nChecksum (remainder):\n");
    puts(rem);

    // Append checksum to message
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = rem[i];
    a[n + k] = '\0';

    printf("\nMessage with checksum appended:\n");
    puts(a);

    // Receiver side
    printf("\nEnter the received message: ");
    scanf("%s", s);

    n = strlen(s);
    flag = 0;

    // Division again for checking
    for (i = 0; i < n - k; i++)
    {
        if (s[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++, t++)
            {
                if (s[t] == gen[j])
                    s[t] = '0';
                else
                    s[t] = '1';
            }
        }
    }

    // Get remainder
    for (i = 0; i < k; i++)
        rem[i] = s[n - k + i];
    rem[k] = '\0';

    // Check for errors
    for (i = 0; i < k; i++)
    {
        if (rem[i] == '1')
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("\nReceived polynomial is error-free ✅\n");
    else
        printf("\nReceived polynomial has an error ❌\n");

    return 0;
}
