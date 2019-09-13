/*Hüseyin Furkan MACAN 383179
383179@ogr.ktu.edu.tr
    -Struct Oluşturulması ve Kullanımı
    -Harfe Göre Sıralama
    -Puana Göre Sıralama
    -Menü Tasarrımı ve Kodun Birleştirilmesi
    -Daha Önce Oynanan Maç Varsa Uyarı Verilmesi,Tabloya İşlenmemesi
Oğuz Kağan ÇOBAN 383195
kagancoban92@gmail.com
    -Dosyadan Maçları Alma,Tabloyu Güncelleme ve Dosyaya Yazma
    -String İşlemleri
    -Takım İsmine Göre Sıralama
    -Dosyadan Ayarları
    -Takım İsimlerini Dosyadan Alma*/
#include <stdio.h>
#include <stdlib.h>

/*Dosyadan alınacak değişkenler tanımlanır*/
int TakimSayi;
int GalibiyetPuani;
int MaglubiyetPuani;
int BeraberlikPuani;

/*Struct tanımlama*/
struct takim{
    char harf;
    char uzunIsim[15];
    int  oynadigiMacSayisi;
    int  galibiyet;
    int  beraberlik;
    int  maglubiyet;
    int  attigiGol;
    int  yedigiGol;
    int  averaj;
    int  puan;
}takimlar[26],gecici,ad_dizi[26],pivot,puanSiraliDizi[26];

/*Maç tekrarını algılayıp engelleyecek kontrol dizisi tanımlanır.*/
int kontrolDizi[26][26];

void ayar_guncelle();
void klavyegiris();
void ilkdegerler();
void puanSiraliTablo();
void uzun_ad();
void puanTablosu();
void takma_ad();
void ad_sirala();
void buyuk_harf();
void ad_sirala();
void arayuz();
void dosyaya_yaz();
void mac_girisi();


int main(){

//ILK BASTA OYNANAN MAC OLMADIGI ICIN KONTROL DIZISINI 0 A SETLEME
for(int x=0;x<TakimSayi;x++)
{
    for(int y=0;y<TakimSayi;y++)
    {
        kontrolDizi[x][y]=0;
    }
}

//ILK DEGERLERI ATAMA
ayar_guncelle();
ilkdegerler();
takma_ad();
uzun_ad();


arayuz();

}
void arayuz(){

int giris=0;

printf("            TURKIYE SANAL SUPER LIG FIKSTURU\n\n");
while(giris!=-1){

/*Giris Menüsü*/
printf("---------------------------------------------------------\n");
printf("1.Maç girisi yap.\n");
printf("2.Dosyadan maç girisi al\n");
printf("3.Puan tablosunu göster.\n");
printf("4.Puan Sirali Tabloyu Goster.\n");
printf("5.Alfabetik Sirali Tabloyu Göster.\n");
printf("6.Takim Isimlerini Büyük Harfe Çevir.\n");
printf("7.Takim Isimlerini Küçük Harfe Çevir.\n");
printf("8.Tabloyu Dosyaya Yaz.\n\n");
printf("-1.Cikis.\n\n");
printf("Yapacaginiz Islemi Seciniz:\n");
scanf("%d",&giris);
printf("---------------------------------------------------------\n");
if(giris==1){
    klavyegiris();
    puanTablosu();
}
if(giris==2){
    mac_girisi();
    puanTablosu();
}
if(giris==3){
    puanTablosu();
}
if(giris==4){
    puanSiraliTablo();
}
if(giris==5){
    ad_sirala();
}

if(giris==6){
    buyuk_harf();
    puanTablosu();
}
if(giris==7){
    kucuk_harf();
    puanTablosu();
}
if(giris==8){

    dosyaya_yaz();

}

}
}

