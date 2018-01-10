#include <stdio.h>
#include <string.h>

int registration();
int authentication();
int getfunc();
long hash(char pw[]);

int main(void)
{
    if (getfunc())
        authentication();
    else
        registration();
    return 0;
}

int registration(void)
{
    char pwinput[11];
    long h;
    printf("登録モード\n=========\n10文字以内のパスワードを入力してください。\nパスワード:");
    scanf("%10s", pwinput);
    h = hash(pwinput);
    FILE *hashfilep;
    hashfilep = fopen("hash.dat", "wb");
    fwrite(&h, sizeof(h), 1, hashfilep);
    fclose(hashfilep);
    puts("パスワードが登録されました。");
    return 0;
}

int authentication(void)
{
    char pwinput[11];
    long h;
    FILE *hashfilep;
    hashfilep = fopen("hash.dat", "rb");
    printf("認証モード\n=========\n");
    if (hashfilep == NULL)
    {
        puts("hash.dat が存在しません。パスワードを登録してください。");
        return 1;
    }
    fread(&h, sizeof(h), 1, hashfilep);
    printf("10文字以内のパスワードを入力してください。\n保存されたhash:%ld\nパスワード:",h);
    scanf("%10s", pwinput);
    if (h != hash(pwinput))
        puts("パスワードが一致しません。");
    else
        puts("パスワードが一致しました。");
    fclose(hashfilep);
    return 0;
}

int getfunc(void)
{
    int func = -1;
    printf("登録:0\t認証:1\n");
    while (1)
    {
        scanf("%1d", &func);
        while (getchar() != '\n')
            ;
        if (func == 0 || func == 1)
        {
            break;
        }
        puts("0 または 1 を入力してください。");
    }
    return (func);
}

long hash(char pw[])
{
    long h = 0;
    int i;
    for (i = 0; i <= (strlen(pw) - 1); i++)
        h = h * 31 + pw[i];
    h = h % 4093;
    printf("hash:%ld\n", h);
    return h;
}