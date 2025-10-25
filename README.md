## Build Info:
* Requirements: libssl-dev
* Command: ``` g++ main.cpp cli.cpp password_hasher.cpp -o stock-manager -lssl -lcrypto ```

# Stock-Manager Planlama Dokümantasyonu

## 1. Proje Özeti

* Bu belge, “Stock-Manager” adlı basit bir konsol tabanlı stok takip
uygulamasının gereksinimlerini, hedeflerini ve teknik detaylarını özetlemektedir.
* Uygulama kullanıcı türlerine göre stokları izlemelerine ya da ürün alıp satarak stokları yönetmelerine imkan tanıyacaktır. Ayrıca rapor alma fonksiyonları sayesinde kâr/zarar durumu incelenebilecektir.
* Projenin amacı, stok yönetimine ihtiyaç duyan insanlara basit ve kullanıcı dostu bir araç sunmaktır.

## 2. Amaç ve Kapsam

### 2.1. Projenin Amaçları

* Kullanıcılara işlem yapabilecekleri bir konsol komut menüsü sağlamak.
* Basit ve hızlı fonksiyonlar sayesinde kullanıcılara temel işlevleri yerine getiren bir
çözüm sağlamak.
* Raporlama fonksiyonları sayesinde kullanıcıya hızlı geri bildirim sağlamak.
* Takım çalışmasını pekiştirmek ve temel proje yönetim becerisi edinmek.

### 2.2. Hedef Kitle

* Satışları büyük boyutlara ulaşmamış küçük işletmeler.

### 2.3. Kapsam Dışı

Bu projenin ilk versiyonunda aşağıdaki özellikler yer almayacaktır:
* Gelişmiş raporlama
* Dolar bazlı izleme seçeneği
* Birden fazla dil seçeneği
* Grafik kullanıcı arayüzü

## 3. Fonksiyonel Gereksinimler

* Kullanıcı Yönetimi
    * Sabit şekilde standart/yönetici kullanıcı olarak iki mod bulunur.
    * Standart modu uygulama ilk açıldığında bizi karşılar. Sadece mevcut ürünleri ve stok adetlerini listeleyebilir.
    * Yönetici moduna geçiş için şifre belirlenir ve sadece o şifre ile giriş yapılabilir. Tüm fonksiyonlara erişim sahibidir.

* Bakiye Yönetimi
    * Para yatırma ve para çekme gibi özelliklerle bakiye kontrol edilebilir.
    * Eklenen ürün tiplerine göre ürün siparişi geçilip gerekli ücret bakiyeden düşülür.
    * Ürün satışı durumunda satılan ürün fiyatı ve adedi kadar ücret bakiyeye eklenir.

* Ürün Yönetimi
    * Yeni bir ürün sisteme eklenebilir (Ürün Kodu, Adı, Alış Fiyatı, Satış Fiyatı, Mevcut Stok Adedi)
    * Mevcut ürünün kodu hariç her türlü bilgisi güncellenebilecektir.
    * Bir ürün sistemden tamamen silinebilir.
    * Tüm ürünler ve stok durumları listelenebilir.
* Raporlama Yönetimi
    * Geçmişe dönük kâr/zarar raporu oluşturulabilir.
    * En çok satılan ürünler listelenebilir.
    * Mevcut stokların toplam değeri görüntülenebilir.
* Günlük Yönetimi
    * Kullanıcı tarafından yapılan her işlem tarih ve saati ile günlükte tutulur.

## 4. Fonksiyonel Olmayan Gereksinimler

* Kullanılabilirlik: Komutlar sezgisel, basit ve açıklayıcı olmalıdır. Kullanıcı saniyeler içerisinde her türlü işlemi gerçekleştirebilmelidir.
* Güvenlik: Şifreler veritabanında şifrelenmiş (hashed) olarak saklanmalıdır.
* Uyumluluk: Windows ve Linux işletim sistemlerinde sorunsuz çalışmalıdır.

## 5. Teknoloji Yığını

Raporlama, çoklu para birimi ve arayüz modülleri Python ile, kalan modüller C++ ile yazılacaktır.

## 6. Sistem Mimarisi

* Uygulama yerel olarak çalışacaktır. Herhangi bir sunucu bağlantısı söz konusu değildir.
* Günlük tutma ve veritabanı da uygulama dizininde saklanacaktır. Veriler .log ve .db uzantılarıyla basit metin dosyaları olarak tutulacaktır.

## 7. Proje Zaman Çizelgesi

* Aşama 1: Komut Sistemi, Bakiye ve Veritabanı modüllerinin geliştirilmesi
    * Komut sisteminin oluşturulması
    * Bakiye sisteminin oluşturulması
    * Veritabanı şemasının oluşturulması
* Aşama 2: Ürün Yönetimi ve Günlük Yönetimi fonksiyonlarının
geliştirilmesi
    * Ürün yönetimi fonksiyonların yazılması ve veritabanı bağlantılarının kurulması
    * Günlük yönetimi fonksiyonlarının yazılması ve gerekli yerlere uygulanması
* Aşama 3: Arayüz, Raporlama ve Çoklu Para Birimi özelliklerinin eklenmesi
    * Arayüz ve dil desteği eklenmesi
    * Raporlama fonksiyonlarının yazılması
    * Çoklu para birimi desteğinin eklenmesi

*Bu belge, 25.10.2025 tarihinde Süleyman Kara tarafından Astra-Cukurova adına güncellenmiştir.*