void ilkdegerler(){
    /*Bütün degerler sifirlanir.*/
    for(int i=0;i<TakimSayi;i++){

        takimlar[i].galibiyet=0;
        takimlar[i].beraberlik=0;
        takimlar[i].maglubiyet=0;
        takimlar[i].attigiGol=0;
        takimlar[i].yedigiGol=0;
        takimlar[i].averaj=0;
        takimlar[i].puan=0;
        for(int j=0;j<TakimSayi;j++){
            kontrolDizi[i][j]=0;
        }
            printf("\n");
    }

}

void ayar_guncelle(){ /*Dosyadan takim sayisi ve galibiyet vs. degerlerini alan fonksiyon*/
    FILE *dosya1;
    if ((dosya1=fopen("ayarlar.txt","r"))!=NULL)
    {
        fscanf(dosya1,"%d %d %d %d",&TakimSayi,&GalibiyetPuani,&BeraberlikPuani,&MaglubiyetPuani);
    }
    else
    {
        printf("Ayarlar Dosyasi Bulunamadi.");
    }
    fclose(dosya1);
}



void klavyegiris(){
    char harf1;
    char harf2;
    int gol2,gol1;
    int takim1;
    int takim2;
/*klavyeden girisler alinir.*/
printf("Takimlarin macini A 3 B 2 formatinda girin.\n\n");
printf("EV SAHIBI TAKIMIN HARFI\n");
printf("| EV SAHIBI TAKIMIN ATTIGI GOL\n");
printf("| | MISAFIR TAKIMIN HARFI\n");
printf("| | | MISAFIR TAKIMIN ATTIGI GOL\n");
printf("| | | |\n");
printf("V V V V\n");
scanf("%s %d %s %d",&harf1,&gol1,&harf2,&gol2);



    /*harflerin ascii deðerlerinden 65 çikarilarak a için 0,
    z için 25 degeri elde edilir.*/
    takim1= harf1 - 65;
    takim2=harf2 - 65;

    if(takim1==takim2){
        printf("Hatali giris yaptiniz.\n");
        return 0;
    }
   /*Maçin daha önce oynanip oynanmadigi tablodan kontrol edilir.*/
   if(kontrolDizi[takim1][takim2]==0){
        takimlar[takim1].attigiGol+=gol1;
        takimlar[takim1].yedigiGol+=gol2;
        takimlar[takim1].averaj=takimlar[takim1].attigiGol - takimlar[takim1].yedigiGol;
        takimlar[takim1].oynadigiMacSayisi+=1;

        takimlar[takim2].attigiGol+=gol2;
        takimlar[takim2].yedigiGol+=gol1;
        takimlar[takim2].averaj=takimlar[takim2].attigiGol - takimlar[takim2].yedigiGol;
        takimlar[takim2].oynadigiMacSayisi+=1;

        /*ev sahibi kazanirsa*/
        if(gol1>gol2){
            /*galip takýmda deðiþiklikler*/
            takimlar[takim1].galibiyet+=1;
            takimlar[takim1].puan+=GalibiyetPuani;

            /*maðlup takýmda deðiþiklikler*/
            takimlar[takim2].maglubiyet+=1;
            takimlar[takim2].puan+=MaglubiyetPuani;
        }


        /*misafir takým kazanirsa*/
        else if(gol2>gol1){
            /*galip takimda degisiklikler*/
            takimlar[takim2].galibiyet+=1;
            takimlar[takim2].puan+=GalibiyetPuani;

            /*maglup takimda degisiklikler*/
            takimlar[takim1].maglubiyet+=1;
            takimlar[takim1].puan+=MaglubiyetPuani;
         }

        /*Maç berabere biterse*/
        else{
            /*galip takýmda degisiklikler*/
            takimlar[takim1].beraberlik+=1;
            takimlar[takim1].puan+=BeraberlikPuani;

            /*maglup takimda degisiklikler*/
            takimlar[takim2].beraberlik+=1;
            takimlar[takim2].puan+=BeraberlikPuani;

        }
        /*Bu maçýn oynandigi kontrol dizisine islenir*/
        kontrolDizi[takim1][takim2]=1;
   }
    else{
        printf("\n\n\n###################\nBU MAÇ DAHA ÖNCE OYNANMIS!!!\n###############\n");
    }
}


