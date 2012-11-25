#include <cstdio>

int main()
{
    FILE *fp = fopen("data.in", "r");
    if (fp) printf("open success!\n");
    char line[9];
    fgets(line, 5, fp);
    printf("%s\n", line);
    fclose(fp);
    
    return 0;
}
