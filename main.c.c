#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct{
    int accountno;
    char name[50];
    char surname[50];
    char password[20];
    double balance;
}account;
int generateaccountno(){
    FILE *fp;
    account acc;
    int num;
    int found=1;
    do{
        found=1;
        num=rand()%1000;
        fp = fopen("accounts.dat", "rb");
        if (fp != NULL) {
        while(fread(&acc,sizeof(account),1,fp)==1){
            if(num==acc.accountno){
                found=0;
                break;
            }
        }
        fclose(fp);
    }
    }while(!found);
    return num;
}
void createacc(){
    FILE *fp;
    account newaccount;
    newaccount.accountno=generateaccountno();
 printf("adiniz ve soyadinizi giriniz=\n");
 scanf("%s %s",newaccount.name,newaccount.surname);
 printf("hesap sifrenizi giriniz=\n");
 scanf("%s",newaccount.password);
 printf("baslangic bakiyesi giriniz=\n");
 scanf("%lf",&newaccount.balance);
  fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }
 fwrite(&newaccount,sizeof(account),1,fp);
 fclose(fp);
 printf("hesap basariyla olusturuldu!\n");
 printf("hesap numaraniz= %d\n",newaccount.accountno);
}
void deposit(){
    account acc;
    int acno;
    double miktar;
    int found=0;
    char sifre[20];
    FILE *fp;
    printf("hesap numaranizi giriniz=\n");
    scanf("%d",&acno);
    fp=fopen("accounts.dat","rb+");
    if(fp==NULL){
        printf("dosya acilamadi\n");
        return;
    }

    while(fread(&acc,sizeof(account),1,fp)==1){
        if(acc.accountno==acno){
            printf("sifrenizi giriniz=\n");
            scanf("%s",sifre);
            if(strcmp(sifre,acc.password)!=0){
            printf("girilen sifre hatali!\n");
            return;
            }
            printf("yatirmak istediginiz miktari giriniz=\n");
            scanf("%lf",&miktar);
            if(miktar<=0){
                printf("gecersiz miktar girdiniz!\n");
                break;
            }
            acc.balance+=miktar;
            fseek(fp,-(long)sizeof(account),SEEK_CUR);
            fwrite(&acc,sizeof(account),1,fp);
            printf("islem tamam! Guncel bakiye= %0.2f\n",acc.balance);
            found=1;
            break;
        }
    }
    if(!found){
        printf("girilen hesap numarasina ait kayit bulunamadi\n");
    }
    fclose(fp);
}
void withdraw(){
    int acno;
    int found=0;
    account acc;
    char sifre[20];
    double miktar;
    FILE *fp;
    printf("hesap numaranizi giriniz=\n");
    scanf("%d",&acno);
    fp=fopen("accounts.dat","rb+");
    if(fp==NULL){
        printf("dosya acilamadi\n");
        return;
    }
    while(fread(&acc,sizeof(account),1,fp)==1){
        if(acno==acc.accountno){
            printf("sifrenizi giriniz=\n");
            scanf("%s",sifre);
            if(strcmp(sifre,acc.password)!=0){
            printf("girilen sifre hatali!\n");
            return;
            }
            printf("cekmek istediginiz miktari giriniz= ");
            scanf("%lf",&miktar);
             if(miktar<=0){
                printf("gecersiz miktar girdiniz!\n");
                break;
            }
            else if(miktar>acc.balance){
                printf("yeterli bakiye yok!\n");
                return;
            }
            acc.balance-=miktar;
            fseek(fp,-(long)sizeof(account),SEEK_CUR);
            fwrite(&acc,sizeof(account),1,fp);
            printf("islem tamam! Guncel bakiyeniz=%0.2f\n",acc.balance);
            found=1;
            break;
        }
    }
    if(!found){
        printf("girilen hesap numarasina ait kayit bulunamadi!\n");
    }
    fclose(fp);
}
void transfer(){
    int acnogonderen;
    int acnoalici;
    char sifre[20];
    int found=0;
    double miktar;
    account acc;
    FILE *fp;
    printf("hesap numaranizi giriniz=\n");
    scanf("%d",&acnogonderen);
    fp=fopen("accounts.dat","rb+");
    if(fp == NULL){
        printf("Dosya acilamadi!\n");
        return;
    }
    while(fread(&acc,sizeof(account),1,fp)==1){
        if(acc.accountno==acnogonderen){
            printf("sifrenizi giriniz=\n");
            scanf("%s",sifre);
            if(strcmp(sifre,acc.password)!=0){
            printf("girilen sifre hatali!\n");
            return;
            }
            printf("transfer yapmak istediginiz miktari giriniz\n");
            scanf("%lf",&miktar);
            if(miktar<=0){
                printf("gecersiz miktar girdiniz!\n");
                break;
            }
            if(miktar<=acc.balance){
                acc.balance-=miktar;
            }
            else{
                printf("bakiye yetersiz!\n");
                found=1;
                fclose(fp);
                return;
            }
            fseek(fp,-(long)sizeof(account),SEEK_CUR);
            fwrite(&acc,sizeof(account),1,fp);
            found=1;
            printf("gonderici yeni bakiyesi=%lf\n",acc.balance);
            break;
        }
    }
            if(!found){
                printf("girilen hesap numarasina ait kayit bulunamadi\n");
                 fclose(fp);
                return;
            }
            found=0;
            rewind(fp);
            printf("alicinin hesap numarasini giriniz\n");
            scanf("%d",&acnoalici);
            while(fread(&acc,sizeof(account),1,fp)==1){
                if(acnoalici==acc.accountno){
                    acc.balance+=miktar;
                fseek(fp,-(long)sizeof(account),SEEK_CUR);
                fwrite(&acc,sizeof(account),1,fp);
                found=1;
                break;
            }
        }
            if(!found){
                printf("girilen hesap numarasina gore alici kaydi bulunamadi\n");
                rewind(fp);
                while(fread(&acc,sizeof(account),1,fp)==1){
                    if(acc.accountno==acnogonderen){
                        acc.balance+=miktar;
                    fseek(fp,-(long)sizeof(account),SEEK_CUR);
                    fwrite(&acc,sizeof(account),1,fp);
                    printf("paraniz geri yatirildi! Yeni bakiye=%lf\n",acc.balance);
                    break;
                }
            }
            }
            fclose(fp);
}
void showbalance(){
    int acno;
    char sifre[20];
    account acc;
    FILE *fp;
    int found=0;
    fp=fopen("accounts.dat","rb");
    if(fp==NULL){
        printf("dosya acilamadi!\n");
        return;
    }
    printf("hesap numaranizi giriniz=\n");
    scanf("%d",&acno);
    while(fread(&acc,sizeof(account),1,fp)==1){
        if(acc.accountno==acno){
            printf("sifrenizi giriniz=\n");
            scanf("%s",sifre);
            if(strcmp(sifre,acc.password)==0){
            printf("hesap bakiyeniz=%0.2lf\n",acc.balance);
            found=1;
            }
            else {
                printf("sifre hatali\n");
            }
            break;
    }
    }
    if(!found){
        printf("girilen hesap numarasina göre kayit bulunamadi\n");
        return;
    }
    fclose(fp);
}
int num;
int main(){ 
    do{
 printf("hangi islemi yapmak istiyorsunuz?\n");
 printf("1-hesap olusturmak\n2-para yatirma\n3-para cekme\n4-baska hesaba para gonderme\n5-bakiye ogrenme\n6-cikis\n");
 scanf("%d",&num);
 srand(time(NULL));
switch(num){
    case 1:
    createacc();
    break;
    case 2:
    deposit();
    break;
    case 3:
    withdraw();
    break;
    case 4:
    transfer();
    break;
    case 5:
    showbalance();
    break;
    case 6:
    printf("Programdan cikiliyor...\n");
    break;
    default:
    printf("Gecersiz secim!\n");
}
}while(num!=6);
return 0;
}