void puanTablosu(){ /*Puan durumunu gösteren tabloyu olusturan ve ekrana basan fonksiyon*/
    /*O:Oynanan Maç Sayisi
G,M,B:Galibiyet,Maglubiyet,Beraberlik
AG,YG,P:Atilan Gol,Yenilen Gol,Puan*/
    printf("H     O     G     B     M     AG    YG      Averaj    Puan     Uzun Isim\n");
    for(int i=0;i<TakimSayi;i++){
        printf("%c     %d     %d     %d     %d     %d     %d       %d         %d        %s\n\n",takimlar[i].harf,takimlar[i].oynadigiMacSayisi,takimlar[i].galibiyet,takimlar[i].beraberlik,takimlar[i].maglubiyet,takimlar[i].attigiGol,takimlar[i].yedigiGol,takimlar[i].averaj,takimlar[i].puan,takimlar[i].uzunIsim);
    }
}


void puanSiraliTablo(){/*Puana gore,esitse averaja gore,o da esitse harfe gore siralayan fonksiyon*/

    for(int i=0;i<TakimSayi;i++){
    puanSiraliDizi[i]=takimlar[i];
    }
    for(int j=0;j<TakimSayi-1;j++){/*n takim varsa sondan n-1 tanesini siralamak yeterlidir.*/
        for(int k=0;k<TakimSayi-1;k++){
            if(puanSiraliDizi[k].puan<puanSiraliDizi[k+1].puan){
                pivot=puanSiraliDizi[k];
                puanSiraliDizi[k]=puanSiraliDizi[k+1];
                puanSiraliDizi[k+1]=pivot;
            }
            if(puanSiraliDizi[k].puan==puanSiraliDizi[k+1].puan){
                if(puanSiraliDizi[k].averaj<puanSiraliDizi[k+1].averaj){
                    pivot=puanSiraliDizi[k];
                    puanSiraliDizi[k]=puanSiraliDizi[k+1];
                    puanSiraliDizi[k+1]=pivot;
                }
                if(puanSiraliDizi[k].averaj==puanSiraliDizi[k+1].averaj){
                    int sayi1=puanSiraliDizi[k].harf;
                    int sayi2=puanSiraliDizi[k+1].harf;
                    if(sayi1>sayi2){
                        pivot=puanSiraliDizi[k];
                    puanSiraliDizi[k]=puanSiraliDizi[k+1];
                    puanSiraliDizi[k+1]=pivot;
                    }
                }
            }
        }

    }
    printf("H     O     G     B     M     AG    YG      Averaj   Puan    Uzun Isim\n");
    for(int l=0;l<TakimSayi;l++){

        printf("%c     %d     %d     %d     %d     %d     %d       %d        %d       %s\n\n",puanSiraliDizi[l].harf,puanSiraliDizi[l].oynadigiMacSayisi,puanSiraliDizi[l].galibiyet,puanSiraliDizi[l].beraberlik,puanSiraliDizi[l].maglubiyet,puanSiraliDizi[l].attigiGol,puanSiraliDizi[l].yedigiGol,puanSiraliDizi[l].averaj,puanSiraliDizi[l].puan,puanSiraliDizi[l].uzunIsim);
    }

    }

void buyuk_harf(){
    int j=0;
    //Tum takim adlarini kontrol eden dongu
    for(int i=0;i<TakimSayi;i++)
    {
        //Ad uzunlugunu bulan dongu
        while(takimlar[i].uzunIsim[j]!='\0')
        {
            j++;
        }
        //Ad uzunluguna kadar kontrol edip butun harfleri buyuk yapan dongu
        for(int k=0;k<j;k++)
        {
            // eger kucuk harf(97-122) varsa 32 cikararak buyuk yapma
            if(takimlar[i].uzunIsim[k]>=97 && takimlar[i].uzunIsim[k]<=122)
            {
                takimlar[i].uzunIsim[k]-=32;
            }
        }
    }
}

