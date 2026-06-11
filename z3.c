#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MMAX 1000
#define N 100

const char* readline()
{
    static char buffer[MMAX+1];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

char* find_out(const char* buffer)
{
    static char tmp[N];
    for (int i = 0; i < N; i++)
    {
        if (isprint(buffer[i]) && buffer[i] != ' ')
        {
            tmp[i] = buffer[i];
        }
        else
        {
            tmp[i] = '\0';
            break;
        }
    }
    return tmp;
}

int load_string(const char* buffer, char* op)
{
    buffer += 3;
    if (strlen(buffer) > N)
    {
        return 0;
    }
    
    strcpy(op, buffer);
    return 1;
}

int out(const char* buffer, char* op, char* mem, char* sp, char* ep)
{
    buffer += 4;
    char* command = find_out(buffer);

    if (!strcmp(command,"op") && buffer[2] == '\0')
    {
        printf("%s\n", op);
    }
    else if (!strcmp(command,"mem") && buffer[3] == '\0')
    {
        printf("%s\n", mem);
    }
    else if (!strcmp(command,"range") && buffer[5] == '\0')
    {
        if (sp>ep)
        {
            return 0;
        }
        else if (sp == ep)
        {
            printf("\n");
            return 1;
        }

        char *ptr = sp;
        for (ptr; ptr < ep; ptr++)
        {
            printf("%c", *ptr);
        }
        printf("\n");
    }

    return 1;
}

int del(char* sp, char* ep, char* op)
{
    if (sp>ep)
    {
        return 0;
    }
    else if (sp == ep)
    {
        return -1;
    }
   
    while (ep<(op+strlen(op)))
    {
        *sp = *ep;
        sp++;
        ep++;
    }
    *sp = '\0';
    return 1;
}

int crop(char* sp, char* ep, char*op)
{
    if (sp == ep)
    {
        *op = '\0';
        return -1;
    }
    else if (sp>ep)
    {
        return 0;
    }
    else 
    {
        while (sp<ep)
        {
            *op = *sp;
            op++;
            sp++;
        }
        *op = '\0';
        return 1;
    }
}

int copy(char* sp, char* ep, char* op, char* mem)
{
    if (sp>ep)
    {
        return 0;
    }
    else if (sp == ep)
    {
        return -1;
    }

    while (sp<ep)
    {
        *mem = *sp;
        sp++;
        mem++;
    }
    *mem = '\0';

    return 1;
}

void replace(char* sp, char* ep, char* op, char* mem)
{
    if (strlen(mem) == 0)
    {
        return;
    }
    
    int len = strlen(mem);
    int i = 0;
    while (sp<ep && i<len)
    {
        *sp = *mem;
        sp++;
        mem++;
        i++;
    }
}

int main()
{
    char op[N+1];
    char mem[N+1];
    op[0] = '\0';
    mem[0] = '\0';
    char* sp = op;
    char* ep = op;

    while (1)
    {
        const char* buffer = readline();
        char* command = find_out(buffer);
        
        if (!strcmp(command,"quit"))
        {
            break;
        }
        else if (!strcmp(command,"in"))
        {
            if (!load_string(buffer, op))
            {
                printf("ERR_OVERFLOW");
                break;
            }
            ep = &op[strlen(op)];
        }
        else if (!strcmp(command,"out"))
        {
            if (!out(buffer, op, mem, sp, ep))
            {
                printf("ERR_POSITION");
                break;
            }
        }
        else if (!strcmp(command,"move"))
        {
            buffer += 5;
            char* command = find_out(buffer);
            if (!strcmp(command,"sp") && buffer[2] == ' ')
            {
                buffer += 3;
                char* tmp1 = find_out(buffer);
                int num1 = atoi(tmp1);
                sp += num1;
                if (sp < op || sp > op+strlen(op))
                {
                    printf("ERR_OUT_OF_RANGE");
                    break;
                }
            }
            else if (!strcmp(command,"ep") && buffer[2] == ' ')
            {
                buffer += 3;
                char* tmp2 = find_out(buffer);
                int num2 = atoi(tmp2);
                ep += num2;
                if (ep < op || ep > op+strlen(op))
                {
                    printf("ERR_OUT_OF_RANGE");
                    break;
                }
            }
        }
        else if (!strcmp(command,"start"))
        {
            buffer += 6;
            char* command = find_out(buffer);
            if (!strcmp(command,"sp") && buffer[2] == '\0')
            {
                sp = op;
            }
            else if (!strcmp(command,"ep") && buffer[2] == '\0')
            {
                ep = op;
            }
        }
        else if (!strcmp(command,"end"))
        {
            buffer += 4;
            char* command = find_out(buffer);
            if (!strcmp(command,"sp") && buffer[2] == '\0')
            {
                sp = op+strlen(op);
            }
            else if (!strcmp(command,"ep") && buffer[2] == '\0')
            {
                ep = op+strlen(op);
            }
        }
        else if (!strcmp(command,"first") && buffer[5] == '\0')
        {
            int var = 0;
            for (int i = 0; i < strlen(op); i++)
            {
                if (isalnum(op[i]))
                {
                    var++;
                }         
            }
            if (var == 0)
            {
                sp = op;
                ep = op;
            }
            else
            {
                sp = op;
                ep = op+strlen(op);
                while (!isalnum(*sp))
                {
                   sp++;
                }
                ep = sp;
                while (isalnum(*ep))
                {
                    ep++;
                }
            }
        }
        else if (!strcmp(command,"last") && buffer[4] == '\0')
        {
            int var = 0;
            for (int i = 0; i < strlen(op); i++)
            {
                if (isalnum(op[i]))
                {
                    var++;
                }         
            }
            if (var == 0)
            {
                sp = op+strlen(op);
                ep = op+strlen(op);
            }
            else
            {
                sp = op;
                ep = op+strlen(op);
                while (!isalnum(*ep))
                {
                   ep--;
                }

                sp = ep;
                ep++;
                while (isalnum(*sp))
                {
                    sp--;
                }
                sp++;
            }
        }
        else if (!strcmp(command,"prev") && buffer[4] == '\0')
        {
            if (!isalnum(*sp) && sp>op)
            {
                while (!isalnum(*sp) && sp>op)
                {
                    sp--;
                }
                ep = sp;
                ep++;
                while (isalnum(*sp) && sp>op)
                {
                    sp--;
                }
                if (sp > op)
                {
                    sp++;
                }
                if ((ep-sp) == 1 && !isalnum(*sp))
                {
                    ep = op;
                }
            }
            else if (isalnum(*sp) && sp>op)
            {
                while (isalnum(*sp) && sp>op)
                {
                    sp--;
                }
                while (!isalnum(*sp) && sp>op)
                {
                    sp--;
                }
                ep = sp;
                ep++;
                while (isalnum(*sp) && sp>op)
                {
                    sp--;
                }
                if (sp > op)
                {
                    sp++;
                }
                if ((ep-sp) == 1 && !isalnum(*sp))
                {
                    ep = op;
                }     
            }
            else
            {
                ep = op;
            }  
        }
        else if (!strcmp(command,"next") && buffer[4] == '\0')
        {
            if (!isalnum(*sp) && sp<(op+strlen(op)))
            {
                while (!isalnum(*sp) && sp<(op+strlen(op)))
                {
                    sp++;
                }
                ep = sp;
                while (isalnum(*ep) && ep<(op+strlen(op)))
                {
                    ep++;
                }
            }
            else if (isalnum(*sp) && sp<(op+strlen(op)))
            {
                while (isalnum(*sp) && sp<(op+strlen(op)))
                {
                    sp++;
                }
                
                while (!isalnum(*sp) && sp<(op+strlen(op)))
                {
                    sp++;
                }
                ep = sp;
                while (isalnum(*ep) && ep<(op+strlen(op)))
                {
                    ep++;
                }
            }
        }
        else if (!strcmp(command,"del") && buffer[3] == '\0')
        {
            int value = del(sp, ep, op);
            if (value == 0)
            {
                printf("ERR_POSITION");
                break;
            }
            else if (value == -1)
            {
                continue;
            }
            else if (value == 1)
            {
                ep = sp;
            }
        }
        else if (!strcmp(command,"crop") && buffer[4] == '\0')
        {
            int value = crop(sp, ep, op);
            if (value == 0)
            {
                printf("ERR_POSITION");
                break;
            }
            else if (value == -1)
            {
                sp = op;
                ep = op;
            }
            else if (value == 1)
            {
                sp = op;
                ep = op+strlen(op);
            }
        }
        else if (!strcmp(command,"copy") && buffer[4] == '\0')
        {
            int value = copy(sp, ep, op, mem);
            if (value == 0)
            {
                printf("ERR_POSITION");
                break;
            }
            else if (value == -1)
            {
                continue;
            }
            else if (value == 1)
            {
                continue;
            }
        }
        else if (!strcmp(command,"insert") && buffer[6] == ' ')
        {
            if (sp>ep)
            {
                printf("ERR_POSITION");
                break;
            }
            
            buffer += 7;
            if (!strcmp(buffer,"mem"))
            {
                if (strlen(op) + strlen(mem) > N)
                {
                    printf("ERR_OVERFLOW");
                    break;
                }
                else if (strlen(mem) == 0)
                {
                    continue;
                }

                char tmp[N];
                strcpy(tmp, sp);
                char* ptr = mem;
                char* p = sp;
                while (*ptr != '\0')
                {
                    *p = *ptr;
                    p++;
                    ptr++;
                }
                
                char *pt = tmp;
                for (int i = 0; i < strlen(tmp); i++)
                {
                    *p = *pt;
                    p++;
                    pt++;
                }
                *p = '\0';
                ep += strlen(mem);
            }
            else
            {
                int n = atoi(buffer);
                if (n == 0)
                {
                    continue;
                }
                else if (strlen(op) + n > N)
                {
                    printf("ERR_OVERFLOW");
                    break;
                }

                char tmp[N];
                strcpy(tmp, sp);
                char* p = sp;
                for (int i = 0; i < n; i++)
                {
                    *p = ' ';
                    p++;
                }
                char *pt = tmp;
                for (int i = 0; i < strlen(tmp); i++)
                {
                    *p = *pt;
                    p++;
                    pt++;
                }
                *p = '\0';
                ep += n;
            }
        }
        else if (!strcmp(command,"replace") && buffer[7] == '\0')
        {
            if (sp>ep)
            {
                printf("ERR_POSITION");
                break;
            }
            else if (sp == ep)
            {
                continue;
            }
            else
            {
                replace(sp,ep,op,mem);
            }
        }
    }
    return 0;
}