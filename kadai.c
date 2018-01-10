#include <stdio.h>
#include <string.h>

int registration(void);
int authentication(void);
int getfunc(void);

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
    printf("登録モード\n=========\n10文字以内のパスワードを入力してください。\nパスワード:");
    scanf("%10s", pwinput);
    FILE *pwfilep;
    pwfilep = fopen("password.dat", "wb");
    fwrite(pwinput, sizeof(pwinput), 1, pwfilep);
    fclose(pwfilep);
    puts("パスワードが登録されました。");
    return 0;
}

int authentication(void)
{
    char pwinput[11];
    char pw[11];
    FILE *pwfilep;
    pwfilep = fopen("password.dat", "rb");
    printf("認証モード\n=========\n10文字以内のパスワードを入力してください。\nパスワード:");
    if (pwfilep == NULL)
    {
        puts("password.dat が存在しません。パスワードを登録してください。");
        return 1;
    }
    fread(pw, sizeof(pw), 1, pwfilep);
    scanf("%10s", pwinput);
    if (strcmp(pw, pwinput))
        puts("パスワードが一致しません。");
    else
        puts("パスワードが一致しました。");
    fclose(pwfilep);
    return 0;
}

int getfunc(void)
{
    int func;
    printf("登録:0\t認証:1\n");
    while (1)
    {
        scanf("%d", &func);
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