void takma_ad(){
     char dizi[28] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' } ;

    for (int i=0;i<TakimSayi;i++)
    {
        takimlar[i].harf=dizi[i];
    }
}

void uzun_ad(){

    FILE *dosya2;
    if ((dosya2=fopen("takimlar.txt","r"))!=NULL)
    {
        for(int i=0;i<TakimSayi;i++)
        {
            fscanf(dosya2,"%s",&takimlar[i].uzunIsim);
        }
    }
    else
    {
    printf("dosya bulunamadi");
    }
    fclose(dosya2);
}


void kucuk_harf(){/*Buyuk harfleri kucuk harfe ceviren fonksiyon*/

    int j=0;
    //Tum takim adlarini kontrol eden dongu
    for(int i=0;i<TakimSayi;i++)
    {
        //Ad uzunlugunu bulan dongu
        while(takimlar[i].uzunIsim[j]!='\0')
        {
            j++;
        }
        for(int k=0;k<j;k++)
        {
            // eger kucuk harf(65-92) varsa 32 ekleyerek buyuk yapma
            if(takimlar[i].uzunIsim[k]>=65 &&takimlar[i].uzunIsim[k]<=92)
            {
                takimlar[i].uzunIsim[k]+=32;
            }
        }
    }
}


void mac_girisi(){/*Dosyadan mac girisi alan fonksiyon.*/
    // Geçici Degiskenler
    char ev_sahibi;
    char misafir;
    int skor_es;
    int skor_msf;
    int i=0,j=0;


    FILE *dosya3;
    if ((dosya3=fopen("maclar1.txt","r"))!=NULL)
    {
        //Giris alma döngüsü
        while(!feof(dosya3))//while (feof)
        {

            //DOSYADAN SONUC OKUMA

            fscanf(dosya3,"%c %d %c %d\n",&ev_sahibi,&skor_es,&misafir,&skor_msf);

            //DOSYADAN GIRILEN TAKIMI HARF-ASCII ILE DIZIDEKI YERINI BULMA
            i=ev_sahibi-65;
            j=misafir-65;
            if(i==j){
                printf("Hatali giris (%c-%c)\n",ev_sahibi,misafir);
                continue;
            }
            if(kontrolDizi[i][j]==1)//DOSYADAN GIRILEN MAC DAHA ONCE OYNANMISMI KONTROL ETME
            {
                printf("Bu mac daha once oynandi. %s(%c)-%s(%c)\n",takimlar[i].uzunIsim,takimlar[i].harf,takimlar[j].uzunIsim,takimlar[j].harf);
            }
            else
            {
                kontrolDizi[i][j]=1;
                //takimi bulduktan sonra skor sonuclari girme
                takimlar[i].attigiGol+=skor_es;
                takimlar[i].yedigiGol+=skor_msf;
                takimlar[i].oynadigiMacSayisi+=1;
                takimlar[i].averaj=takimlar[i].attigiGol-takimlar[i].yedigiGol;

                takimlar[j].attigiGol+=skor_msf;
                takimlar[j].yedigiGol+=skor_es;
                takimlar[j].oynadigiMacSayisi+=1;
                takimlar[j].averaj=takimlar[j].attigiGol-takimlar[j].yedigiGol;

                //skorlari karsilastirip sonuclari girme
                if (skor_es>skor_msf)
                {
                    takimlar[i].galibiyet+=1;
                    takimlar[j].maglubiyet+=1;
                    takimlar[i].puan+=GalibiyetPuani;
                    takimlar[j].puan+=MaglubiyetPuani;
                }
                else if (skor_es<skor_msf)
                {
                    takimlar[j].galibiyet+=1;
                    takimlar[i].maglubiyet+=1;
                    takimlar[j].puan+=GalibiyetPuani;
                    takimlar[i].puan+=MaglubiyetPuani;
                }
                else if(skor_es==skor_msf)
                {
                    takimlar[i].beraberlik+=1;
                    takimlar[j].beraberlik+=1;
                    takimlar[i].puan+=BeraberlikPuani;
                    takimlar[j].puan+=BeraberlikPuani;
                }

            }
        }
    }
    //Dosya hatasi
    else
    {
        printf("Mac Giris dosyasi bulunamadi.");
    }
    fclose(dosya3);
}



void dosyaya_yaz(){

    FILE *dosya4;
    dosya4=fopen("puan_tablosu.txt","w");
        //HARF SIRASI ILE YAZMA
        fprintf(dosya4,"()-O\t|G|\t|B|\t|M|\t|A|\t|Y|\t|Av|\t|P|\tUzun Ýsimler\n");
        for(int i=0;i<TakimSayi;i++)
        {
            fprintf(dosya4,"(%c)-%d\t-%d-\t-%d-\t-%d-\t-%d-\t-%d-\t%d\t%d\t%s-\n",takimlar[i].harf,takimlar[i].oynadigiMacSayisi,takimlar[i].galibiyet,takimlar[i].beraberlik,takimlar[i].maglubiyet,takimlar[i].attigiGol,takimlar[i].yedigiGol,takimlar[i].averaj,takimlar[i].puan,takimlar[i].uzunIsim);

        }
        //KUCUK HARF OLARAK YAZMA
        kucuk_harf();
        fprintf(dosya4,"-----------KUCUK HARF----------\n");

        fprintf(dosya4,"()-O\t|G|\t|B|\t|M|\t|A|\t|Y|\t|Av|\t|P|\tUzun Ýsimler\n");
        for(int i=0;i<TakimSayi;i++)
        {
            fprintf(dosya4,"(%c)-%d\t-%d-\t-%d-\t-%d-\t-%d-\t-%d-\t%d\t%d\t%s-\n",takimlar[i].harf,takimlar[i].oynadigiMacSayisi,takimlar[i].galibiyet,takimlar[i].beraberlik,takimlar[i].maglubiyet,takimlar[i].attigiGol,takimlar[i].yedigiGol,takimlar[i].averaj,takimlar[i].puan,takimlar[i].uzunIsim);

        }
        //BUYUK HARF OLARAK DOSYAYA YAZMA
        buyuk_harf();
        fprintf(dosya4,"-----------BUYUK HARF----------\n");

        fprintf(dosya4,"()-O\t|G|\t|B|\t|M|\t|A|\t|Y|\t|Av|\t|P|\tUzun Ýsimler\n");
        for(int i=0;i<TakimSayi;i++)
        {
            fprintf(dosya4,"(%c)-%d\t-%d-\t-%d-\t-%d-\t-%d-\t-%d-\t%d\t%d\t%s-\n",takimlar[i].harf,takimlar[i].oynadigiMacSayisi,takimlar[i].galibiyet,takimlar[i].beraberlik,takimlar[i].maglubiyet,takimlar[i].attigiGol,takimlar[i].yedigiGol,takimlar[i].averaj,takimlar[i].puan,takimlar[i].uzunIsim);
        }
        //ISIM SIRALI OLARAK DOSYAYA YAZMA
        ad_sirala();
        printf("Ad sıralı tablo yazılıyor..\n");
        fprintf(dosya4,"-----------ISIM SIRALI----------\n");
        fprintf(dosya4,"H     O     G     B     M     AG    YG    Averaj Puan  Uzun Ýsim\n");
        for(int i=0;i<TakimSayi;i++){
            fprintf(dosya4,"%c     %d     %d     %d     %d     %d     %d     %d      %d      %s\n",ad_dizi[i].harf,ad_dizi[i].oynadigiMacSayisi,ad_dizi[i].galibiyet,ad_dizi[i].beraberlik,ad_dizi[i].maglubiyet,ad_dizi[i].attigiGol,ad_dizi[i].yedigiGol,ad_dizi[i].averaj,ad_dizi[i].puan,ad_dizi[i].uzunIsim);
        }
        //PUAN SIRALI OLARAK DOSYAYA YAZMA
        puanSiraliTablo();
        printf("Puan sıralı tablo yazılıyor..\n");
        fprintf(dosya4,"-----------PUAN SIRALI----------\n");
        fprintf(dosya4,"H     O     G     B     M     AG    YG    Averaj Puan\n");
        for(int l=0;l<TakimSayi;l++){
        fprintf(dosya4,"%c     %d     %d     %d     %d     %d     %d     %d      %d       %s\n",puanSiraliDizi[l].harf,puanSiraliDizi[l].oynadigiMacSayisi,puanSiraliDizi[l].galibiyet,puanSiraliDizi[l].beraberlik,puanSiraliDizi[l].maglubiyet,puanSiraliDizi[l].attigiGol,puanSiraliDizi[l].yedigiGol,puanSiraliDizi[l].averaj,puanSiraliDizi[l].puan,puanSiraliDizi[l].uzunIsim);
        }

        printf("###############\nMAÇLAR DOSYAYA YAZILDI\n###########\n\n");
fclose(dosya4);
}



void ad_sirala()
{


    for(int i=0;i<TakimSayi;i++){
    ad_dizi[i]=takimlar[i];
    }

    //butun takimlari kontrol etmek icin olan dongu
    for(int i=0;i<TakimSayi;i++)
    {
        //takimlarin uzun ad sýralamasýný kontrol etmek icin olan dongu
        for(int j=0;j<i;j++)
        {
            //takimlarin adlarini ascii koduna gore alfabetik olarak karsilastirma
            if(ad_dizi[j].uzunIsim[0]>ad_dizi[i].uzunIsim[0])
            {
                //eger ascii kod buyukse structtaki gecici degisken yardimiyla siralamayi alfabetik degistirme
                gecici=ad_dizi[i];
                ad_dizi[i]=ad_dizi[j];
                ad_dizi[j]=gecici;
            }
            //ilk harfler ayniysa 2. harfe 2. harf ayniysa 3. harfe ayni mantikla alfabetik siralama degistirme
            else if(ad_dizi[j].uzunIsim[0]==ad_dizi[i].uzunIsim[0])
            {
                if(ad_dizi[j].uzunIsim[1]>ad_dizi[i].uzunIsim[1])
                {
                    gecici=ad_dizi[i];
                    ad_dizi[i]=ad_dizi[j];
                    ad_dizi[j]=gecici;
                }
                  if(ad_dizi[j].uzunIsim[1]==ad_dizi[i].uzunIsim[1])
                {
                    if(ad_dizi[j].uzunIsim[2]>ad_dizi[i].uzunIsim[2])
                    {
                        gecici=takimlar[i];
                        ad_dizi[i]=ad_dizi[j];
                        ad_dizi[j]=gecici;
                    }
                }
            }
        }
    }
    printf("H     O     G     B     M     AG    YG      Averaj   Puan  Uzun Isim\n");
    for(int i=0;i<TakimSayi;i++){
        printf("%c     %d     %d     %d     %d     %d     %d       %d        %d      %s\n\n",ad_dizi[i].harf,ad_dizi[i].oynadigiMacSayisi,ad_dizi[i].galibiyet,ad_dizi[i].beraberlik,ad_dizi[i].maglubiyet,ad_dizi[i].attigiGol,ad_dizi[i].yedigiGol,ad_dizi[i].averaj,ad_dizi[i].puan,ad_dizi[i].uzunIsim);
    }

}
